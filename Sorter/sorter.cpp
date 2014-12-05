/*
Author: adwisatya
Purpose: to sort log of chat in server or client based on time
Category: main
*/
#include "Objek.h"
bool operator<(const Objek &a, const Objek &b)
{
    return a.getpriority() > b.getpriority();
}
int main(){
    priority_queue<Objek> qObjek;
    ifstream ifile;
    ofstream fon;
    string line;
    int delimitedPosition;

    ifile.open("log.txt");
    if(ifile.is_open()){
        while(getline(ifile,line)){
                delimitedPosition = line.find(" ");
                qObjek.push(Objek(atol(line.substr(0,delimitedPosition).c_str()),line.substr(delimitedPosition+1,line.size())));
                //cout << line.substr(0,delimitedPosition);
            }
        }
        ifile.close();

    while(!qObjek.empty()){
        cout << qObjek.top().getpriority() << " " << qObjek.top().getmessage() << endl;
        qObjek.pop();
    }

    return 0;
}
