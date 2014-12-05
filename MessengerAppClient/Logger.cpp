/* 
 * File:   Logger.cpp
 * Author: akhfa
 * 
 * Created on December 5, 2014, 5:33 PM
 */

#include "Logger.h"
#include "AllInclude.h"

Logger::Logger() {
}

Logger::Logger(const Logger& orig) {
}

Logger::~Logger() {
}

string Logger::getCurrentTime()
{
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    char buffer[50];
    int i;
    
    string date;
    sprintf(buffer, "[%d-%d-%2d %2d:%2d]", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, 
                    now->tm_hour, now->tm_min);
    
    return date;
}

void Logger::init()
{
    ofstream filelog;
    filelog.open("serverlog.txt", ios::app);
    if(filelog.is_open())
    {
        filelog << getCurrentTime() << "Server starts" << endl;
        filelog.close();
    }
    else
    {
        cout << "Gagal membuka file serverlog.txt" << endl;
    }
}
