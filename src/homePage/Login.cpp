//
// Created by TairanLiu on 24-12-17.
//
#include <fstream>
#include <sstream>
#include "Login.h"

/**
 * 获取用户索引
 * @return 返回用户下标
 */
int Login::getUserIndex() {
    cout<<"进入"<<endl;
    string input;
    Customer user[MAX];
    char filename[MAX]="../../resource/users.txt";

    int UserCount=ReadUsersInf(filename, user);
//    文件不存在，直接退出
    if (UserCount==-1){
        return -1;
    }
    char username[MAX], password[MAX];
    cout<<"输入你的姓名"<<endl;
    getline(cin,input);
    strcpy(username,input.c_str());
    cout<<"输入密码"<<endl;
    getline(cin,input);
    strcpy(password,input.c_str());
    // 返回登录的用户索引
    for (int i = 0; i < UserCount; i++) {
        if (strcmp(user[i].getUsersName(), username) == 0 && strcmp(user[i].getPassword(), password) == 0) {
            cout<<"登录成功"<<endl;
            return i;
        }
    }
    cout<<"用户名或密码错误"<<endl;
    return -1;
}

//读取文件,返回最后一个用户下一个的下标
int Login::ReadUsersInf(char* fname, Customer Inf[])
{
    int i=0;
    char usersname[MAX];
    char password[MAX];
    char clockTime[MAX];
    int score=0;
    ifstream file(fname);
    string line;


    if (file.is_open()) {
        while (getline(file, line)) {
            istringstream iss(line);
            string user, pass,ct;  // 临时string变量

            if (iss >> user >> pass >> score >>ct) {
                // 将string复制到char数组
                strcpy(usersname, user.c_str());
                strcpy(password, pass.c_str());
                strcpy(clockTime, ct.c_str());
            }
            Inf[i].setUsersName(usersname);
            Inf[i].setPassword(password);
            Inf[i].setScore(score);
            Inf[i].setClockTime(clockTime);
            i++;
        }
        file.close();
    }else{
        cout<<"文件打开失败"<<endl;
    }
    //因为文件写入时输入格式里的换行会写入文件，最后一条记录后面会有一个空行
    return i;
}