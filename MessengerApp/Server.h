/* 
 * File:   Server.h
 * Author: rikysamuel
 *
 * Created on November 27, 2014, 5:30 PM
 */

#ifndef SERVER_H
#define	SERVER_H

#define MAXBUF 200

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
#include <string>
using namespace std;

class Server {
public:
    Server();
    Server(const Server& orig);
    ~Server();
    
    void openTCPConnection();
    void setSocketReusable();
    void bindServer();
    void Listen(int maxuser);
    void createClientSocket();
    void closeConnection();
    
    static string getDestination(string message);
    static string getMessage(string message);
    static void closeClientSocket(int sock_client);
    static void* recvDataSocket(void* client_sock);
    static void* sendDataSocket(void* client_sock);
    
    static int* length;
    static string* status;
    static string* buffer;
    static pthread_mutex_t lock;
private:
    int sock;
    int client_sock;
    socklen_t clilen;
    int port;
    struct sockaddr_in serv_addr, cli_addr;
};

#endif	/* SERVER_H */

