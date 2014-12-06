/* 
 * File:   main.cpp
 * Author: rikysamuel
 *
 * Created on November 27, 2014, 5:29 PM
 */

#include <cstdlib>
#include <iostream>
#include "Server.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Server *serv = new Server();
    int n =1;
    serv->openTCPConnection();
    serv->setSocketReusable();
    serv->bindServer();
    serv->Listen();
    while(1){
        serv->createClientSocket();
    }
    return 0;
}

