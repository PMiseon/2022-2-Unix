#include <stdio.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mymsgbuf{
        long mtype;
        char mtext[80];
}

//char byemsg[80] = "bye";

main(){

        key_t key;
        int msgid;
        struct mymsgbuf pmsg, cmsg;
        //parent msg, child msg
        pid_t pid;
        char msg[80];

        msgid = msgget(15011015, IPC_CREAT|0644);
        int flag = 0;

        switch(pid = fork()){

        case -1 :
                perror("fork");
                exit(1);
                break;

        case 0 : //child

                while(1){
        //      printf("child : ");
        //      fflush(stdin);
                fgets(msg, sizeof(msg),stdin);
                if(strcmp(msg,"bye\n") == 0){
                        cmsg.mtype = 2;
                        flag = 1;
                        }

                else {
                        cmsg.mtype = 1;
                        }

                strcpy(cmsg.mtext,msg);
                msgsnd(msgid, (void *)&cmsg, 80, 0);

                if(flag == 1) break;

                }

                break;


        default : //parent

                while(1){
                msgrcv(msgid, &pmsg, 80,0,0);
        //      printf("parent : %s\n" pmsg.mtext);
//              printf("mtype : %d\n" ,pmsg.mtype);
                if(pmsg.mtype == 1)
                        printf("msg : %s\n", pmsg.mtext);

                else if(pmsg.mtype == 2){
                //      exit(1);
                        break;
                        }

                }
        //      exit(1);
                break;
        }



}

