/* 
 * File:   main.cpp
 * Author: rikysamuel
 *
 * Created on November 27, 2014, 7:41 PM
 */

#include <cstdlib>
#include "Client.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    string input;
    Client klien;
//    int rc;
//    pthread_t cli_thread;
    
    
    klien.setLoginStatus(false);
    while(input.compare("exit") != 0)
    {
        cout << klien.isLoggedIn() << endl;
        cout << "> ";
        if(!klien.isLoggedIn())
        {
            getline(cin,input);
            cout << input;

            /**
             * Untuk signup
             */
            if(input.compare("signup") == 0)
            {
               klien.printSignUp(); 
            }
            
            /**
             * Untuk login
             */
            else if(input.compare("login") == 0)
            {
                klien.printLogin();
                cout << "keluar login" << endl;
            }
            
            /* Jika commandnya message, create, or join tapi belum login */
            else if(input.find("message") != std::string::npos || input.find("create") != std::string::npos ||
                    input.find("join") != std::string::npos)
            {
                cout << "Silahkan login terlebih dahulu" << endl;
            }
        } else{
            cout << "req connect.........." << endl;
            klien.openTCPConnection();
            klien.setServerAddress((char*)"127.0.0.1");
            klien.reqConnect();
            klien.ConnectionHandler();
        }
        
    }
    
//    Client *client = new Client();
//    client->openTCPConnection();
//    client->setServerAddress((char*)"127.0.0.1");
//    client->reqConnect();
//    while(1){
//	    client->Write((char*) message);
//	    client->readServerReply();
//	}
    return 0;
}

