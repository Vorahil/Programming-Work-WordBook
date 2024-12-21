//
// Created by TairanLiu on 24-12-17.
//

#ifndef PROGRAMMING_REGISTER_H
#define PROGRAMMING_REGISTER_H
#include "iostream"
#include "Login.h"
#include "filesystem"
using namespace std;
class Register{
public:
 static int registerUserReturnIndex();
private:
 static void createFolder(const string& basePath, const string& newFolderName);
};
#endif //PROGRAMMING_REGISTER_H
