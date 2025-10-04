#include "../include/common.h"
#include "../ipc/include/fifo_utils.h"
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <errno.h>

int fd_descriptor = -1;
int server_fifo_descriptor = -1;
int client_fifo_descriptor = -1;
char* fifo_name = NULL;

// Signal handler for clean shutdown
void sig_handler(int signo) {
    if (signo == SIGTERM || signo == SIGINT) {
        printf("Client process %d exiting...\n", getpid());
        if (fifo_name != NULL) {
            remove_fifo(fifo_name);
        }
        if (fd_descriptor != -1) close(fd_descriptor);
        if (server_fifo_descriptor != -1) close(server_fifo_descriptor);
        if (client_fifo_descriptor != -1) close(client_fifo_descriptor);
        exit(EXIT_SUCCESS);
    }
    if (signo == SIGUSR1) {
        printf("Server is down!..Exiting...\n");
        if (fifo_name != NULL) {
            remove_fifo(fifo_name);
        }
        if (fd_descriptor != -1) close(fd_descriptor);
        if (server_fifo_descriptor != -1) close(server_fifo_descriptor);
        if (client_fifo_descriptor != -1) close(client_fifo_descriptor);
        exit(EXIT_SUCCESS);
    }
}

// Read a line from a file descriptor into buffer
int read_line(int fd, char *buffer, size_t size) {
    ssize_t bytes_read = 0;
    char c;
    while (bytes_read < size - 1) {
        ssize_t result = read(fd, &c, 1);
        if (result <= 0) break;
        if (c == '\n') break;
        buffer[bytes_read++] = c;
    }
    buffer[bytes_read] = '\0';
    return bytes_read;
}


