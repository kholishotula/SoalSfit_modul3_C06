#include <stdio.h>
#include <sys/socket.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define PORT 8080
int flag = 1;
void* tampilstok (void* arg){
key_t key = 1234;
int *value; 

int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
value = shmat(shmid, NULL, 0);
while(1){
    if(flag == 0)
    break;

    printf("stok : %d\n",*value);
    sleep(5);
}
}
int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
key_t key = 1234;
int *value;

int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
value = shmat(shmid, NULL, 0);
*value = 10;
pthread_t t;
pthread_create(&t, NULL, tampilstok, NULL);
while(1){
    char buffer[1024] = {0};
    valread = read( new_socket , buffer, 1024);
    if(strcmp(buffer,"tambah")==0){
        *value = *value+1;
        printf("%d\n", *value);
        
    }
   else  if(strcmp(buffer,"bubar")==0){
        printf("cao\n");
        flag = 0;
        break;
    }
}
    //send(new_socket , hello , strlen(hello) , 0 );
    return 0;
}
