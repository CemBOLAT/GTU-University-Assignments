#pragma once

void cmd_exit(int sockfd);
void cmd_join(int sockfd, const char *room_name);
void cmd_leave(int sockfd);
void cmd_broadcast(int sockfd, const char *message);
void cmd_whisper(int sockfd, const char *target, const char *message);
void cmd_sendfile(int sockfd, const char *target, const char *filename);
