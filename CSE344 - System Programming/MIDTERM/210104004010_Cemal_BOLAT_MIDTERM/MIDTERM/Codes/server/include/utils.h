#ifndef UTILS_H
#define UTILS_H

#define LOG_PATH "AdaBank.bankLog"

void    generate_bank_id(char* out, int id_num);
void    cleanup_and_exit(int status);
void    handle_signal(int signo);
int     extract_id(const char* bank_id);
int     extract_pid(const char* fifo_name);
int     read_db_format(int fd, char* id, int *balance, int max_id_len);

#endif