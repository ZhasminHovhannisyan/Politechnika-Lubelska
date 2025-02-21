#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main() {
    pid_t child_pid;
    int processed_data;
    int file_pipes[2];
    const char some_data[] = "123";
    char buffer[BUFSIZ + 1];
    memset(buffer, '\0', sizeof(buffer));
    int result = pipe(file_pipes);
    child_pid = fork();
    if (result == 0) {
        if (child_pid == 0){
            processed_data = write(file_pipes[1], some_data, strlen(some_data));
            printf("Wrote %d bytes\n", processed_data);
            close(file_pipes[1]);
        }
        else{
            processed_data = read(file_pipes[0], buffer, BUFSIZ);
            printf("Read %d bytes: %s\n", processed_data, buffer);
            close(file_pipes[0]);
            
        }
        exit(EXIT_SUCCESS);
    }
    else
    exit(EXIT_FAILURE);
}
