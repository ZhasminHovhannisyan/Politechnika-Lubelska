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
    printf("poroducer opens the fifo and waits for the consuler\n");
    descriptor=open(FIFO_FILE,O_WRONLY);
    printf("consumer opened fifo. Descriptor: %d\n",descriptor);

    /*writing data*/
    printf("producer is sending data\n");
    int counter;
    char bufor[ROZM_BUF];
    for (counter = 0; counter < 10; counter++) {
        sprintf(bufor,"napis %d",counter);
        write(descriptor,bufor,ROZM_BUF);
        sleep(1);
    }

    close(descriptor);

    return (EXIT_SUCCESS);
}
