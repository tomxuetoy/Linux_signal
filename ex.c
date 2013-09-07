// Code comes from link: http://blog.csdn.net/zhangjingyangguang/article/details/6155119
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
 
static void pr_mask(const char * string) {
    sigset_t procmask;
 
    sigprocmask(SIG_SETMASK, NULL, &procmask);
 
    printf("%s: \n", string);
    if(sigismember(&procmask, SIGINT))
        printf("SIGINT \n");
    if(sigismember(&procmask, SIGUSR1))
        printf("SIGUSR1 \n");
    if(sigismember(&procmask, SIGUSR2))
        printf("SIGUSR2 \n");
    if(sigismember(&procmask, SIGTERM))
        printf("SIGTERM \n");
    if(sigismember(&procmask, SIGQUIT))
        printf("SIGQUIT \n");
}
 
static void sigusr(int signum)
{
    pr_mask("int sigusr");
 
    if(signum == SIGUSR1)
        printf("SIGUSR1 received \n");
    else if(signum == SIGUSR2)
        printf("SIGUSR2 received \n");
    else
        printf("signal %d received \n", signum);
}
 
int main(void)
{
    if(signal(SIGUSR1, sigusr) == SIG_ERR) {
        printf("error catching SIGUSR1 \n");
        exit(1);
    }
    else{
        printf("catching SIGUSR1 \n");
    }
 
    if(signal(SIGUSR2, SIG_IGN) == SIG_ERR) {
        printf("error ignoring SIGUSR2 \n");
        exit(1);
    }
    else{
        printf("ignoring SIGUSR2 \n");
    }
 
    if(signal(SIGINT, SIG_DFL) == SIG_ERR) {
        printf("error setting SIGINT to default \n");
        exit(1);
    }
    else{
        printf("setting SIGINT to default \n");
    }
 
    while(1)
        pause();    // pause()会令目前的进程暂停（进入睡眠状态），直到被信号(signal)所中断
 
    exit(0);
}
