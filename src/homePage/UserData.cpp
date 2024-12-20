//
// Created by TairanLiu on 24-12-20.
//
#include "UserData.h"
void UserData::checkScore(int userId) {
    char filename[MAX]="../../resource/users.txt";
    Customer users[MAX];
    Login::ReadUsersInf(filename,users);
    cout<<"你的总分是"<<users[userId].getTotalScore()<<endl;
}

void UserData::checkWrongBook(int userId) {
    Word wrongWordBook[MAX];
    string wrongBookDir;
    char filename[MAX]="../../resource/users.txt";
    Customer users[MAX];
    int wrongNum;

    Login::ReadUsersInf(filename,users);

    wrongBookDir="../../resource/wrongBook/";
    wrongNum=QModel::readFromWrongBookReturnCount(wrongBookDir+users[userId].getUsersName(),wrongWordBook);

    if (wrongNum==0){
        cout<<"你没有错题"<<endl;
        return;
    }else{
        for (int i = 0; i < wrongNum; ++i) {
            cout<<"单词:"<<wrongWordBook[i].getWord()<<"     \t"<<"词性"<<wrongWordBook[i].getPartOfSpeech()<<"          \t"<<"释义："<<wrongWordBook[i].getMeaning()<<endl;
        }
    }
}

void UserData::clock(int userId) {
    char filename[MAX]="../../resource/users.txt";
    Customer users[MAX];
    string ct;
    int userCount;
    userCount=Login::ReadUsersInf(filename,users);

    time_t t = time(nullptr); // 获取当前时间戳
    tm* localTime =localtime(&t); // 转换为本地时间（tm结构）
    ostringstream oss;
    // 格式为：年-月-日
    oss << (1900 + localTime->tm_year) << "-"<< (1 + localTime->tm_mon) << "-"<< localTime->tm_mday;
    ct=oss.str();

    if (strcmp(users[userId].getClockTime(),ct.c_str())==0){
        cout<<"今日已打卡"<<endl;
        return;
    } else{
        users[userId].setClockTime(ct.c_str());
        if (changeClockTime("../../resource/users.txt",users,userCount)){
            cout<<"今日打卡成功"<<endl;
        }else{
            cout<<"打卡失败"<<endl;
        }
    }
}

//返回值表示是否写入成功
int UserData::changeClockTime(string filePath, Customer *users,int userCount) {
    ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return 0;
    }
    for (int i = 0; i <userCount ; ++i) {
        file<<users[i].getUsersName()<<" "<<users[i].getPassword()<<" "<<users[i].getTotalScore()<<" "<<users[i].getClockTime()<<endl;
    }
    file.close();
    return 1;
}

