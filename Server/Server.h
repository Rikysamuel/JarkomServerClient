/* 
 * File:   Server.h
 * Author: rikysamuel
 *
 * Created on November 27, 2014, 5:30 PM
 */

#ifndef SERVER_H
#define	SERVER_H

#define MAXBUF 200
#define MAXUSER 10

#include <cstdio>
#include <sys/types.h>   // tipe data penting untuk sys/socket.h dan netinet/in.h
#include <netinet/in.h>  // fungsi dan struct internet address
#include <sys/socket.h>  // fungsi dan struct socket API
#include <netdb.h>       // lookup domain/DNS hostname
#include <unistd.h>
#include <cstdlib>
#include <errno.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include "UserData.h"
#include "Group.h"
using namespace std;

class Server {
public:
    Server();
    Server(const Server& orig);
    ~Server();
    
    void openTCPConnection();
    void setSocketReusable();
    void bindServer();
    void Listen();
    void createClientSocket();
    void closeConnection();
    
    static int signup(string username, string password);
    static int login(string username, string password);
    static string getPassword(string username);
    static string substrUser(string input);
    static string substrPasswd(string input);
    static string getDestination(string message);
    static string getMessage(string message);
    static string getUsernameFromMessage(string message);
    static string getPasswordFromMessage(string message);
    static void closeClientSocket(int sock_client);
    static void* recvDataSocket(void* client_sock);
    static void* sendDataSocket(void* client_sock);
    static void listUser();
    static int searchIDbyName(string name);
    static bool checkNameExist();
    
//    static int* length;
//    static string* status;
//    static string* buffer;
    static int j;
    static char data[MAXBUF];
    static ofstream ofile;
    static ifstream ifile;
    static UserData *users;
    static Group group;
    
    //function tambahan for client
    bool cariUser(string username);
    
private:
    int sock;
    int client_sock;
    socklen_t clilen;
    int port;
    struct sockaddr_in serv_addr, cli_addr;
};

#endif	/* SERVER_H */

