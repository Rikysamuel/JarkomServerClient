/* 
 * File:   Server.cpp
 * Author: rikysamuel
 * 
 * Created on November 27, 2014, 5:30 PM
 */

#include "Server.h"

//initiate static member
int *Server::length = new int[MAXBUF];
string *Server::status = new string[MAXBUF];
string *Server::buffer = new string[MAXBUF];
pthread_mutex_t Server::lock = PTHREAD_MUTEX_INITIALIZER;

Server::Server() {
    port = 9000;
    printf("Server Started.........\n");
}

Server::Server(const Server& orig) {
    this->cli_addr = orig.cli_addr;
    this->client_sock = orig.client_sock;
    this->clilen = orig.clilen;
    this->port = orig.port;
    this->serv_addr = orig.serv_addr;
    this->sock = orig.sock;
}

Server::~Server() {
    printf("destructor called");
}

void Server::Listen(int maxuser) {
    listen(sock,maxuser); 
    printf("listen to %d user\n",maxuser);
}

void Server::bindServer() {
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; // semua address pada network interface
    serv_addr.sin_port = htons(port); // port 9000
    if (bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        close(sock);
        printf("Cannot bind socket\n");
        exit(1);
    } else{
        printf("Server binded\n");
    }
}

void Server::closeClientSocket(int sock_client) {
     close(sock_client);
     printf("socket %d closed\n",sock_client);
}

void Server::openTCPConnection() {
    if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) < 0){
        close(sock);
        printf("Cannot open socket\n");
        exit(1);
    } else{
        printf("Connection Opened\n");
        printf("Sock-id: %d\n",sock);
    }
}

void Server::setSocketReusable() {
    int yes = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("Cannot set option\n");
        exit(1);
    } else{
        printf("Socket set reusable\n");
    }
}

void Server::closeConnection() {
    close(sock);
    printf("socket closed");
}

string Server::getDestination(string message){
    int parse = message.find('|',0);
    return (message.substr(0,parse));
}

string Server::getMessage(string message){
    int parse = message.find('|',0);
    return (message.substr(parse+1,message.length()-parse-1));
}

void Server::createClientSocket() {
    clilen = sizeof(cli_addr);
    pthread_t socket_thread[10];
    int rc1, rc2; int i=0;
    
    while(1){
        printf("listening....................\n");
        client_sock = accept(sock, (struct sockaddr *) &cli_addr, &clilen);
        int *cli_sock = new int[1];
        *cli_sock = client_sock;
        
        Server::buffer[client_sock] = " ";
        Server::length[client_sock] = -1;
        Server::status[client_sock] = "online";
        
        cout << "Creating thread: " << i << endl;
        if((rc1=pthread_create(&socket_thread[i], NULL, &Server::recvDataSocket, &cli_sock))<0){
           cout << "Error" << endl;
        } i++;
        cout << &socket_thread[i] << " created" << endl;
        
        cout << "Creating thread: " << i << endl;
        if((rc2=pthread_create(&socket_thread[i], NULL, &Server::sendDataSocket, &cli_sock))<0){
           cout << "Error" << endl;
        } cout << &socket_thread[i] << " created" << endl;
        
//        pthread_join(socket_thread[i],NULL);
    }
}

void* Server::sendDataSocket(void* client_sock) {
    cout << "Thread sender created" << endl;
    
    int c_sock = *((int*)client_sock);
    int cl_sock = *((int*)c_sock);
    
    cout << "Client Socket: " << cl_sock << endl;
    
    char* reply = (char*) ("\"Welcome to the MESSENGER\"\n");   //welcome message
    write(cl_sock , reply , strlen(reply)); //send welcome message
    
    /* Main loop */
    while(status[cl_sock]=="online"){
        if(length[cl_sock]>=0){
//            pthread_mutex_lock(&lock);
            cout << "lock sender called" << endl;
            length[cl_sock] = -1;
//            pthread_mutex_unlock(&lock);
            cout << "unlock sender called" << endl;
        }
    }
    
    
    cout << "Thread-sender for sock: " << cl_sock << " die..........." << endl;
    pthread_exit(NULL);
}


void *Server::recvDataSocket(void *client_sock) {
    cout << "Thread listener created" << endl;
    
    int c_sock = *((int*)client_sock);
    int cl_sock = *((int*)c_sock);
    char* buff; buff = new char[MAXBUF];
    bzero(buff,MAXBUF); int len;
    
    cout << "Client Socket: " << cl_sock << endl;
    cout << "status client "<< cl_sock << ": "<< status[cl_sock] << endl;

    /* Main loop */
    while(status[cl_sock]=="online"){
        
        cout << "lock listener called" << endl;
        buffer[cl_sock] = "";
        bzero(buff,MAXBUF);
        len = recv(cl_sock, buff , MAXBUF , 0); //receive message from user
        buffer[cl_sock] = (string)buff;
        buffer[cl_sock] = buffer[cl_sock].substr(0,buffer[cl_sock].length()-2); //delete "\n" character
        cout << len << endl;
        
        if (len>=0){
           if(buffer[cl_sock]=="logout"){   //if user type "logout"
               cout << "masuk" << endl;
                closeClientSocket(cl_sock);
                status[cl_sock]="offline";
                cout << "client "<< cl_sock << ": "<< Server::status[cl_sock] << endl;
                break;
           } else if(getDestination(buffer[cl_sock])=="--login--"){
               
           } else if (getDestination(buffer[cl_sock])=="--register--"){
               
           } else{
                cout << "dest: " << getDestination(buffer[cl_sock]) << endl;
                cout << "Message: " << getMessage(buffer[cl_sock]) << endl;
                cout << "Message len: " << getMessage(buffer[cl_sock]).length() << endl;
           }
           length[cl_sock] = len;
        }
        cout << "bufer[" << cl_sock << "] : " << buffer[cl_sock].length() << endl;
        cout << "unlock listener called" << endl;
    }
    
    cout << "Thread-listener for sock: " << cl_sock << " die..........." << endl;
    pthread_exit(NULL);
}
