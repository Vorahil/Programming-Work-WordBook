//
// Created by TairanLiu on 24-12-18.
//

#include "ChoiceQ.h"
#include "../entity/Customer.h"
#include "../homePage/Login.h"

void ChoiceQ::chooseWay(int i) {
    string input;
    int choice;
    do{
        cout<<"输入提示方式"<<endl;
        cout<<"1.提示单词"<<endl;
        cout<<"2.提示释义"<<endl;
        cout<<"0.返回"<<endl;
        getline(cin, input);
        choice = stoi(input);
        switch (choice) {
            case 1:
                operateWordQ(i);
                choice=0;
                break;
            case 2:
                break;
            case 0:
                break;
            default:
                cout<<"输入正确的数字"<<endl;
                break;
        }
    }while (!choice);
}

//提示单词选择释义,并加入错题本
int ChoiceQ::wordChoiceQ() {
    bool ifAnswerIsRight= true;
    string input;
    Word wordbook[MAX];
    char filename[MAX] = "C:/CodeWork/C/Programming/resource/WordBook";
    char word[MAX], partOfSpeech[MAX], meaning[MAX];
    int wordCount = AddWord::readFileReturnId(filename, wordbook);

    //随机数
    random_device rd;
    mt19937 gen(rd());
    int max = wordCount-1;
    if (max<3){
        cout<<"单词过少，添加单词"<<endl;
        return -1;
    }
    //生成随机数表示选择的单词
    uniform_int_distribution<int> disChoice(0, max);
    //生成正确的选项
    uniform_int_distribution<int> disTrueChoice(0, 3);
    int numA = disChoice(gen);
    int numB;
    do {
        numB = disChoice(gen);
    } while (numB == numA);//B与A不同

    int numC;
    do {
        numC = disChoice(gen);
    } while (numC == numA || numC == numB);//C与A或B都不同

    int numD;
    do {
        numD = disChoice(gen);
    } while (numD == numA || numD == numB || numD == numC);//D与A或B或C都不同
    //正确选项
    int numT = disTrueChoice(gen);
    string answerChoice;
    switch (numT) {
        case 0:
            answerChoice="A";
            break;
        case 1:
            answerChoice="B";
            break;
        case 2:
            answerChoice="C";
            break;
        default:
            answerChoice="D";
            break;
    }

    Word T=wordbook[numT];
    Word A=wordbook[numA];
    Word B=wordbook[numB];
    Word C=wordbook[numC];
    Word D=wordbook[numD];
    cout<<"题目："<<T.getMeaning()<<endl;
    cout<<"A."<<A.getWord()<<endl;
    cout<<"B."<<B.getWord()<<endl;
    cout<<"C."<<C.getWord()<<endl;
    cout<<"D."<<D.getWord()<<endl;
    cout<<"输入你的选项"<<endl;

    getline(cin,input);
    if (input==answerChoice){
        cout<<"恭喜你，答对了"<<endl;
    } else{
        cout<<"很遗憾，你回答错误"<<endl;
        ifAnswerIsRight= false;
    }
    return ifAnswerIsRight;
}

//读取文件并写入分数
void ChoiceQ::operateWrong(int ifAnswerIsRight,int i){
    Customer users[MAX];
    int score;
    char filePath[MAX]="C:/CodeWork/C/Programming/resource/users.txt";
        int usersCount=Login::ReadUsersInf(filePath,users);
        //如果正确
        if (ifAnswerIsRight){
            score=users[i].getTotalScore();
            score+=10;
            users[i].setScore(score);
        }else{
            score=users[i].getTotalScore();
            score-=10;
            users[i].setScore(score);
        }
}

//单词具体操作
void ChoiceQ::operateWordQ(int userId) {
    int tscore = 0;
    Customer users[MAX];
    int userCount=0;
    for (int i = 1; i < 11; ++i) {
        cout<<"第"<<i<<"题"<<endl;
        int iAIR=wordChoiceQ();
        if (iAIR==-1){
            return ;
        } else{
            //如果正确
            if (iAIR){
                tscore+=10;
            }else{
                tscore-=10;
            }
            operateWrong(iAIR,userId);
        }

    }
    if(tscore<=20){
        cout<<"此次考核不合格，请继续练习"<<endl;
        char filePath[MAX]="C:/CodeWork/C/Programming/resource/users.txt";

    }else{
        cout<<"考核成功，继续努力"<<endl;
    }
}


