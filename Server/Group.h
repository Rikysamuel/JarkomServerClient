/* 
 * File:   Group.h
 * Author: akhfa
 *
 * Created on December 3, 2014, 10:01 AM
 */

#ifndef GROUP_H
#define	GROUP_H

#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
using namespace std;

class Group {
public:
    std::vector<string> userList;
    Group();
    Group(const Group& orig);
    virtual ~Group();
    void newGroup(char* namaGroup); 
    void addNewMemberGroup(char* namaGroup, string namaUser);
    list<string> getDaftarUser(char* filename);
    void simpanGrupMessage(char* grupName, string waktu, string namaUser, string message);
    string getCurrentTime();
    void delMember(char* namaGroup,string namaUser);
private:

};

#endif	/* GROUP_H */

