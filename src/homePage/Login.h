//
// Created by TairanLiu on 24-12-17.
//
#include "iostream"
#ifndef PROGRAMMING_LOGIN_H
#define PROGRAMMING_LOGIN_H
#include "../entity/Customer.h"
#include "cstring"
using namespace std;
class Login{
private:
    char filename[MAX];
public:
    static int getUserIndex();
    static int ReadUsersInf(char* fname,Customer Inf[]);
};
#endif //PROGRAMMING_LOGIN_H
