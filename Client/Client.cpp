/* 
 * File:   Client.cpp
 * Author: rikysamuel
 * Modified: Aryya
 * Created on November 27, 2014, 6:10 PM
 */

#include "Client.h"
#include <cstring>

int Client::status = 0;
string Client::buffer = new char[MAXBUF];
int Client::len = -1;

Client::Client() {
    port = 9000;
//    printf("constructor called\n");
}

Client::Client(const Client& orig) {
    this->buffer = orig.buffer;
    this->port = orig.port;
    this->serv_addr = orig.serv_addr;
    this->server = orig.server;
    this->sock = orig.sock;
}

Client::~Client() {
    
}

void Client::openTCPConnection() {
    if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) < 0){
        close(sock);
        printf("Cannot open socket\n");
        exit(1);
    }
}

void Client::reqConnect() {
    char* buff; buff = new char[MAXBUF];
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);
//    printf("%d\n",port);

    // connect ke server, jika error keluar
    if (connect(sock,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) exit(1);
    
    cout << "Server greetings: ";
    len = recv(sock, buff , MAXBUF , 0);
    if (len >= 0){
        printf("%s\n", buff);
    }
}

void Client::setServerAddress(char* serv_address) {
    server = gethostbyname(serv_address);
    if (server == NULL) {
        fprintf(stderr,"Host not found\n");
        exit(1);
    }
    printf("Connected to Server!\n");
}

int Client::Write() {
    char* buff; buff = new char[MAXBUF];
    bzero(buff,MAXBUF);
    strcpy(buff,buffer.c_str());
    len = send(sock,buff,strlen(buff),0);
    return len;
}

void* Client::readServerReply(void* this_sock) {
    int client_sock = *(int*)this_sock;
    int my_sock = *(int*)client_sock;
    
    char* buff;buff=new char[MAXBUF];
    while(status==0){
        len = recv(my_sock, buff , MAXBUF , 0);
        if(strcmp(buff,"true")){
            status = 1;
            cout << "status berubah jadi: " << status << endl;
            len = -1;
        }
    }
    while(status==1){
        len = recv(my_sock, buff , MAXBUF , 0);
        buffer = (string)buff;
        if (len >= 0){
            cout << "New Message received!"<< endl;
            len=-1;
            bzero(buff,MAXBUF);
        }
    }
    cout << "keluar...." << endl;
    pthread_exit(NULL);
}

void Client::openInbox(){
    cout << buffer << endl;
    buffer="";
}

char* Client::signup(string username, string password){
	string text;
	text.append("--register--");
        text.append("|");
	text.append(username);
    text.append(":");
	text.append(password);
    char * writable = new char[text.size() + 1];
    copy(text.begin(), text.end(), writable);
    writable[text.size()] = '\0';
    return writable;
}

char* Client::login(string username, string password){
	string text;
	text.append("--login--");
        text.append("|");
	text.append(username);
        text.append(":");
	text.append(password);
    char * writable = new char[text.size() + 1];
    copy(text.begin(), text.end(), writable);
    writable[text.size()] = '\0';
    return writable;
}

char* Client::logout(){
	string text;
	text.append("--logout--:");
	text.append(getusername());
	text.append(";");
    char * writable = new char[text.size() + 1];
    copy(text.begin(), text.end(), writable);
    writable[text.size()] = '\0';
    return writable;
}

void Client::sendMessage(){
    string username;
    string message;
    buffer="";
    printf("> username: ");
    getline(cin,username);
    printf("> message: ");
    getline(cin,message);
    username.append("|");
    username.append(message);
    buffer = username;
    Write();
}

void Client::createGroup(){
    string request = "--create--|";
    string groupname;
    buffer="";
    printf("> Group Name: ");
    getline(cin,groupname);
    request.append(groupname);
    buffer = request;
    cout << "test create group: " << buffer << endl;
    Write();
}

void Client::leaveGroup(){
    string request = "--leave--|";
    string groupname;buffer="";
    printf("> Group name:");
    getline(cin, groupname);
    request.append(groupname);
    buffer = request;
    cout << "test leave group" << buffer << endl;
    Write();
}
void Client::joinGroup(){
    string request = "--join--|";
    string groupname;
    buffer="";
    printf("> Group Name: ");
    getline(cin,groupname);
    request.append(groupname);
    request.append(":");
    request.append(getusername());
    buffer = request;
    cout << "test join group: " << buffer << endl;
    Write();
}

