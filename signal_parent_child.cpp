#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

//handle SIGSTOP signal by child process, however, child process cannot catch SIGSTOP
//so, child process do the default action by SIGSTOP (stop the process until receive SIGCONT)
void sig_handler_sigstop(int signo) {
    if(signo == SIGSTOP) {
        printf("child: received SIGSTOP, suspend temporarily process..\n");
    }
}

//handle SIGCONT signal by child process
//child process receive SIGCONT, continue doing work
void sig_handler_sigcont(int signo) {
    if(signo == SIGCONT) {
        printf("child: received SIGCONT, continue doing my work\n");
    }
}

int main() {
    pid_t pid = fork();

    if(pid < 0) {
        perror("create process");
        exit(EXIT_FAILURE);
    }

    if(pid == 0) {
        printf("this is child process, pid = %d\n", pid);
        printf("child: doing some work..\n");

        //register sig_handler function for SIGSTOP & SIGCONT
        signal(SIGSTOP, sig_handler_sigstop); //register SIGSTOP, but cannot be catched by child process
        signal(SIGCONT, sig_handler_sigcont);
        printf("child: registered signal\n");

        for(int i = 0; i < 10; ++i) {
            printf("child: doing my work, i = %d\n", i);
            sleep(1);
        }

        printf("sleep 5 seconds..\n");
        sleep(5);
        printf("child: finished\n");
    }

    else {
        printf("this is parent process, pid = %d\n", pid);
        printf("parent: doing some work..\n");
        sleep(3);
        printf("parent: sending SIGSTOP signal to child..\n");
        kill(pid, SIGSTOP);
        printf("parent: sent SIGSTOP\n");
        
        for(int i = 0; i < 3; ++i) {
            printf("parent: doing my work, i = %d\n", i);
            sleep(1);
        }

        printf("parent: sending SIGCONT signal to child\n");
        kill(pid, SIGCONT);
        printf("parent: sent SIGCONT\n");

        wait(NULL);
        printf("parent: finished\n");
    }
}