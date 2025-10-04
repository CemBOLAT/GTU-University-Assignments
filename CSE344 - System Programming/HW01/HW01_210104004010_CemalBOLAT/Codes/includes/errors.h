#ifndef ERRORS_H
#define ERRORS_H

// Error messages for directory operations
#define ERR_DIRECTORY "Error: Directory \""
#define ERR_ALREADY_EXISTS "\" already exists.\n"
#define ERR_NOT_FOUND "\" not found.\n"
#define ERR_CANNOT_CREATED "\" cannot be created:"
#define ERR_CANNOT_LIST "\" cannot be listed:"
#define ERR_DIR_NAME_NULL "Error: Directory name cannot be NULL.\n"
#define ERR_EXTENSION_NULL "Error: Extension cannot be NULL.\n"
#define ERR_CANNOT_DELETE "\" cannot be deleted:"

// Error messages for file operations
#define ERR_FILE "Error: File \""
#define ERR_CANNOT_WRITE "Error: Cannot write to \""
#define ERR_FILE_LOCKED "\". File is locked or read-only.\n"
#define ERR_FILE_NAME_NULL "Error: File name cannot be NULL.\n"
#define ERR_FILE_CONTENT_NULL "Error: File content cannot be NULL.\n"
#define ERR_CREATED_BUT_TIMESTAMP " created but timestamp cannot be written:"
#define ERR_CREATED_BUT_CLOSING " created but closing is failed:"
#define ERR_CANNOT_READ "\" cannot be read:"
#define ERR_CANNOT_APPEND "\" cannot be appended:"

// Success messages
#define DIRECTORY "Directory \""
#define CREATED_SUCCESS "\" created successfully.\n"
#define FILE  "File \""
#define DELETED_SUCCESS "\" deleted successfully.\n"

#define LISTED_SUCCESS "\" listed successfully.\n"
#define READ_SUCCESS "\" read successfully.\n"

// Usage guide
#define USAGE_GUIDE "Usage: fileManager <command> [arguments]\n\nCommands:\n" \
    "  createDir \"folderName\"         - Create a new directory\n" \
    "  createFile \"fileName\"          - Create a new file\n" \
    "  listDir \"folderName\"           - List all files in a directory\n" \
    "  listFilesByExtension \"folderName\" \".txt\" - List files with specific extension\n" \
    "  readFile \"fileName\"            - Read a file's content\n" \
    "  appendToFile \"fileName\" \"new content\"  - Append content to a file\n" \
    "  deleteFile \"fileName\"          - Delete a file\n" \
    "  deleteDir \"folderName\"         - Delete an empty directory\n" \
    "  showLogs                        - Display operation logs\n"

#endif // ERRORS_H
