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
using namespace std;

class Group {
public:
    Group();
    Group(const Group& orig);
    virtual ~Group();
    void makeGroup();
    void newGroup(char* namaGroup); 
    void addNewMemberGroup(char* namaGroup, string namaUser);
    list<string> getDaftarUser(char* filename);
    void simpanGrupMessage(char* grupName, string waktu, string namaUser, string message);
    string getCurrentTime();
private:

};

#endif	/* GROUP_H */

