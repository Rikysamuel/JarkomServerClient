/*
Author: adwisatya
Purpose: to sort log of chat in server or client based on time
Category: container
*/
#include "Objek.h"
Objek::Objek() {
     message = "";
     priority = 0;
}
Objek::Objek(int p,string n) {
     message = n;
     priority = p;
}

string Objek::getmessage() const {
    return message;
}
long Objek::getpriority() const {
    return priority;
}


