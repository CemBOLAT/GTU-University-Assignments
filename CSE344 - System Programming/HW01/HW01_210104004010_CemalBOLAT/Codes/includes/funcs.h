#ifndef FUNCS_H
#define FUNCS_H

int display_help();

// Directory Operations
int create_dir(const char *dir_name);
int list_dir(const char *dir_name);
int delete_dir(const char *dir_name);
int list_files_by_extension(const char *dir_name, const char *extension);

// File Operations
int create_file(const char *file_name);
int read_file(const char *file_name);
int append_to_file(const char *file_name, const char *content);
int delete_file(const char *file_name);
int add_log(const char *macro, const char *content, const char *macro2, const char *error, int has_error);

#endif // FUNCS_H