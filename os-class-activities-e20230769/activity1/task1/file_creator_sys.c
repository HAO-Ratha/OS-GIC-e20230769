/* file_creator_sys.c */
#include <fcntl.h>    // open(), O_WRONLY, O_CREAT, O_TRUNC
#include <unistd.h>   // write(), close()
#include <string.h>   // strlen()

int main() {
    // 1. Open/create "output.txt" using open()
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        const char *err = "Error opening file\n";
        write(STDERR_FILENO, err, strlen(err));
        return 1;
    }

    // 2. Write the text using write()
    const char *text = "Hello from Operating Systems class!\n";
    write(fd, text, strlen(text));

    // 3. Close the file using close()
    close(fd);

    // 4. Print the success message to the terminal using write()
    const char *msg = "File created successfully!\n";
    write(STDOUT_FILENO, msg, strlen(msg));

    return 0;
}
