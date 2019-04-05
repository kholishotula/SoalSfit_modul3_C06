#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
 
int WakeUp_Status;
int Spirit_Status;
int cmd;
int count_wakeup;
int count_sleep;

void* All_Status(void *arg)
{
	while(1) {
		while(cmd != 1){}

		printf("Agmal WakeUp_Status = %d\n", WakeUp_Status);
		printf("Iraj Spirit_Status = %d\n", Spirit_Status);

		cmd = 0;
	}
}

void* Bangun(void *arg)
{
	while(1) {
		if(WakeUp_Status >= 100) {
                        printf("Agmal Terbangun, mereka bangun pagi dan berolahraga\n");
                        exit(EXIT_SUCCESS);
                }

		while(cmd != 2){}

		WakeUp_Status += 15;

		cmd = 0;
	}
}

void* Tidur(void *arg)
{
	while(1) {
                if(Spirit_Status <= 0) {
                        printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
                        exit(EXIT_SUCCESS);
                }

		while(cmd != 3){}

		Spirit_Status -= 20;

		cmd = 0;
	}
}
 
int main(void)
{
	pthread_t tid1, tid2, tid3;
	cmd = 0;
	WakeUp_Status = 0;
	Spirit_Status = 100;
	count_wakeup = 0;
	count_sleep = 0;
	char command[100];

	pthread_create(&(tid1), NULL, All_Status, NULL);
	pthread_create(&(tid2), NULL, Bangun, NULL);
	pthread_create(&(tid3), NULL, Tidur, NULL);

	while(1)
	{
		gets(command);

		if(strcmp(command, "All Status") == 0) {
			cmd = 1;
		}
		else if(strcmp(command, "Agmal Ayo Bangun") == 0) {
			if(count_sleep==3) {
				printf("Fitur Agmal Ayo Bangun disabled 10 s\n");
				sleep(10);
				continue;
			}
			count_wakeup+=1;
                        cmd = 2;
                }
		else if(strcmp(command, "Iraj Ayo Tidur") == 0) {
			if(count_wakeup==3) {
        	                printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
                	        sleep(10);
				continue;
			}
			count_sleep+=1;
                        cmd = 3;
                }
	}

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);

    return 0;
}
