#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
int PORT = 8080;
char hello[1024]; pthread_t thread1;

int sock = 0, valread;
void *konek (void *arg){

struct sockaddr_in address;
struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
    }

    while(1){
    char buffer[1024] = {0};
    scanf("%s",hello);
    send(sock , hello , strlen(hello) , 0 );
    if(strcmp(hello,"beli")==0){
    int valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );

    }
    else if(strcmp(hello,"bubar")==0){
    break;
    }
    }
}
  
int main(int argc, char const *argv[]) {

        printf("insert port : \n1.Penjual(8080)\n2.Pembeli(8081)\n");
        int x; scanf("%d",&x);
        PORT = x;
        pthread_create(&thread1, NULL, konek, NULL);
        pthread_join(thread1,NULL);

    return 0;
}