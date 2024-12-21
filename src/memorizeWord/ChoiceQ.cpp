//
// Created by TairanLiu on 24-12-18.
//

#include "ChoiceQ.h"

/**
 * 选择提示释义还是单词
 * @param i 用户ID
 */
void ChoiceQ::chooseWay(int i) {
    string input;
    int choice;
    do {
        cout << "输入提示方式" << endl;
        cout << "1.提示释义，选择单词" << endl;
        cout << "2.提示单词，选择释义" << endl;
        cout << "0.退出" << endl;
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
 * 单词选择题具体操作
 * @param userId 用户ID
 */
void ChoiceQ::operateWordQ(int userId) {
    int tscore = 0;
    Customer users[MAX];
    for (int i = 1; i < 11; ++i) {
        cout << "第" << i << "题" << endl;
        //是否回答正确
        int iAIR = wordChoiceQ(userId);
        if (iAIR == -1) {
            return;
        } else {
            //如果正确
            if (iAIR) {
                tscore += 10;
            } else {
                tscore -= 10;
            }
            operateScore(iAIR, userId);
        }
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
 * 单词选择题，并录入错题本
 * @param userId 用户ID
 * @return 正确的返回1，错误返回0
 */
int ChoiceQ::wordChoiceQ(int userId) {
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
    if (maxI < 3) {
        cout << "单词过少，添加单词" << endl;
        return -1;
    }
    //生成随机数表示选择的单词
    uniform_int_distribution<int> disChoice(0, maxI);
    //生成正确的选项
    uniform_int_distribution<int> disTrueChoice(0, 3);

    //定义选项
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
            answerChoice = "A";
            break;
        case 1:
            answerChoice = "B";
            break;
        case 2:
            answerChoice = "C";
            break;
        default:
            answerChoice = "D";
            break;
    }

    Word A = wordbook[numA];
    Word B = wordbook[numB];
    Word C = wordbook[numC];
    Word D = wordbook[numD];
    Word chooseWord[4]={A,B,C,D};
    Word T=chooseWord[numT];

    cout << "题目：" << T.getMeaning() << endl;
    cout << "A." << A.getWord() << endl;
    cout << "B." << B.getWord() << endl;
    cout << "C." << C.getWord() << endl;
    cout << "D." << D.getWord() << endl;
    cout << "输入你的选项" << endl;

    getline(cin, input);

    if (input == answerChoice) {
        cout << "恭喜你，答对了" << endl;
    } else {
        cout << "很遗憾，你回答错误" << endl;
        string fullPath = "../../resource/wrongBook/";
        fullPath+=users[userId].getUsersName();
        //若已在错题本里面，不会重复录入
        for (int i = 0; i < wrongWordCount; ++i) {
            if (strcmp(wrongWordBook[i].getWord(),T.getWord())==0){
                ifAnswerIsRight=false;
                return ifAnswerIsRight;
            }
        }

        //加入错题本
        QModel::toWrongBook(fullPath, T.getWord(), T);

        ifAnswerIsRight = false;
    }
    return ifAnswerIsRight;
}

/**
 *选项是释义的具体操作
 * @param userId 用户ID
 */
void ChoiceQ::operateMeaningQ(int userId) {
    int tscore = 0;
    Customer users[MAX];
    for (int i = 1; i < 11; ++i) {
        cout << "第" << i << "题" << endl;
        //是否回答正确
        int iAIR = meaningChoiceQ(userId);
        if (iAIR == -1) {
            return;
        } else {
            //如果正确
            if (iAIR) {
                tscore += 10;
            } else {
                tscore -= 10;
            }
            operateScore(iAIR, userId);
        }
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
 * 释义选择题，录入错题本
 * @param userId 用户ID
 * @return 正确返回1，错误返回0
 */
int ChoiceQ::meaningChoiceQ(int userId) {
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
    if (maxI < 3) {
        cout << "单词过少，添加单词" << endl;
        return -1;
    }
    //生成随机数表示选择的单词
    uniform_int_distribution<int> disChoice(0, maxI);
    //生成正确的选项
    uniform_int_distribution<int> disTrueChoice(0, 3);

    //定义选项
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
            answerChoice = "A";
            break;
        case 1:
            answerChoice = "B";
            break;
        case 2:
            answerChoice = "C";
            break;
        default:
            answerChoice = "D";
            break;
    }

    Word A = wordbook[numA];
    Word B = wordbook[numB];
    Word C = wordbook[numC];
    Word D = wordbook[numD];
    Word chooseWord[4]={A,B,C,D};
    Word T=chooseWord[numT];

    cout << "题目：" << T.getMeaning() << endl;
    cout << "A." << A.getWord() << endl;
    cout << "B." << B.getWord() << endl;
    cout << "C." << C.getWord() << endl;
    cout << "D." << D.getWord() << endl;
    cout << "输入你的选项" << endl;

    getline(cin, input);

    if (input == answerChoice) {
        cout << "恭喜你，答对了" << endl;
    } else {
        cout << "很遗憾，你回答错误" << endl;
        string fullPath = "../../resource/wrongBook/";
        fullPath+=users[userId].getUsersName();
        //若已在错题本里面，不会重复录入
        for (int i = 0; i < wrongWordCount; ++i) {
            if (strcmp(wrongWordBook[i].getWord(),T.getWord())==0){
                ifAnswerIsRight=false;
                return ifAnswerIsRight;
            }
        }

        //加入错题本
        QModel::toWrongBook(fullPath, T.getWord(), T);

        ifAnswerIsRight = false;
    }
    return ifAnswerIsRight;
}

/**
 * 写入分数
 * @param ifAnswerIsRight 是否正确
 * @param i 用户ID
 */
void ChoiceQ::operateScore(int ifAnswerIsRight, int i) {
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


