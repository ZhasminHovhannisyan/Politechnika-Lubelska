#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_FILE "/tmp/fifi_fifo"
#define ROZM_BUF 2048

int main(int argc, char** argv) {

    int descriptor;

    /*check maybe fifo was already created*/
    if (access(FIFO_FILE,F_OK)!=0)
        /*if non we create a fifo*/
        if (mkfifo(FIFO_FILE, S_IRUSR | S_IWUSR)!=0)
                printf("failed to create fifo\n");
        else printf("fifo created successfully\n");
    else printf("fifo already exists\n");

    /*trying to open fifo for writing*/
    printf("consumer opens fifo for reading and waits for produces\n");
    descriptor=open(FIFO_FILE,O_RDONLY);
    printf("producer opened fifo. Descriptor: %d\n",descriptor);

    /*writing data*/
    printf("consumer is receiving the data\n");
    int counter;
    char bufor[ROZM_BUF];
    for (counter = 0; counter < 10; counter++) {
        read(descriptor,bufor,ROZM_BUF);
        printf("%s\n",bufor);
    }

    close(descriptor);

    return (EXIT_SUCCESS);
}