void Client::chatGroup(){
    string request = "--group--|";
    string groupname;buffer="";
    printf("> Chat to Group :");
    getline(cin, groupname);
    request.append(groupname);
    buffer = request;
    Write();
}

string Client::getusername(){
	return username;
}

void Client::toLog(){
	
    /*string namafile;
	namafile.append(getusername());
	namafile.append(".txt");
	ofstream outfile;
	outfile.open(namafile,ios_base::app);
	outfile << input;*/
}

/*Di bawah ini fungsi untuk print perintah ke user. Kalo bikin fungsi lagi, di atasnya aja ya...*/
void Client::printSignUp()
{
    cout << "Welcome to this chat application" << endl;
    cout << "Masukkan username baru\t: ";
    getline(cin, username);
    cout << "Masukkan password\t\t: ";
    getline(cin, password);
    cout << "Konfirmasi Password\t: ";
    getline (cin, confirmPassword);
    
    if(password.compare(confirmPassword) == 0)
    {
        char * buff; buff = new char[MAXBUF];
    
        strcpy(buff,signup(username, password));
        cout << (string)buff << endl;
        openTCPConnection();
        setServerAddress((char*)"127.0.0.1");
        reqConnect();
        ConnectionHandler(buff);
    }
    else
    {
        cout << "Password dan konfirmasi password anda tidak sama" << endl;
    }

}

void Client::printLogin()
{
    char * buff; buff = new char[MAXBUF];
//    string passwordCheck = "akhfa";
    cout << "username: ";
    getline(cin,username);
    cout << "password: ";
    getline(cin,password);
    
    strcpy(buff,login(username, password));
    cout << (string)buff << endl;
    openTCPConnection();
    setServerAddress((char*)"127.0.0.1");
    reqConnect();
    ConnectionHandler(buff);
//    len = send(sock,buff,strlen(buff),0);
//    len = -1;
//    bzero(buff,MAXBUF);
//    cout << len << endl;
//    cout << "buff: " << buff << endl;
//    cout << strlen(buff) << endl;
//    if (len>=0){
//        len = recv(sock, buff , MAXBUF , 0); //receive message from user
//        if (strcmp(buff,"true")==0){
//            cout << "yayyyyyyyyy" << endl;
//            setLoginStatus(true);
//        status = 1;
//        
////        cout << "req connect.........." << endl;
////        openTCPConnection();
////        setServerAddress((char*)"127.0.0.1");
////        reqConnect();
//        }
//    }
//    len=-1;
//    if(password.compare(passwordCheck) == 0)
//    {
//        cout << "Success Login" << endl;
//        
//    }
}

void Client::setLoginStatus(bool status)
{
    LoggedIn = status;
}

bool Client::isLoggedIn()
{
    return LoggedIn;
}

void Client::ConnectionHandler(char* buff){
    pthread_t client_thread;
    int rc; string input;
    
    int *cli_sock = new int[1];
        *cli_sock = sock;
    cout << "client sock: " << sock;
    
    cout << "Creating thread" << endl;
    if((rc=pthread_create(&client_thread, NULL, &Client::readServerReply, &cli_sock))<0){
       cout << "Error" << endl;
    }
    cout << "Thread created" << endl;
    
    len = send(sock,buff,strlen(buff),0);
    cout << status << endl;
    if (status==0){
        status=1;
    }
    while(buffer!="logout"){
        printf("> ");
        getline(cin,input);
        if (input=="message"){
            sendMessage();
            input="";
        }
        if (input=="logout"){
            buffer="logout";
        }
        if(input=="create"){
            createGroup();
        }
        if(input=="join"){
            joinGroup();
        if(input=="read"){
            openInbox();
            buffer="";
        }
        if(input=="group"){
            chatGroup();
        }
    }
    if (input=="logout"){
        cout << "die............" << endl;
        setLoginStatus(false);
        status = 0;
    }
            
//    pthread_cancel(client_thread);
//    pthread_join(client_thread,NULL);
//    pthread_exit(NULL);
}

int Client::getSock(){
    return sock;
}

void Client::saveMessage(char *namaFile, string from, string message)
{
	ofstream file;
	file.open(namaFile, ios::app);
	if(file.is_open())
	{
		file << getCurrentTime() << " " << from << ":" << message << endl;
	}
	else
	{
		cout << "gagal membuka file" << endl;
	}
}

string Client::getCurrentTime()
{
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    char buffer[50];
    int i;
    
    sprintf(buffer, "[%d-%d-%d %2d:%2d]", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, 
                    now->tm_hour, now->tm_min);
    
    return buffer;
}
