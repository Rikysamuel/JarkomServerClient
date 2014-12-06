/* 
 * File:   Client.h
 * Author: rikysamuel
 * Modified: Aryya
 * Created on November 27, 2014, 6:10 PM
 */

#ifndef CLIENT_H
#define	CLIENT_H

#define MAXBUF 200
#include "AllInclude.h"
//#include <iostream>
//#include <cstdio>
//#include <sys/types.h>   // tipe data penting untuk sys/socket.h dan netinet/in.h
//#include <netinet/in.h>  // fungsi dan struct internet address
//#include <sys/socket.h>  // fungsi dan struct socket API
//#include <netdb.h>       // lookup domain/DNS hostname
//#include <unistd.h>
//#include <cstdlib>
//#include <errno.h>
//#include <cstring>
//#include <string>
//#include <fstream>

using namespace std;
class Client {
public:
    Client();
    Client(const Client& orig);
    ~Client();
    
    void openTCPConnection();
    void setServerAddress(char* serv_address);
    void reqConnect();
    int getSock();
    int Write();
    char* signup(string username,string password);
    char* login(string username, string password);
    char* logout();
    string getusername();
    void toLog(/*string msg,int type*/);
    void ConnectionHandler(char* msg);
    void sendMessage();
    void createGroup();
    void leaveGroup();
    static void* readServerReply(void* this_sock);
    static int status;
    
    /*Fungsi untuk memberikan perintah ke user*/
    void printSignUp();
    void printLogin();
    bool isLoggedIn();
    void setLoginStatus(bool status);
    
private:
    bool lock;
    string username;
    string password;
    string confirmPassword;
    bool LoggedIn; /* State untuk menunjukkan bahwa usernya sudah login atau belum */
    
    int sock;
    int port;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    static int len;
    static string buffer;
    static string inbox;
};

#endif	/* CLIENT_H */

