//
// Created by TairanLiu on 24-12-18.
//
#include "BlankQ.h"

/**
 * 选择提示单词还是释义
 * @param i 用户ID
 */
void BlankQ::chooseWay(int i) {
    string input;
    int choice;
    do {
        cout << "输入提示方式" << endl;
        cout << "1.提示释义，选择单词" << endl;
        cout << "2.提示单词，选择释义" << endl;
        cout << "0.返回" << endl;
        getline(cin, input);
        choice = stoi(input);
        switch (choice) {
            case 1:
                operateWordQ(i);
                choice = 0;
                break;
            case 2:
                operateMeaningQ(i);
                choice=0;
                break;
            case 0:
                break;
            default:
                cout << "输入正确的数字" << endl;
                choice=1;
                break;
        }
    } while (choice);
}

/**
 * 录入是单词的具体操作
 * @param userId 用户ID
 */
void BlankQ::operateWordQ(int userId) {
    int tscore = 0;
    Customer users[MAX];
    for (int i = 1; i < 11; ++i) {
        cout << "第" << i << "题" << endl;
        //是否回答正确
        int iAIR = wordBlankQ(userId);
        //如果正确
        if (iAIR) {
            tscore += 10;
        } else {
            tscore -= 10;
        }
        operateScore(iAIR, userId);

    }

    if (tscore <= 20) {
        cout << "此次考核不合格，请继续练习" << endl;
        char filePath[MAX] = "../../resource/users.txt";
        Login::ReadUsersInf(filePath, users);
    } else {
        cout << "考核成功，继续努力" << endl;
    }
    QModel::review(userId);
}

/**
 * 单词填空题，并录入错题本
 * @param userId 用户ID
 * @return 正确的返回1，错误返回0
 */
int BlankQ::wordBlankQ(int userId) {
    bool ifAnswerIsRight = true;
    string input;
    Word wordbook[MAX];
    Word wrongWordBook[MAX];
    Customer users[MAX];

    char filename[MAX] = "../../resource/WordBook";
    char userFilename[MAX] = "../../resource/users.txt";
    string wrongWordFilename = "../../resource/wrongBook/";

    Login::ReadUsersInf(userFilename, users);
    int wordCount = AddWord::readFileReturnId(filename, wordbook);
    int wrongWordCount=QModel::readFromWrongBookReturnCount(wrongWordFilename + users[userId].getUsersName(),
                                                            wrongWordBook);

    //随机数
    random_device rd;
    mt19937 gen(rd());
    int maxI = wordCount - 1;
    //生成随机数表示选择考试的单词
    uniform_int_distribution<int> disChoice(0, maxI);

    //定义题目
    int wordNum = disChoice(gen);
    string blankAnswer;
    Word wordQ = wordbook[wordNum];
    blankAnswer=string (wordQ.getWord());

    cout << "题目：" << wordQ.getMeaning() << endl;
    cout << "输入你的答案" << endl;

    getline(cin, input);

    if (input == blankAnswer) {
        cout << "恭喜你，答对了" << endl;
    } else {
        cout << "很遗憾，你回答错误" << endl;
        string fullPath = "../../resource/wrongBook/";
        fullPath+=users[userId].getUsersName();
        //若已在错题本里面，不会重复录入
        for (int i = 0; i < wrongWordCount; ++i) {
            if (strcmp(wrongWordBook[i].getWord(),wordQ.getWord())==0){
                ifAnswerIsRight=false;
                return ifAnswerIsRight;
            }
        }

        //加入错题本
        QModel::toWrongBook(fullPath, wordQ.getWord(), wordQ);

        ifAnswerIsRight = false;
    }
    return ifAnswerIsRight;
}

/**
 * 录入是释义的具体操作
 * @param userId 用户ID
 */
void BlankQ::operateMeaningQ(int userId) {
    int tscore = 0;
    Customer users[MAX];
    for (int i = 1; i < 11; ++i) {
        cout << "第" << i << "题" << endl;
        //是否回答正确
        int iAIR = meaningBlankQ(userId);
        //如果正确
        if (iAIR) {
            tscore += 10;
        } else {
            tscore -= 10;
        }
        operateScore(iAIR, userId);

    }

    if (tscore <= 20) {
        cout << "此次考核不合格，请继续练习" << endl;
        char filePath[MAX] = "../../resource/users.txt";
        Login::ReadUsersInf(filePath, users);
    } else {
        cout << "考核成功，继续努力" << endl;
    }
    QModel::review(userId);
}
/**
 * 释义填空题，录入错题本
 * @param userId 用户ID
 * @return 正确返回1，错误返回0
 */
int BlankQ::meaningBlankQ(int userId) {
    bool ifAnswerIsRight = true;
    string input;
    Word wordbook[MAX];
    Word wrongWordBook[MAX];
    Customer users[MAX];

    char filename[MAX] = "../../resource/WordBook";
    char userFilename[MAX] = "../../resource/users.txt";
    string wrongWordFilename = "../../resource/wrongBook/";

    Login::ReadUsersInf(userFilename, users);
    int wordCount = AddWord::readFileReturnId(filename, wordbook);
    int wrongWordCount=QModel::readFromWrongBookReturnCount(wrongWordFilename + users[userId].getUsersName(),
                                                            wrongWordBook);

    //随机数
    random_device rd;
    mt19937 gen(rd());
    int maxI = wordCount - 1;
    //生成随机数表示选择考试的单词
    uniform_int_distribution<int> disChoice(0, maxI);

    //定义题目
    int wordNum = disChoice(gen);
    string blankAnswer;
    Word wordQ = wordbook[wordNum];
    blankAnswer=string (wordQ.getMeaning());

    cout << "题目：" << wordQ.getWord() << endl;
    cout << "输入你的答案" << endl;

    getline(cin, input);

    if (input == blankAnswer) {
        cout << "恭喜你，答对了" << endl;
    } else {
        cout << "很遗憾，你回答错误" << endl;
        string fullPath = "../../resource/wrongBook/";
        fullPath+=users[userId].getUsersName();
        //若已在错题本里面，不会重复录入
        for (int i = 0; i < wrongWordCount; ++i) {
            if (strcmp(wrongWordBook[i].getWord(),wordQ.getWord())==0){
                ifAnswerIsRight=false;
                return ifAnswerIsRight;
            }
        }

        //加入错题本
        QModel::toWrongBook(fullPath, wordQ.getWord(), wordQ);

        ifAnswerIsRight = false;
    }
    return ifAnswerIsRight;
}

/**
 * 写入分数至文本
 * @param ifAnswerIsRight 回答是否正确
 * @param i 用户ID
 */
void BlankQ::operateScore(int ifAnswerIsRight, int i) {
    Customer users[MAX];
    int score;
    char filePath[MAX] = "../../resource/users.txt";

    int userCount=Login::ReadUsersInf(filePath, users);
    //如果正确
    if (ifAnswerIsRight) {
        score = users[i].getTotalScore();
        score += 10;
        users[i].setScore(score);
        QModel::changeUserScore("../../resource/users.txt",users,userCount);
    } else {
        score = users[i].getTotalScore();
        score -= 10;
        users[i].setScore(score);
        QModel::changeUserScore("../../resource/users.txt",users,userCount);
    }
}