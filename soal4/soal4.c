#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int status=0;

void* simpan_proses1(void *arg)
{
	system("ps -aux | head -n 11 | tail -n 10 > /home/maya/Documents/FolderProses1/SimpanProses1.txt");
}

void* simpan_proses2(void *arg)
{
	system("ps -aux | head -n 11 | tail -n 10 > /home/maya/Documents/FolderProses2/SimpanProses2.txt");
}

void *kompres1(void *arg)
{
	system("zip -mj /home/maya/Documents/FolderProses1/KompresProses1.zip /home/maya/Documents/FolderProses1/SimpanProses1.txt");
	status = 1;
}

void *kompres2(void *arg)
{
	system("zip -mj /home/maya/Documents/FolderProses2/KompresProses2.zip /home/maya/Documents/FolderProses2/SimpanProses2.txt");
	status = 1;
}

void * ekstrak1(void *arg)
{
	system("unzip /home/maya/Documents/FolderProses1/KompresProses1.zip -d /home/maya/Documents/FolderProses1");
}

void * ekstrak2(void *arg)
{
	system("unzip /home/maya/Documents/FolderProses2/KompresProses2.zip -d /home/maya/Documents/FolderProses2");
}

int main()
{
	pthread_t tid1[2];
	pthread_t tid2[2];
	pthread_t tid3[2];

	pthread_create(&tid1[0], NULL, simpan_proses1, NULL);
	pthread_create(&tid1[1], NULL, simpan_proses2, NULL);
	pthread_join(tid1[0], NULL);
	pthread_join(tid1[1], NULL);

	pthread_create(&tid2[0], NULL, kompres1, NULL);
	pthread_create(&tid2[1], NULL, kompres2, NULL);
	pthread_join(tid2[0], NULL);
	pthread_join(tid2[1], NULL);

	while(status!=1) {}
	printf("Menunggu 15 detik untuk mengekstrak kembali\n");
	sleep(15);

	pthread_create(&tid3[0], NULL, ekstrak1, NULL);
	pthread_create(&tid3[1], NULL, ekstrak2, NULL);
	pthread_join(tid3[0], NULL);
	pthread_join(tid3[1], NULL);

	return 0;
}
