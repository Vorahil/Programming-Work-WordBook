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
using namespace std;
class QModel{
private:

public:
    static void questionChoose(int i);
    static void toWrongBook(string fullPath, string filenamePath,Word word);
    static int readFromWrongBookReturnCount(const filesystem::path &dirPath, Word words[])
};
#endif //PROGRAMMING_QMODEL_H
