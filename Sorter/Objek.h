#ifndef OBJEK_H
#define OBJEK_H

#include <queue>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
using namespace std;

class Objek {
private:
  long priority;
  string message;
public:
  Objek();
  Objek(int p,string n);
  string getmessage() const;
  long getpriority() const;
};
#endif
