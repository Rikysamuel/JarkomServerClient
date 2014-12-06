/*
TO DO function:

User:
    signup();
    login();
    logChat();
    viewChatFile();

Server:
    signup();
    login();
    listUser();
    viewChatFile();
    substrUser();
    substrPasswd();
*/

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Server{
    public:
        char data[100];
        ofstream ofile;
        ifstream ifile;
        void signup(){
            ofile.open("userlist.txt");
            ofile << "adwisatya adwisatyapwd";
            cout << "Pendaftaran berhasil";
        }
        int login(string username,string password){
            cout << password << getPassword(username);
            return password==getPassword(username);
        }

        string substrUser(string input){
            int delimitedPosition;
            delimitedPosition =  input.find(" ");
            return input.substr(0,delimitedPosition);
        }
        string substrPasswd(string input){
            int delimitedPosition;
            delimitedPosition =  input.find(" ");
            return input.substr(delimitedPosition+1,input.length());
        }
        string getPassword(string username){
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
        void listUser(){
            string line;
            ifile.open("userlist.txt");
            if(ifile.is_open()){
                while(getline(ifile,line)){
                    cout << substrUser(line) << endl;
                }
                ifile.close();
            }
        }
};

int main(){
    Server server;
    //server.signup();
    server.listUser();
    //cout << endl << "Password dari adwis2atya" << server.getPassword("adwis2atya")<<endl;
    //string manip = "aryya oke";
    //int delimiterPosotion = manip.find(" ");
    //cout << manip.substr(0, manip.find(" "));
    cout << server.login("asdasdasd","asdasdas") << endl;
    return 0;
}
