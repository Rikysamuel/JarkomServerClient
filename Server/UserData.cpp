/* 
 * File:   UserData.cpp
 * Author: rikysamuel
 * 
 * Created on December 5, 2014, 11:02 PM
 */

#include "UserData.h"

UserData::UserData() {
}

UserData::UserData(const UserData& orig) {
    this->message=orig.message;
    this->length=orig.length;
    this->sock_id=orig.sock_id;
    this->status=orig.status;
}

UserData::~UserData() {
}

string UserData::getMessage() {
    return message;
}

int UserData::getID() {
    return sock_id;
}

int UserData::getLength() {
    return length;
}

string UserData::getStatus() {
    return status;
}

void UserData::setMessage(string inbox) {
    this->message = inbox;
}

void UserData::setID(int sock_id) {
    this->sock_id = sock_id;
}

void UserData::setLength(int length) {
    this->length = length;
}

void UserData::setStatus(string status) {
    this->status = status;
}

string UserData::getName(){
    return username;
}

void UserData::setName(string name){
    this->username = name;
}