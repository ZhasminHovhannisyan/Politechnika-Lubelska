//Modify the program from the previous exercise
//so that each of the processes (parent and child)
//will display the ID: own, parent and child.

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
    pid_t child_pid, id1, id2;
    char message[50];
    int repetition;
    printf("So far only one process is runing\n");
    child_pid = fork();
    id1 = getpid();
    id2 = getppid();
    switch (child_pid)
    {
        case -1:
            printf("fork process failed\n");
            exit(1);
         case 0:
            snprintf(message, 49, "I am a child, my pid is %d", id1);
            repetition = 5;
            break;

        default:
            id2 = getpid();
            snprintf(message, 49, "I am a parent, my pid is %d", id2);
            repetition = 5;
            break;
    }

    // Print the message in a loop
    for (; repetition > 0; repetition--) {
        puts(message);
        sleep(1);
    }

    return 0;
}
