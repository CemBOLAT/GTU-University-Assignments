#include "../includes/errors.h"
#include "../includes/funcs.h"
#include <string.h>

int main(int argc, char **argv) {
    if (argc == 1) {
        return display_help();
    }
    else if (argc == 3 && strcmp(argv[1], "createDir") == 0) {
        return create_dir(argv[2]);
    }
    else if (argc == 3 && strcmp(argv[1], "createFile") == 0) {
        return create_file(argv[2]);
    }
    else if (argc == 3 && strcmp(argv[1], "listDir") == 0) {
        return list_dir(argv[2]);
    }
    else if (argc == 4 && strcmp(argv[1], "listFilesByExtension") == 0){
        return list_files_by_extension(argv[2], argv[3]);
    }
    else if (argc == 3 && strcmp(argv[1], "readFile") == 0){
        return read_file(argv[2]);
    }
    else if (argc == 4 && strcmp(argv[1], "appendToFile") == 0){
        return append_to_file(argv[2], argv[3]);
    }
    else if (argc == 3 && strcmp(argv[1], "deleteFile") == 0){
        return delete_file(argv[2]);
    }
    else if (argc == 3 && strcmp(argv[1], "deleteDir") == 0){
        return delete_dir(argv[2]);
    }
    else if (argc == 2 && strcmp(argv[1], "showLogs") == 0){
        return read_file("log.txt");
    }
    else {
        return display_help();
    }
}