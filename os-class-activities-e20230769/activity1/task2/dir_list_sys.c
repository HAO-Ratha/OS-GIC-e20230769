/* dir_list_sys.c */
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>    // only for snprintf to format numbers into strings

int main() {
    char buffer[512];

    // 1. Open current directory with opendir(".")
    DIR *dir = opendir(".");
    if (dir == NULL) {
        const char *err = "Error opening directory\n";
        write(STDERR_FILENO, err, strlen(err));
        return 1;
    }

    // 2. Print header line using write()
    const char *header = "Directory listing:\n";   // copy from dir_list_lib.c
    write(STDOUT_FILENO, header, strlen(header));

    // 3. Loop through entries with readdir()
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        struct stat st;

        // 4. For each entry, use stat() to get file size
        if (stat(entry->d_name, &st) < 0) {
            continue;   // skip entries we cannot stat
        }

        // 5. Format output into buffer with snprintf(), then write() to fd 1
        int len = snprintf(buffer, sizeof(buffer), "%-30s %ld bytes\n",   // copy format from dir_list_lib.c
                           entry->d_name, (long)st.st_size);
        write(STDOUT_FILENO, buffer, len);
    }

    // 6. Close directory with closedir()
    closedir(dir);

    return 0;
} 
