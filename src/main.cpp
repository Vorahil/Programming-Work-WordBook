#include <iostream>
#include "windows.h"
#include "string"

#include "homePage/Login.h"
#include "homePage/Register.h"
#include "homePage/UserData.h"
#include "wordOperator/AddWord.h"
#include "WordOperator/DeleteWord.h"
#include "WordOperator/ModifyWord.h"
#include "WordOperator/AddMeaning.h"
#include "WordOperator/ViewWords.h"
#include "memorizeWord/QModel.h"

using namespace std;

void homePage();

void chooseModel(int i);

void bookOperator();

void memorizeWord(int i);

int main() {
    SetConsoleOutputCP(65001);
    homePage();
    return 0;
}

//主页操作
void homePage() {
    int choice;
    string input;
    int i;
    do {
        cout << "欢迎" << endl;
        cout << "1.登录" << endl;
        cout << "2.注册" << endl;
        cout << "0.退出" << endl;
        cout << "键入数字选择你的要求" << endl;
        getline(cin, input);
        choice = stoi(input);
        switch (choice) {
            case 1:
                i = Login::getUserIndex();
                if (i != -1) {
                    cout << "选择你要的服务" << endl;
                    chooseModel(i);
                }
                break;
            case 2:
                Register::registerUserReturnIndex();
                break;
            case 0:
                cout << "欢迎下次使用" << endl;
                break;
            default:
                cout << "请键入正确的数字" << endl;
                break;
        }
    } while (choice);
}

//选择要求
void chooseModel(int i) {
    string input;
    int choice;
    do {
        cout << "1.打开单词本" << endl;
        cout << "2.开始背单词" << endl;
        cout << "0.退出并打卡" << endl;
        getline(cin, input);
        choice = stoi(input);
        switch (choice) {
            case 1:
                bookOperator();
                break;
            case 2:
                memorizeWord(i);
                break;
            case 0:
                UserData::clock(i);
                cout << "退出至登录界面" << endl;
                return;
            default:
                cout << "请输入正确的数字" << endl;
        }
    } while (true);
}

//单词本操作
void bookOperator() {
    int choice;
    string input;
    do {
        cout << "欢迎使用单词本" << endl;
        cout << "1.添加单词" << endl;
        cout << "2.删除单词" << endl;
        cout << "3.修改单词" << endl;
        cout << "4.添加注释" << endl;
        cout << "5.浏览单词" << endl;
        cout << "0.退出" << endl;
        cout << "键入你的选择" << endl;
        getline(cin, input);
        choice = stoi(input);
        switch (choice) {
            case 1:
                AddWord::addWord();
                break;
            case 2:
                DeleteWord::deleteWord();
                break;
            case 3:
                ModifyWord::modifyWord();
                break;
            case 4:
                AddMeaning::addMeaning();
                break;
            case 5:
                ViewWords::viewWords();
                break;
            case 0:
                cout << "欢迎下次使用" << endl;
                break;
            default:
                cout << "请输入正确的数字" << endl;
        }
    } while (choice);
}

//背单词操作
void memorizeWord(int i) {
    string input;
    int choice;
    do {
        cout << "欢迎使用背单词功能" << endl;
        cout<<"1.查看所有单词"<<endl;
        cout<<"2.开始学习"<<endl;
        cout<<"3.查看分数"<<endl;
        cout<<"4.查看错题本"<<endl;
        cout<<"5.开始复习"<<endl;
        cout<<"0.退出"<<endl;
        cout<<"键入你的选项"<<endl;
        getline(cin, input);
        choice = stoi(input);
        switch (choice) {
            case 1:
                ViewWords::viewWords();
                break;
            case 2:
                QModel::questionChoose(i);
                break;
            case 3:
                UserData::checkScore(i);
                break;
            case 4:
                UserData::checkWrongBook(i);
                break;
            case 5:
                QModel::review(i);
            case 0:
                cout<<"退至主页"<<endl;
                break;
            default:
                cout<<"输入正确的数字"<<endl;
        }
    } while (choice);
}