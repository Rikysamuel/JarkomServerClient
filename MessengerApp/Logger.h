/* 
 * File:   Logger.h
 * Author: akhfa
 *
 * Created on December 5, 2014, 5:33 PM
 */

#ifndef LOGGER_H
#define	LOGGER_H

#include "AllInclude.h"
//#include <list>
//#include <string>
//#include <fstream>
//#include <iostream>
//#include <ctime>
//#include <stdio.h>
//#include <stdlib.h>

using namespace std;

class Logger {
public:
    Logger();
    Logger(const Logger& orig);
    virtual ~Logger();
    void init();
    string getCurrentTime();
    void loggedIn(string username);
    void join(string username, string namagrup);
    void message(string namaPengirim, string tujuan);
    void loggedOut(string username);
    void left(string username, string leftFromWhere);
    void terdaftar(string username);
private:
    
};

#endif	/* LOGGER_H */

