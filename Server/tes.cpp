#include <string>
#include <iostream>
#include <fstream>
using namespace std;

string substrUser(string input){
    int delimitedPosition;
    delimitedPosition =  input.find(" ");
    return input.substr(0,delimitedPosition);
}
string substrPasswd(string input){
    int delimitedPosition;
    delimitedPosition =  input.find(" ");
    return input.substr(delimitedPosition,input.length());
}

int main(){
    ifstream ifile;
    string username="a";
    string line;
    string password = "";
    int delimitedPosition;
    ifile.open("userlist.txt");
    if(ifile.is_open()){
        while(getline(ifile,line)){
            if(substrUser(line)==username){
                password = substrPasswd(line);
                cout << substrPasswd(line) << ":" << substrUser(line) << endl;
                false;
            }
        }
        ifile.close();
    }
    cout << password << endl;
    return 0;
}