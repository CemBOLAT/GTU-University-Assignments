
#include "../includes/errors.h"
#include "../includes/funcs.h"
#include "../includes/utils.h"
#include <sys/errno.h>
#include <unistd.h>

int display_help() {
    if (write(STDOUT_FILENO, USAGE_GUIDE, sizeof(USAGE_GUIDE) - 1) < 0) {
        add_log("Error ", "writing ", "to stdout while displaying help", NULL, 1);
        my_perror("Error writing to stdout while displaying help");
        return 1;
    }
    add_log("Help", " displayed ", "successfully", NULL, 0);
    return 0;
}