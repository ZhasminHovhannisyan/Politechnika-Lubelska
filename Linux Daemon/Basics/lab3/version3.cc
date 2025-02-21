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
    signal(SIGINT, sig_int_handling);
    sigset_t blocked_signals;
    sigset_t sent_signals;
    sigemptyset(&blocked_signals);
    sigaddset(&blocked_signals, SIGINT);
    sigaddset(&blocked_signals, SIGQUIT);
    sigprocmask(SIG_BLOCK, &blocked_signals, NULL);

    int counter = 0;
    while(true)
    {
        printf("Hello it is process: %d\n", getpid());
        sleep(1);
        counter ++;
        if (counter == 15){
            sigpending(&sent_signals);
            if (sigismember(&sent_signals, SIGINT))
                printf("Signal INT was sent \n");
            if (sigismember(&sent_signals, SIGQUIT))
                printf("Signa QUIT was sent \n");
            sigprocmask(SIG_UNBLOCK, &blocked_signals, NULL);
        }
    }
    printf("Only 15 minutes of our class left");

    return 0;
}
