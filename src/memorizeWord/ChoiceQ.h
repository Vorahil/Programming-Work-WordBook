//
// Created by TairanLiu on 24-12-18.
//

#ifndef PROGRAMMING_CHOICEQ_H
#define PROGRAMMING_CHOICEQ_H
#include "QModel.h"

class ChoiceQ{
public:
    static void operateWordQ(int userId);
    static void operateMeaningQ(int userId);
    static void chooseWay(int i);
    static int wordChoiceQ(int userId);
    static int meaningChoiceQ(int userId);
    static void operateScore(int ifAnswerIsRight, int i);
};
#endif //PROGRAMMING_CHOICEQ_H
