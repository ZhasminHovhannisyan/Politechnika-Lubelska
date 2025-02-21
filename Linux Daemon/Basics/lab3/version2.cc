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
void sig_alrm_handling(int sig)
{
    signal(SIGINT, SIG_DFL);
}
int main(int argc, char** argv)
{
    signal(SIGINT, sig_int_handling);
    signal(SIGALRM, sig_alrm_handling);
    alarm(7);
    while (true)
    {
        printf("Hello it is process: %d\n", getpid());
        sleep(1);
    }

    return 0;
}
// signal, functions
