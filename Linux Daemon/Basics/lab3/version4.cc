#include <signal.h>
#include <stdio.h>
#include <unistd.h>
//basic version of the program displays 3 subtitles by pressing CTRL+C
//to finish the program press CTRL+\ (SIGQUIT)

char strings[3][80] = { "Ha! Ha! Ha! It's only a superficial signal!\n",
 "Only process %d can ignore signal %d \n",
 "Ouch - that hurt!\n" };
int string_no = 0;
//void (*signal(int sig, void (*func)(int)))(int);
void sig_int_handling(int sig)
{
    printf(strings[string_no], getpid(), sig);
    string_no = ((string_no + 1) % 3);
}


int main(int argc, char** argv)
{


    sigset_t blocked_signals;
    sigemptyset(&blocked_signals);
    sigaddset(&blocked_signals, SIGINT);
    sigaddset(&blocked_signals, SIGQUIT);

    struct sigaction sigactstruct;
    sigactstruct.sa_handler = sig_int_handling;
    sigactstruct.sa_mask = blocked_signals;
    sigactstruct.sa_flags = 0;


    sigaction(SIGINT,&sigactstruct, NULL);

    while (true)
    {
        printf("Hello it is process: %d\n", getpid());
        sleep(5);
    }

    return 0;
}
