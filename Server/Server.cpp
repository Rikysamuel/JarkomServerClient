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
ofstream Server::ofile;
ifstream Server::ifile;
Group Server::group;

//int *Server::length = new int[MAXBUF];
//string *Server::status = new string[MAXBUF];
//string *Server::buffer = new string[MAXBUF];

Server::Server() {
    for(int i=0;i<MAXUSER;i++){
        users[i].setID(0);
        users[i].setLength(-1);
        users[i].setMessage("");
        users[i].setStatus("offline");
    }
    port = 9000;
    printf("Server Started.........\n");
    logger.init();
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

string Server::getUsernameFromMessage(string message){
    message = getMessage(message);
    int parse = message.find(':',0);
    return (message.substr(0,parse));
}

string Server::getPasswordFromMessage(string message){
    cout << "1. dalem fungsi getpassword: " << message << endl;
    message = getMessage(message);
    cout << "2. dalem fungsi getpassword: " << message << endl;
    int parse = message.find(':',0);
    return (message.substr(parse+1,message.length()-parse-1));
}

void Server::listUser(){
    string line;
    ifile.open("userlist.txt");
    if(ifile.is_open()){
        while(getline(ifile,line)){
            cout << substrUser(line) << endl;
        }
        ifile.close();
    }
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

    }
    
//    for(int t=0;t<=i;t++){
//        pthread_cancel(socket_thread[t]);
////        pthread_join(socket_thread[t],NULL);
//    }
//    for(int t=0;t<=i;t++){
//        pthread_join(socket_thread[t],NULL);
//    }
//            pthread_join(socket_thread[i],NULL);
//    pthread_exit(NULL);
}

void* Server::sendDataSocket(void* client_sock) {
    cout << "Thread sender created" << endl;
    
    int active = j;
    cout << "send on :" <<  active << endl;
    int c_sock = *((int*)client_sock);
    int cl_sock = *((int*)c_sock);
    char* buff; buff = new char[MAXBUF];
    
    cout << "Client Socket: " << users[active].getID() << endl;
    
    char* reply = (char*) ("\"Welcome to the MESSENGER\"\n");   //welcome message
    write(cl_sock , reply , strlen(reply)); //send welcome message
    
    /* Main loop */
    while(users[active].getStatus()=="online"){
        if(users[active].getLength()>=0){
            cout << "panjang :" << users[active].getLength() << endl;
            cout << "masuk" << endl;
            cout << "sender active: " << active << endl;
            cout << "pesan diterima: " << users[active].getMessage().length() << endl;
            strcpy(buff,(users[active].getMessage()+"\n").c_str());
            write(cl_sock , buff , strlen(buff));
            users[active].setLength(-1);
            users[active].setMessage("");
        }
    }
    
    cout << "Thread-sender for sock: " << users[active].getID() << " die..........." << endl;
    pthread_exit(NULL);
}


