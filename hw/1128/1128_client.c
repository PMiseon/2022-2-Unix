#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/shm.h>

void handler(int dummy){
;
}


main(int argc, char **argv){

        key_t key;
        int shmid;
        void *shmaddr;
        char buf[1024];
        sigset_t mask;


        shmid = shmget(15011015,1024,IPC_CREAT|0666);

        sigfillset(&mask);
        sigdelset(&mask, SIGUSR1);
        sigset(SIGUSR1, handler);

        shmaddr = shmat(shmid,NULL,0);
        //공유메모리 연결
        //
        sprintf(buf,"%d",getpid());
        printf("client pid (check) : %s\n", buf);
        strcpy(shmaddr,buf);
        kill(atoi(argv[1]),SIGUSR1);
        sleep(3);

        //통신 시작

        while(1){
        printf("Client send: "),
        fgets(buf,sizeof(buf),stdin);
        strcpy(shmaddr, buf);
//      if(strcmp(buf,"q\n") == 0)
//              break;
        kill(atoi(argv[1]),SIGUSR1);

        if(strcmp(buf, "q\n") == 0)
                break;

        sigsuspend(&mask);

        strcpy(buf,shmaddr);
        printf("From Server : %s",buf);
        printf("\n");


        if(strcmp(buf,"q\n") == 0)
                break;

          


        }




        //공유메모리 연결해제 & 삭제
        shmdt(shmaddr);
        shmctl(shmid, IPC_RMID,NULL);
}
