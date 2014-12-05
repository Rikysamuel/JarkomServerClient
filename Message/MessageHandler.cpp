/* 
 * File:   MessageHandler.cpp
 * Author: rikysamuel
 * 
 * Created on December 4, 2014, 10:19 PM
 */

#include "MessageHandler.h"

MessageHandler::MessageHandler() {
    message = new string();
}

MessageHandler::MessageHandler(const MessageHandler& orig) {
    this->message = orig.message;
}

MessageHandler::~MessageHandler() {
}

string MessageHandler::GetMessage() const {
    return message;
}

void MessageHandler::SetMessage(string message) {
    this->message = message;
}

string MessageHandler::getDest() const {
    return destination;
}

void MessageHandler::setDest(string destination) {
    this->destination = destination;
}


string MessageHandler::getDestination() {
    int parse = message.find("|");
    string dest = message.substr(0,parse);
    return dest;
}

string MessageHandler::getParseMessage() {
    int parse = message.find("|");
    int len = message.length() - parse;
    string msg = message.substr(parse,message.end());
    return msg;
}