void *Server::recvDataSocket(void *client_sock) {
    cout << "Thread listener created" << endl;
    
    int active = j;
    cout << "recv on :" <<  active << endl;
    int c_sock = *((int*)client_sock);
    int cl_sock = *((int*)c_sock);
    char* buff; buff = new char[MAXBUF];
    bzero(buff,MAXBUF); int len; char *str;
    
    cout << "Client Socket: " << users[active].getID() << endl;
    cout << "status client "<< users[active].getID() << ": "<< users[active].getStatus() << endl;

    /* Main loop */
    while(users[active].getStatus()=="online"){
        
        cout << "lock listener called" << endl;
        users[active].setMessage("");
        bzero(buff,MAXBUF);
        len = recv(users[active].getID(), buff , MAXBUF , 0); //receive message from user
        printf("%s\n",buff);
        buff = strtok(buff,"\n\r");
        printf("habis di strtok: %s\n",buff);
        cout << "panjang: " << strlen(buff) << endl;
        users[active].setMessage((string)buff);
        
        cout << len << endl;
        
        if (len>=0){
            string dest = getDestination(users[active].getMessage());
            int id_dest = searchIDbyName(dest);
            
            if(users[active].getMessage()=="logout"){   //if user type "logout"
                cout << "masuk" << endl;
                closeClientSocket(users[active].getID());
                users[active].setStatus("offline");
                cout << "client "<< users[active].getID() << ": "<< users[active].getStatus() << endl;
                break;
            } else if(dest=="--login--"){
                int success = 0;
                listUser();
                string usr=getUsernameFromMessage(users[active].getMessage());
                string pass=getPasswordFromMessage(users[active].getMessage());
                cout << "usr: " << usr << endl;
                cout << "usr length: " << usr.length() << endl;
                cout << "pass: " << pass << endl;
                cout << "pass length: " << pass.length() << endl;
                success = login(usr,pass);
                cout << "success: " << success << endl;
                if (success>0){
                    // char * convert; convert = new char[32];
                    string msg = "true";
                    write(users[active].getID(),msg.c_str(),strlen(msg.c_str()));
                    users[active].setName(usr);
                }else{
                    users[active].setStatus("offline");
                    logger.loggedIn(usr);
                   // closeClientSocket(users[active].getID());
                }
            } else if (dest=="--register--"){
                string usr=getUsernameFromMessage(users[active].getMessage());
                string pass=getPasswordFromMessage(users[active].getMessage());
                int success = 0;
                success = signup(usr,pass);
                cout <<"success: " << success << endl;
                if (success>0){
                    string msg = "account succesfully created";
                    write(users[active].getID(),msg.c_str(),strlen(msg.c_str()));
                    users[active].setName(usr);
                    logger.terdaftar(usr);
                }
            }else if(dest=="--create--"){
                string grpname = getMessage(users[active].getMessage());
                cout << grpname << endl;
                cout << grpname.length() << endl;
                //Server::group.newGroup(grpname);
                group.newGroup(strdup(grpname.c_str()));
                write(users[active].getID(),"Group succesfully created",25);
            } else if(dest=="--join--"){
                string group=getUsernameFromMessage(users[active].getMessage());
                string name=getPasswordFromMessage(users[active].getMessage());
                cout << group;
                cout << name;
                /*
                char* membername;
                strcpy(membername, name.c_str());
                cout << groupname;
                cout << membername;
                */
                Server::group.addNewMemberGroup(group,name);
                
            }else if(dest=="--leave--"){
                string group=getUsernameFromMessage(users[active].getMessage());
                string name=getPasswordFromMessage(users[active].getMessage());
                char* groupname;
                strcpy(groupname, group.c_str());
                char* membername;
                strcpy(membername, name.c_str());
                Server::group.delMember(groupname,membername);
            }else{
                 cout << "dest: " << dest << endl;
                 cout << "len dest: " << dest.length() << endl;
                 cout << "id_dest" << id_dest << endl;
                 cout << "Message: " << getMessage(users[active].getMessage()) << endl;
                 cout << "Message len: " << getMessage(users[active].getMessage()).length() << endl;
                 cout << "test : " << active << endl;
                 users[id_dest].setMessage(getMessage(users[active].getMessage()));
                 cout << "test lawan: " << users[id_dest].getMessage()<< endl;
                 cout << "status: " << users[active].getStatus() << endl;
                 users[active].setLength(len);
                 users[id_dest].setLength(len);
            }
        }
        cout << "bufer[" << active << "] : " << users[active].getMessage().length() << endl;
//        cout << "unlock listener called" << endl;
    }
    
    cout << "Thread-listener for sock: " << active << " die..........." << endl;
    pthread_exit(NULL);
}

int Server::login(string username,string password){
    cout << "username: " << username << endl;
    cout << "username length: " << username.length() << endl;
    cout << "password: " << password << endl;
    cout << "password length: " << password.length() << endl;
    cout << getPassword(username) << endl;
    
    if(getPassword(username).find(password)==0){
        return 1;
    }else{

    return 0;
}
    
    // int comp=0;
    // int comp = password.compare(getPassword(username));
    // if(password==getPassword(username)){
    //     comp=1;
    // }else{
    //     comp=0;
    // }
    // cout << "comp: " << comp << endl;
    // if (comp==0){
    //     return 1;
    // } else{
    //     return 0;
    // }
}

string Server::getPassword(string username){
    string line;
    string password = "";
    int delimitedPosition;
    ifile.open("userlist.txt");
    if(ifile.is_open()){
        while(getline(ifile,line)){
            if(substrUser(line)==username){
                password = substrPasswd(line);
                false;
            }
        }
        ifile.close();
    }
    return password;
}

string Server::substrUser(string input){
    int delimitedPosition;
    delimitedPosition =  input.find(" ");
    return input.substr(0,delimitedPosition);
}
string Server::substrPasswd(string input){
    int delimitedPosition;
    delimitedPosition =  input.find(" ");
    return input.substr(delimitedPosition+1,input.length()-2);
}

int Server::searchIDbyName(string name) {
    int i = 0;
    for(i=0;i<MAXUSER;i++){
        cout << "online: " << users[i].getName() << endl;
        if(users[i].getName()==name){
            cout << "found i : i" << i << endl;
            return i;
        }
    }
}

int Server::signup(string username, string password){
    ofstream file;
    file.open("userlist.txt",ios::app);
    if(file.is_open())
    {
        file << username << " " << password << endl;
        file.close();
    }
    else
    {
        cout << "File tidak berhasil dibuka";
    }
    //ofile.open("userlist.txt", std::ios::app);
    //ofile << username << " " << password;
}

bool Server::cariUser(string username)
{
    string line;
    ifile.open("userlist.txt");
    if(ifile.is_open())
    {
        while(getline(ifile,line)){
            if(substrUser(line).compare(username) == 0){
                ifile.close();
                return true;
            }
        }
        ifile.close();
        return false;
    }
    else
    {
        cout << "gagal membuka file userlist.txt" << endl;
    }
}
