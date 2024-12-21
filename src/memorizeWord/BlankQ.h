//
// Created by TairanLiu on 24-12-18.
//

#ifndef PROGRAMMING_BLANKQ_H
#define PROGRAMMING_BLANKQ_H
#include "QModel.h"

class BlankQ{
private:
    static void operateWordQ(int userId);
    static void operateMeaningQ(int userId);
    static int wordBlankQ(int userId);
    static int meaningBlankQ(int userId);
    static void operateScore(int ifAnswerIsRight, int i);
public:
    static void chooseWay(int i);
};
#endif //PROGRAMMING_BLANKQ_H
