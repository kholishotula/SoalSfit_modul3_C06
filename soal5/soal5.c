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


int hunger,hygiene,health,foodstock;
int battle = 0; int bathtime,bathstatus;
int enemyhp, enemyatt = 20, myatt = 20;

void showstandby(){
    printf("Standby Mode\n");
    printf("Health : %d\n",health);
    printf("Hunger : %d\n",hunger);
    printf("Hygiene : %d\n",hygiene);
    printf("Food left : %d\n",foodstock);
    printf("Bath will be ready in %ds\n",bathtime);
    printf("Choices\n1. Eat\n2. Bath\n3. Battle\n4. Shop\n5. Exit\n6. Refresh\n");
}
void showbattle(){
    printf("Battle Mode\n");
    printf("Monster's Health : %d\n", health);
    printf("Enemy's Health : %d\n",enemyhp);
    printf("Choices\n1. Attack\n2. Run\n");
}

void showshop(int sstock){
    printf("Shop Mode\n");
    printf("Shop food stock : %d\n",sstock);
    printf("Your food stock : %d\n",foodstock);
    printf("Choices\n1. Buy\n2. Back\n");

}
void* regenHealth(void* arg){
while(1){
    if(battle == 1){
    }
    else {
        health+=5;
    }
    sleep(10);
}
}
void* reduceHygiene(void* arg){
while(1){
    if(battle == 1){
    }
    else {
        hygiene-=10;
    }
    sleep(30);
}
}
void* reduceHunger(void* arg){
while(1){
    if(battle == 1){
    }
    else {
        hunger-=5;
        if(hunger == 0){
            system("clear");
            printf("Monster's hunger level is 0, you lose this game.\n");
            exit(0);
        }
    }
    sleep(10);
}
}
void* bathCD(void* arg){
while(1){
    if(bathstatus==1){
        bathtime--;
        if(bathtime == 0)
        bathstatus = 0;
    }
    sleep(1);
}
}

int main(){
key_t key = 4321;
int *shopstock;
int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
shopstock = shmat(shmid, NULL, 0);


pthread_t t1,t2,t3,t4;
hunger = 200;
hygiene = 100;
health = 30;
foodstock = 5;
bathtime = 20; bathstatus = 0; *shopstock = 10;
system("clear");
showstandby();
pthread_create(&t1, NULL, reduceHunger, NULL);
pthread_create(&t2, NULL, reduceHygiene, NULL);
pthread_create(&t3, NULL, regenHealth, NULL);
pthread_create(&t4, NULL, bathCD, NULL);
while(1){
    char key; int k;
    key = getch();
    k = key;
    if(k == 49){
        if(foodstock>0){
            foodstock -=1;
            hunger+=15;
            system("clear");
            showstandby();
        }
        else{
            system("clear");
            printf("Your food stock is 0!!\n");
            sleep(1);
            system("clear");
            showstandby();
        }
    }
    else if(k == 50){
        if(bathstatus == 0){
        bathtime = 20;
        bathstatus = 1;
        hygiene += 30;
        system("clear");
        showstandby();
        }
        else{
        system("clear");
        showstandby();
        }
    }
    else if(k == 51){
        battle = 1;
        enemyhp = 100;
        system("clear");
        showbattle();
        while(1){
        key = getch();
        k = key;
        if(k == 49){
            if(enemyhp == 0){
                battle=0;
                system("clear");
                showstandby();
                break;
            }
            enemyhp = enemyhp - myatt;
            health = health - enemyatt;
            system("clear");
            showbattle();
            if(health <= 0){
                system("clear");
                printf("Monster's health level is 0, you lose this game.\n");
                exit(0);
            }

        }
        else if(k == 50){
            battle = 0;
            system("clear");
            showstandby();
            break;
        }
        }
    }
    else if(k == 52){
        system("clear");
        showshop(*shopstock);
        while(1){
        key = getch();
        k = key;
        if(k == 49){
            if(*shopstock == 0){
                system("clear");
                printf("Can't buy food, shop's food stock is 0!\n");
                sleep(2);
                system("clear");
                showshop(*shopstock);
            }
            else{
                foodstock+=1;
                *shopstock-=1;
                system("clear");
                showshop(*shopstock);
            }
        }
        else if(k == 50){
            system("clear");
            showstandby();
            break;
        }
        }
    }
    else if(k == 53){
        break;
    }
    else if(k == 54){
        system("clear");
        showstandby();
    }

}
    return 0;
}