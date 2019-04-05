#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <pthread.h>

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}



int main(){
key_t key = 4321;
int *shopstock;
int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
shopstock = shmat(shmid, NULL, 0);

    while(1){
        printf("Shop\n");
        printf("Food stock : %d\n",*shopstock);
        printf("Choices\n1. Restock\n2. Exit\n");
        char key;
        key = getch();
        int k = key;
        if(k == 49){
            *shopstock+=1;
        }
        else if(k == 50){
            break;
        }

    }



    return 0;
}