// Parse a transaction line into a ClientRequest structure
int parse_transaction_line(char* line, ClientRequest* req) {
    char type_str[16], trans_str[16];
    int amount;
    memset(req, 0, sizeof(ClientRequest));

    req->client_pid = getpid();
    generate_client_fifo_name(req->client_fifo, req->client_pid);

    int parsed = sscanf(line, "%s %s %d", type_str, trans_str, &amount);
    if (parsed < 3) return -1;

    if (strcmp(type_str, "N") == 0) {
        req->bank_id[0] = '\0';
        req->new_account = 1;
    } else if (strncmp(type_str, "BankID_", 7) == 0) {
        strncpy(req->bank_id, type_str, MAX_BANK_ID_LEN - 1);
    } else {
        snprintf(req->bank_id, MAX_BANK_ID_LEN, "BankID_%s", type_str);
    }

    if (strcmp(trans_str, "deposit") == 0) {
        req->type = TRANSACTION_DEPOSIT;
    } else if (strcmp(trans_str, "withdraw") == 0) {
        req->type = TRANSACTION_WITHDRAW;
    } else {
        return -1;
    }

    req->amount = amount;
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <ClientXX.file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Setup signal handlers
    signal(SIGTERM, sig_handler);
    signal(SIGINT, sig_handler);
    signal(SIGUSR1, sig_handler);
    signal(SIGPIPE, SIG_IGN);

    // Open client file
    int fd = open(argv[1], O_RDONLY);
    fd_descriptor = fd;
    if (fd == -1) {
        perror("open client file");
        exit(EXIT_FAILURE);
    }

    // Create client FIFO
    char client_fifo[MAX_FIFO_NAME_LEN];
    generate_client_fifo_name(client_fifo, getpid());
    if (create_fifo(client_fifo) == -1) {
        close(fd);
        exit(EXIT_FAILURE);
    }
    fifo_name = client_fifo;

    ClientRequest requests[MAX_REQUESTS];
    int request_count = 0;

    char line[MAX_LINE_LEN];
    printf("Reading %s...\n", argv[1]);
    while (read_line(fd, line, sizeof(line)) > 0) {
        ClientRequest req;
        if (parse_transaction_line(line, &req) == 0) {
            req.client_id = request_count + 1;
            requests[request_count++] = req;
        }
    }
    
    printf("%d client to connect.. creating clients...\n", request_count);
    
    // Connect to server FIFO
    int server_fd = open_fifo_write(SERVER_FIFO_NAME);
    server_fifo_descriptor = server_fd;
    if (server_fd == -1) {
        printf("Cannot connect to ServerFIFO_CemalBOLAT..\nexiting...\n");
        remove_fifo(client_fifo);
        close(fd);
        exit(EXIT_FAILURE);
    }

    
    printf("Connected to BankServer...\n");
    
    // Send client FIFO name to server  
    if (write(server_fd, client_fifo, strlen(client_fifo)) != (ssize_t)strlen(client_fifo)) {
        perror("write fifo name to server");
        close(server_fd);
        remove_fifo(client_fifo);
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (close(server_fd) == -1) {
        perror("close server fifo");
        remove_fifo(client_fifo);
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    // Open client FIFO for writing requests
    int fifo_write_fd = open(client_fifo, O_WRONLY);
    if (fifo_write_fd == -1) {
        perror("open client fifo for writing");
        remove_fifo(client_fifo);
        close(fd);
        exit(EXIT_FAILURE);
    }
    

    // Send each request to server
    for (int i = 0; i < request_count; ++i) {
        ClientRequest req = requests[i];
        printf("Client%02d connected..%s %d credits\n",
            i + 1,
            req.type == TRANSACTION_DEPOSIT ? "depositing" : "withdrawing",
            req.amount);
            
        //sig_handler(SIGTERM); // test case 1
        if (write(fifo_write_fd, &requests[i], sizeof(ClientRequest)) != sizeof(ClientRequest)) {
            char error_msg[128];
            snprintf(error_msg, sizeof(error_msg), "write to client fifo failed for client%02d", i + 1);
            perror(error_msg);
        }
    }
        
    printf("..\n");
    if (close(fifo_write_fd) == -1) {
        perror("close client fifo for writing");
        remove_fifo(client_fifo);
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Open client FIFO for reading responses
    int fifo_read_fd = open(client_fifo, O_RDONLY);
    client_fifo_descriptor = fifo_read_fd;
    if (fifo_read_fd == -1) {
        perror("open client fifo for reading");
        remove_fifo(client_fifo);
        close(fd);
        exit(EXIT_FAILURE);
    }
        
    printf("Waiting for responses...\n");
        
    // Read responses with timeout
    time_t now = time(NULL);
    int timeout = request_count * TIMEOUT_SECONDS;
    int read_response = 0;
    while (time(NULL) - now < timeout) {
        ServerResponse resp;
        ssize_t bytes_read = read(fifo_read_fd, &resp, sizeof(ServerResponse));
        if (bytes_read == sizeof(ServerResponse)) {
            if (resp.new_balance == 0 && resp.success){
                printf("Client%02d served.. account closed\n", read_response + 1);
            }
            else if (resp.success) {
                printf("Client%02d: served.. %s new balance: %d\n", read_response + 1, resp.bank_id, resp.new_balance);
            } else {
                printf("Client%02d something went WRONG :%s\n", read_response + 1, resp.message);
            }
            read_response++;
        } 
        else if (read_response == request_count)
            break;
        else if (bytes_read == -1){
            break;
        }
        else if (bytes_read == 0) {
            sleep(1);
        }
        //sig_handler(SIGTERM); // test case 2
        //while (1); // test case 3
    }
    
    if (read_response < request_count) {
        printf("Timeout occurred. Not all responses received.\n");
    }
    printf("exiting...\n");


    // Cleanup
    if (close(fifo_read_fd) == -1) {
        perror("close client fifo for reading");
    }
    if (close(fd) == -1) {
        perror("close client file");
    }
    if (remove_fifo(client_fifo) == -1) {
        perror("remove client fifo");
    }
    return 0;
}