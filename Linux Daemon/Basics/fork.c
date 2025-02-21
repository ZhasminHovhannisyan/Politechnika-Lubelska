#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
    pid_t child_pid;
    char *message;
    int repetition;
    printf("So far only one process is runing\n");
    child_pid = fork();
    switch (child_pid)
    {
        case -1:
        printf("fork process failed\n");
        exit(1);
        case 0:
        message = "J am a child";
        repetition = 5;
        break;
        default:
        message = "J am a parent";
        repetition = 5;
        break;
    }
    for (; repetition > 0; repetition--)
    {
        puts(message);
        sleep(1);
    }
}
