#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<string.h>
#include<string>
#define PORT 8080

using namespace std;
 
int main() 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address);  
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
    string mess_from_server;
    char buffer[255];    
    while(1){
memset(buffer, 0, 255);
    cout<<"from client: ";
    valread = recv(new_socket, buffer, 255, 0);
    
    cout<<buffer;
    if(strcmp(buffer,"bye") == 0)
        break;  
    cout<<endl<<"tin nhan den client: ";
    getline(cin, mess_from_server);
    send(new_socket, mess_from_server.c_str(), mess_from_server.size()+1, 0);
    };
    close(new_socket);
    return 0; 
}
