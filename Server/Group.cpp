/* 
 * File:   Group.cpp
 * Author: akhfa
 * 
 * Created on December 3, 2014, 10:01 AM
 */

#include "Group.h"

Group::Group() {
}

Group::Group(const Group& orig) {
}

Group::~Group() {
}

void Group::newGroup(string namaGroup)
{
    ofstream file;
    file.open("f.txt");
    file.close();
}

void Group::addNewMemberGroup(char* namaGroup, string namaUser)
{
    ofstream file;
    file.open(namaGroup,ios::app);
    if(file.is_open())
    {
        file << namaUser << endl;
        file.close();
    }
    else
    {
        cout << "File tidak berhasil dibuka";
    }
}

void Group::delMember(char* namaGroup, string namaUser){
    cout << "sudah dihapust api dummy doang";
}
list<string> Group::getDaftarUser(char* filename)
{
    ifstream file;
    string user;
    list <string> daftarUser;
    file.open(filename);
    if(file.is_open())
    {
        while(getline(file,user))
        {
            daftarUser.push_back(user);
        }
    }
    return daftarUser;
}

void Group::simpanGrupMessage(char* grupName, string waktu, string namaUser, string message)
{
    ofstream file;
    file.open(grupName,ios::app);
//    string line;
    if(file.is_open())
    {
        file << waktu << " : " << namaUser << " : " << message << endl;
        file.close();
    }
}
string Group::getCurrentTime()
{
//    time_t t = time(0);   // get time now
//    struct tm * now = localtime( & t );
//    char buffer[50];
//    int i;
//
//    itoa(now->tm_year + 1900,buffer, 10);
//    string date;
//    date.append(buffer);
//    date.append("-");
//    
//    itoa(now->tm_mon + 1, buffer, 10);
//    date.append(buffer);
//    date.append("-");
//    
//    itoa(now->tm_mday,buffer, 10);
//    date.append(buffer);
//    date.append(" | ");
//
//    itoa(now->tm_hour, buffer, 10);
//    date.append(buffer);
//    date.append(":");
//    
//    itoa(now->tm_min, buffer, 10);
//    date.append(buffer);
//    date.append(":");
//    
//    itoa(now->tm_sec, buffer, 10);
//    date.append(buffer);
//    
//    return date;
}