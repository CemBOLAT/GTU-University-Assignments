#include "util.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
 * This function will take the environment variables and the command to be executed
 * and return the full path of the command if it is found in the environment variables.
 * If the command is not found in the environment variables, it will return NULL.
 *
 * @param env: The environment variables
 * @param cmd: The command to be executed
 * @return: The full path of the command if it is found in the environment variables, NULL otherwise.
*/
char	*pathFinder(char **env, char *cmd){
	int i = 0;
	char *path = NULL;
	char *token;
	char *pathEnv = NULL;
	while (env[i] != NULL){
		if (strncmp(env[i], "PATH=", 5) == 0){
			pathEnv = env[i];
			break;
		}
		i++;
	}
	if (pathEnv == NULL){
		return NULL;
	}
	pathEnv += 5;
	token = strtok(pathEnv, ":");
	while (token != NULL){
		path = (char *)malloc(strlen(token) + strlen(cmd) + 2);
		strcpy(path, token);
		strcat(path, "/");
		strcat(path, cmd);
		if (access(path, F_OK) == 0){
			return path;
		}
		cb_free((void *)path);
		token = strtok(NULL, ":");
	}
	return NULL;
}
