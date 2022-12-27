#include <sys/types.h>
#include <signal.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void handler(int dummy) {
    ;
}

main() {

        key_t key;
        int shmid, pid;
        void *shmaddr;
        char buf[1024];
        sigset_t mask;

        shmid = shmget(15011015, 1024, IPC_CREAT|0666);

        sigfillset(&mask);
        sigdelset(&mask, SIGUSR1);
        sigset(SIGUSR1, handler);
        printf("Server wait for client\n");
        printf("Server PID : %d\n", getpid());

        sigsuspend(&mask);
        //신호가 올때까지 대기


//      sleep(10);
        //공유메모리에서 get child pid
        shmaddr = shmat(shmid, NULL, 0);
        strcpy(buf, shmaddr);
        printf("Client PID : %s\n",buf);

        int cpid = atoi(buf);
        //통신 시작
        while(1){

        sigsuspend(&mask);
        strcpy(buf,shmaddr);
        printf("From Client : %s\n",buf);

        //client pid 정보 저장하기
//      int cpid = atoi(buf);

       if(strcmp(buf,"q\n") == 0)
                break;


        printf("To Client: ");
        fgets(buf,sizeof(buf),stdin);
        strcpy(shmaddr, buf);
//      if(strcmp(buf, "q\n") ==0 )
//              break;

        kill(cpid,SIGUSR1);
          
                  if(strcmp(buf,"q\n") == 0)
                break;
        }


        shmdt(shmaddr);
}

