#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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

int main(){
    string username ="aryya2";
    ifstream ifile;
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
    cout << username.compare("aryya2");
    cout << password;
}

