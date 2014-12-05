/* 
 * File:   Server.cpp
 * Author: rikysamuel
 * 
 * Created on November 27, 2014, 5:30 PM
 */

#include "Server.h"

//initiate static member
UserData *Server::users = new UserData[MAXUSER];
int Server::j=-1;
//int *Server::length = new int[MAXBUF];
//string *Server::status = new string[MAXBUF];
//string *Server::buffer = new string[MAXBUF];

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
    this->users = orig.users;
}

Server::~Server() {
}

void Server::Listen() {
    listen(sock,MAXUSER); 
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
    }
}

void Server::closeClientSocket(int sock_client) {
     close(sock_client);
     printf("Client %d logged out\n",sock_client);
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
    pthread_t socket_thread[2*MAXUSER];
    int rc1, rc2; int i=0;
    
    while(1){
        printf("listening....................\n");
        client_sock = accept(sock, (struct sockaddr *) &cli_addr, &clilen);
        
        int *cli_sock = new int[1];
        *cli_sock = client_sock;
        cout << "client sock: " << &cli_sock << endl;
        
//        Server::buffer[client_sock] = " ";
//        Server::length[client_sock] = -1;
//        Server::status[client_sock] = "online";
        j++;
        Server::users[j].setID(client_sock);
        Server::users[j].setStatus("online");
        Server::users[j].setMessage("");
        Server::users[j].setLength(-1);
        
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
    
    int active = j;
    int c_sock = *((int*)client_sock);
    int cl_sock = *((int*)c_sock);
    
    cout << "Client Socket: " << users[active].getID() << endl;
    
    char* reply = (char*) ("\"Welcome to the MESSENGER\"\n");   //welcome message
    write(cl_sock , reply , strlen(reply)); //send welcome message
    
    /* Main loop */
    while(users[active].getStatus()=="online"){
        if(users[active].getLength()>=0){
//            pthread_mutex_lock(&lock);
//            cout << "lock sender called" << endl;
            users[active].setLength(-1);
//            pthread_mutex_unlock(&lock);
//            cout << "unlock sender called" << endl;
        }
    }
    
    cout << "Thread-sender for sock: " << users[active].getID() << " die..........." << endl;
    pthread_exit(NULL);
}


void *Server::recvDataSocket(void *client_sock) {
    cout << "Thread listener created" << endl;
    
    int active = j;
    int c_sock = *((int*)client_sock);
    int cl_sock = *((int*)c_sock);
    char* buff; buff = new char[MAXBUF];
    bzero(buff,MAXBUF); int len;
    
    cout << "Client Socket: " << users[active].getID() << endl;
    cout << "status client "<< users[active].getID() << ": "<< users[active].getStatus() << endl;

    /* Main loop */
    while(users[active].getStatus()=="online"){
        
        cout << "lock listener called" << endl;
        users[active].setMessage("");
        bzero(buff,MAXBUF);
        len = recv(users[active].getID(), buff , MAXBUF , 0); //receive message from user
        printf("%s\n",buff);
        users[active].setMessage((string)buff);
        //        buffer[cl_sock] = buffer[cl_sock].substr(0,buffer[cl_sock].length()-2); //delete "\n" character
        cout << len << endl;
        
        if (len>=0){
           if(users[active].getMessage()=="logout"){   //if user type "logout"
               cout << "masuk" << endl;
                closeClientSocket(users[active].getID());
                users[active].setStatus("offline");
                cout << "client "<< users[active].getID() << ": "<< users[active].getStatus() << endl;
                break;
           } else if(getDestination(users[active].getMessage())=="--login--"){
               
           } else if (getDestination(users[active].getMessage())=="--register--"){
               
           } else{
                cout << "dest: " << getDestination(users[active].getMessage()) << endl;
                cout << "Message: " << getMessage(users[active].getMessage()) << endl;
                cout << "Message len: " << getMessage(users[active].getMessage()).length() << endl;
           }
           users[active].setLength(len);
        }
        cout << "bufer[" << active << "] : " << users[active].getMessage().length() << endl;
//        cout << "unlock listener called" << endl;
    }
    
    cout << "Thread-listener for sock: " << active << " die..........." << endl;
    pthread_exit(NULL);
}
