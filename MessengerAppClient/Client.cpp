/* 
 * File:   Client.cpp
 * Author: rikysamuel
 * Modified: Aryya
 * Created on November 27, 2014, 6:10 PM
 */

#include "Client.h"

Client::Client() {
    buffer = new char[MAXBUF];
    port = 9000;
//    printf("constructor called\n");
}

Client::Client(const Client& orig) {
    this->buffer = orig.buffer;
    this->len = orig.len;
    this->port = orig.port;
    this->serv_addr = orig.serv_addr;
    this->server = orig.server;
    this->sock = orig.sock;
}

Client::~Client() {
//    printf("destructor called\n");
    delete [] buffer;
}

void Client::openTCPConnection() {
    if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) < 0){
        close(sock);
        printf("Cannot open socket\n");
        exit(1);
    }
}

void Client::reqConnect() {
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);
//    printf("%d\n",port);

    // connect ke server, jika error keluar
    if (connect(sock,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) exit(1);
//    printf("%d\n",ntohs(serv_addr.sin_port));
//    printf("%d.%d.%d.%d\n",
//    int(serv_addr.sin_addr.s_addr&0xFF),
//    int((serv_addr.sin_addr.s_addr&0xFF00)>>8),
//    int((serv_addr.sin_addr.s_addr&0xFF0000)>>16),
//    int((serv_addr.sin_addr.s_addr&0xFF000000)>>24));
    
    len = recv(sock, buffer , MAXBUF , 0);
    if (len >= 0){
        printf("Server Greetings: %s", buffer);
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

int Client::Write(char* message) {
//    len = write(sock,message,maxbuffer);
    
    printf("Your message: ");
    gets(message);
//    printf("%s\n",strerror(errno));
    
    bzero(buffer,MAXBUF);
    strcpy(buffer,message);
    len = send(sock,buffer,strlen(buffer),0);
//    printf("sock: %d\n",sock);
//    printf("pesan: %s\n",message);
//    printf("panjang: %i\n",(int)strlen(message));
    return len;
}

void Client::readServerReply() {
//    bzero(buffer,MAXBUF);
    len = recv(sock, buffer , MAXBUF , 0);
//    bzero(buffer,MAXBUF);
//    printf("%d\n",sock);
//    printf("%d\n",len);
//    printf("%d",(int)sizeof(buffer));
//    printf("%s\n",strerror(errno));
    if (len >= 0){
        printf("%s\n", buffer);
    }
}

int Client::signup(string username, string password){
	string text;
	text.append("--register--");
	text.append(username);
	text.append(password);
	text.append(";");
    char * writable = new char[text.size() + 1];
    copy(text.begin(), text.end(), writable);
    writable[text.size()] = '\0';
    Write(writable);
}

int Client::login(string username, string password){
	string text;
	text.append("--login--");
	text.append(username);
	text.append(password);
	text.append(";");
    char * writable = new char[text.size() + 1];
    copy(text.begin(), text.end(), writable);
    writable[text.size()] = '\0';
    Write(writable);
}

int Client::logout(){
	string text;
	text.append("--logout--:");
	text.append(getusername());
	text.append(";");
    char * writable = new char[text.size() + 1];
    copy(text.begin(), text.end(), writable);
    writable[text.size()] = '\0';
    Write(writable);}

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
        //signup(username, password);
        cout << "Sign up success" << endl;
    }
    else
    {
        cout << "Password dan konfirmasi password anda tidak sama" << endl;
    }

}

void Client::printLogin()
{
    string passwordCheck = "akhfa";
    cout << "username: ";
    getline(cin,username);
    cout << "password: ";
    getline(cin,password);
    if(password.compare(passwordCheck) == 0)
    {
        cout << "Success Login" << endl;
    }
    login(username, password);
}

void Client::setLoginStatus(bool status)
{
    LoggedIn = status;
}

bool Client::isLoggedIn()
{
    return LoggedIn;
}