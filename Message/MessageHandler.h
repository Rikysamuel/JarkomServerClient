/* 
 * File:   MessageHandler.h
 * Author: rikysamuel
 *
 * Created on December 4, 2014, 10:19 PM
 */

#include <iostream>
#include <string>
using namespace std;

#ifndef MESSAGEHANDLER_H
#define	MESSAGEHANDLER_H

class MessageHandler {
public:
    MessageHandler();
    MessageHandler(const MessageHandler& orig);
    virtual ~MessageHandler();
    string GetMessage() const;
    void SetMessage(string message);
    string getDest() const;
    void setDest();
    
    
    string getDestination();
    string getParseMessage();
    
private:
    string message;
    string destination;
};

#endif	/* MESSAGEHANDLER_H */

