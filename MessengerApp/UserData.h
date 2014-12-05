/* 
 * File:   UserData.h
 * Author: rikysamuel
 *
 * Created on December 5, 2014, 11:02 PM
 */

#ifndef USERDATA_H
#define	USERDATA_H

#include <string>
#include <iostream>
using namespace std;

class UserData {
public:
    UserData();
    UserData(const UserData& orig);
    virtual ~UserData();
    int getLength();
    void setLength(int length);
    int getID();
    void setID(int sock_id);
    string getStatus();
    void setStatus(string status);
    string getMessage();
    void setMessage(string inbox);
private:
    int length;
    int sock_id;
    string status;
    string message;
};

#endif	/* USERDATA_H */

