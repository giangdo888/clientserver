#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <ctype.h>
#define PORT 8080 
int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char mess_from_client[225];
    char buffer[1024] = {0}; 
    char *hello = "Hello from server";
    int continu = 1;
    //tao socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    //gia tri cho bien dia chi
  
  
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; //bind the socket to all available interfaces
    address.sin_port = htons( PORT );  //gan cong la 8080   
    // bind 
    bind(server_fd, (struct sockaddr *)&address, addrlen);
   
    //listen, chi dinh socket lang nghe ket noi
    listen(server_fd, 1) ;
    
    //accept, chap nhan ket noi
    new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen);
    
   while(continu == 1){    
	    char str_cli_ip[INET_ADDRSTRLEN];
	    struct sockaddr_in* ip_client = (struct sockaddr_in*)&address;
	    inet_ntop(AF_INET, &ip_client->sin_addr, str_cli_ip, INET_ADDRSTRLEN);
	    printf("ipclient: %s\n", str_cli_ip );
	    char str_cli_port[INET_ADDRSTRLEN];
	    printf("port: %d\n", ntohs(ip_client->sin_port));
	    printf("Tin nhan tu client: \n");
	    //read, doc du lieu gan vao bien valread tra ve so byte ma no doc duoc
	    valread = read( new_socket, buffer, 1024);
	    //gan bien hello tra ve cho client la buffer
	    hello = &buffer;
	    printf("%s\n",buffer ); 
	    send(new_socket, hello, strlen(hello), 0 ); 
    }
    close(new_socket);
    return 0; 
} 
