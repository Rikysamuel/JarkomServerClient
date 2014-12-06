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
    
    sprintf(buffer, "[%d-%d-%d %2d:%2d]", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, 
                    now->tm_hour, now->tm_min);
    
    return buffer;
}

void Logger::init()
{
    ofstream filelog;
    filelog.open("serverlog.txt", ios::app);
    if(filelog.is_open())
    {
        filelog << getCurrentTime() << " Server starts" << endl;
        filelog.close();
    }
    else
    {
        cout << "Gagal membuka file serverlog.txt" << endl;
    }
}


void Logger::loggedIn(string username)
{
    ofstream filelog;
    filelog.open("serverlog.txt", ios::app);
    if(filelog.is_open())
    {
        filelog << getCurrentTime() << " " << username << " logged in." << endl;
        filelog.close();
    }
    else
    {
        cout << "Gagal membuka file serverlog.txt" << endl;
    }
}

void Logger::createGroup(string namaGroup)
{
	ofstream filelog;
    filelog.open("serverlog.txt", ios::app);
    if(filelog.is_open())
    {
        filelog << getCurrentTime() << " " << namaGroup << " created successfully." << endl;
        filelog.close();
    }
    else
    {
        cout << "Gagal membuka file serverlog.txt" << endl;
    }
}

void Logger::join(string username, string namagrup)
{
    ofstream filelog;
    filelog.open("serverlog.txt", ios::app);
    if(filelog.is_open())
    {
        filelog << getCurrentTime() << " "  << username << " joined " << namagrup << endl;
        filelog.close();
    }
    else
    {
        cout << "Gagal membuka file serverlog.txt" << endl;
    }
}

void Logger::message(string namaPengirim, string tujuan)
{
    ofstream filelog;
    filelog.open("serverlog.txt", ios::app);
    if(filelog.is_open())
    {
        filelog << getCurrentTime() << " "  << namaPengirim << " message " << tujuan << endl;
        filelog.close();
    }
    else
    {
        cout << "Gagal membuka file serverlog.txt" << endl;
    }
}

void Logger::loggedOut(string username)
{
    ofstream filelog;
    filelog.open("serverlog.txt", ios::app);
    if(filelog.is_open())
    {
        filelog << getCurrentTime() << " " << username << " logged out." << endl;
        filelog.close();
    }
    else
    {
        cout << "Gagal membuka file serverlog.txt" << endl;
    }
}

void Logger::left(string username, string leftFromWhere)
{
    ofstream filelog;
    filelog.open("serverlog.txt", ios::app);
    if(filelog.is_open())
    {
        filelog << getCurrentTime() << " " << username << " left " << leftFromWhere << endl;
        filelog.close();
    }
    else
    {
        cout << "Gagal membuka file serverlog.txt" << endl;
    }
}

void Logger::terdaftar(string username)
{
    ofstream filelog;
    filelog.open("serverlog.txt", ios::app);
    if(filelog.is_open())
    {
        filelog << getCurrentTime() << " " << username << " telah mendaftar." << endl;
        filelog.close();
    }
    else
    {
        cout << "Gagal membuka file serverlog.txt" << endl;
    }
}
