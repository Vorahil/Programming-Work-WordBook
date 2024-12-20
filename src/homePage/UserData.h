//
// Created by TairanLiu on 24-12-20.
//

#ifndef PROGRAMMING_USERDATA_H
#define PROGRAMMING_USERDATA_H
#include "Login.h"
#include "../memorizeWord/QModel.h"
class UserData{
private:
    static int changeClockTime(string filePath, Customer users[], int userCount);
public:
    static void checkScore(int userId);
    static void checkWrongBook(int userId);
    static void clock(int userId);
};
#endif //PROGRAMMING_USERDATA_H
