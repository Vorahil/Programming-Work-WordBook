//
// Created by TairanLiu on 24-12-18.
//

#ifndef PROGRAMMING_CHOICEQ_H
#define PROGRAMMING_CHOICEQ_H
#include "QModel.h"

class ChoiceQ{
public:
    static void chooseWay(int i);
private:
    static void operateWordQ(int userId);
    static void operateMeaningQ(int userId);
    static int wordChoiceQ(int userId);
    static int meaningChoiceQ(int userId);
    static void operateScore(int ifAnswerIsRight, int i);
};
#endif //PROGRAMMING_CHOICEQ_H
