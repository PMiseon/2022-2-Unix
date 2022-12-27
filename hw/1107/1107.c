#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void){

        int fd1[2], fd2[2];
        pid_t pid;
        char buf[257]; //256+1
        char msg[257] = "";

        if(pipe(fd1) == -1){
                perror("pipe fd1");
                exit(1);
        }

        if(pipe(fd2) == -1){
                perror("pipe fd2");
                exit(1);
        }

        int len;

        switch(pid = fork()){
        case -1:
                perror("fork");
                exit(1);
                break;

        case 0: //child
                close(fd1[1]);
                close(fd2[0]);

        //      write(1,"Child Process: ",15);
                len = read(fd1[0],buf,256);
                write(1,"From parent:",15);
                write(1,buf,256);
                write(1,"\n",3);
        //      *msg = "\n";
                write(1,"child :",15);
                fgets(msg,sizeof(msg),stdin);
                write(fd2[1],msg,sizeof(msg));

                break;


        default : //parent
                close(fd1[0]);
                close(fd2[1]);

//              len = read(fd2[0],buf,256);
                write(1,"From child:",15);
                write(1,buf,256);
                write(1,"\n",3);
//              *msg = "\n";
                write(1,"Parent:",15);
                fgets(msg,sizeof(msg),stdin);
//              scanf("%s",&buf);
                write(fd1[1],msg,sizeof(msg));

                break;

        }
}
