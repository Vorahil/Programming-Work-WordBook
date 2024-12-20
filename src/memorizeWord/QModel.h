//
// Created by TairanLiu on 24-12-18.
//

#ifndef PROGRAMMING_QMODEL_H
#define PROGRAMMING_QMODEL_H
#include "../entity/Word.h"
#include "iostream"
#include "string"
#include "ChoiceQ.h"
#include "BlankQ.h"
#include "../wordOperator/AddWord.h"
#include "random"
#include "../entity/Word.h"
#include "../entity/Customer.h"
#include "../homePage/Login.h"
using namespace std;
class QModel{
private:
    static void reviewWord(int userId);
public:
    static void questionChoose(int i);
    static int toWrongBook(string fullPath, string filenamePath,Word word);
    static int readFromWrongBookReturnCount(const filesystem::path &dirPath, Word words[]);
    static void review(int userId);
    static int changeUserScore(string filePath,Customer users[],int userCount);
};
#endif //PROGRAMMING_QMODEL_H
