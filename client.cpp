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
    struct sockaddr_in address; 
    int sock, valread; 
    string bye("bye");
    struct sockaddr_in serv_addr; 
   
    //tao socket
    sock = socket(AF_INET, SOCK_STREAM, 0); 
    
    memset(&serv_addr, '0', sizeof(serv_addr)); //??
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
    // Convert IPv4 from add to binary form in serv_addr
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)  
    { 
        cout<<"Invalid"<<endl; 
        return -1; 
    } 
    // connect
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    string mess_from_client;
    char buffer[255]; 
while(1){
    memset(buffer, 0, 255);
    cout<<endl<<"tin nhan den server: ";

    getline(cin, mess_from_client);
    send(sock , mess_from_client.c_str() , mess_from_client.size()+1 , 0 ); 
    if (mess_from_client == "bye")
        break;
    cout<<"from server: ";
    valread = recv(sock, buffer, 255, 0);
    cout<<buffer;
    };
close(sock);
return 0; 
}
