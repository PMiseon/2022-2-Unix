#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

//sigset_t new;

void handler(int signo){

        psignal(signo, "Received Signal SIGINT: ");
        sleep(10);
        printf("In Signal Handler, After Sleep\n");

//      sigprocmask(SIG_UNBLOCK, &new, (sigset_t *)NULL);
}

int main(void){

        struct sigaction act;
        int i;
        sigset_t new;

        printf("pid = %d\n",getpid());

        sigemptyset(&act.sa_mask);
        sigemptyset(&new);
        sigaddset(&new, SIGUSR1);
        sigprocmask(SIG_BLOCK, &new, (sigset_t*)NULL);
        act.sa_flags = 0;
        act.sa_handler = handler;

        if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0){
                perror("sigaction");
                exit(1);
        }

        fprintf(stderr, "Input SIGINT: ");
        pause();
  
  
        sigprocmask(SIG_UNBLOCK, &new, (sigset_t *)NULL);

              return 0;
//
//              }
}


