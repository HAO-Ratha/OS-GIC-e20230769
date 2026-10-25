/* file_reader_sys.c */
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    char buffer[256];

    // 1. Open "output.txt" for reading using open()
    int fd = open("output.txt", O_RDONLY);
    if (fd < 0) {
        const char *err = "Error opening file\n";
        write(STDERR_FILENO, err, strlen(err));
        return 1;
    }

    // 2. Read content into buffer using read() in a loop
    ssize_t n;
    while ((n = read(fd, buffer, sizeof(buffer))) > 0) {
        // 3. Write the content to the terminal (fd 1) using write()
        write(STDOUT_FILENO, buffer, n);
    }

    // 4. Close the file using close()
    close(fd);

    return 0;
}
