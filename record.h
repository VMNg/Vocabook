#include <string>
#ifndef RECORD_H
#define RECORD_H
using namespace std;
struct record{
    string name;
    string mean;
    string kind;
    string day_create;
    struct record* next; //must to know!!
};
#endif
