//
// Created by TairanLiu on 24-12-18.
//
#include "QModel.h"

void QModel::questionChoose(int i) {
    string input;
    int choice;
    do{
        cout<<"输入题型"<<endl;
        cout<<"1.选择题"<<endl;
        cout<<"2.填空题"<<endl;
        cout<<"0.返回"<<endl;
        getline(cin, input);
        choice = stoi(input);
        switch (choice) {
            case 1:
                ChoiceQ::chooseWay(i);
                choice=0;
                break;
            case 2:
                BlankQ::chooseWay(i);
                choice=0;
                break;
            case 0:
                cout<<"欢迎下次使用"<<endl;
                break;
            default:
                cout<<"输入正确的数字"<<endl;
                choice=1;
                break;
        }
    }while (choice);
}

/**
 * 写入大错题本目录
 * @param fullPath 文件夹
 * @param filenamePath 文本文档名称(不含后缀)
 * @param word 输入的单词
 * @return
 */
int QModel::toWrongBook(string fullPath, string filenamePath,Word word) {
    filenamePath+=".txt";
    filesystem::path filePath = filesystem::path(fullPath) / filenamePath;
    ofstream file(filePath);
    if (file.is_open()) {
        file << word.getPartOfSpeech() << endl;
        file << word.getMeaning() << endl;
        file.close();
        cout<<"文件写入"<<filePath<<endl;
        return 1;
    } else {
        cout<<"未打开文件"<<endl;
        return 0;
    }
}

//读取错题本
int QModel::readFromWrongBookReturnCount(const filesystem::path &dirPath, Word words[]) {
    int wordCount = 0;
    char word[MAX];
    char partOfSpeech[MAX];
    char meaning[MAX];

    if (filesystem::exists(dirPath) && filesystem::is_directory(dirPath)) {
        for ( const auto& entry : filesystem::directory_iterator(dirPath)) {
            ifstream file(entry.path());
            if (!file.is_open()) {
                cout << "文件打开失败 " << entry.path() << endl;
                return -1;
            }

            // 获取文件名作为单词
            string filename = entry.path().stem().string();
            strcpy(word, filename.c_str());

            string line;
            int lineIndex = 0;

            // 读取每一行
            while (getline(file, line)) {
                if (lineIndex == 0) {
                    strcpy(partOfSpeech, line.c_str());
                } else if (lineIndex==1){
                    strcpy(meaning, line.c_str());
                } else{
                    strcat(meaning,line.c_str());
                }
                lineIndex++;
            }

            words[wordCount].setWord(word);
            words[wordCount].setPartOfSpeech(partOfSpeech);
            words[wordCount].setMeaning(meaning);
            file.close();
            wordCount++;
        }
    } else {
        cout << "文件不存在" << endl;
        return -1;
    }
    return wordCount;
}



//复习界面
void QModel::review(int userId) {
    string input;
    int flag;
    do {
        flag=1;
        cout<<"是否复习?1.是、0.否"<<endl;
        getline(cin,input);
        if (stoi(input)){
            reviewWord(userId);
        }else{
            if (!stoi(input)){
                cout<<"注意多多练习"<<endl;
                return;
            }else{
                cout<<"输入正确的数字"<<endl;
                flag=0;
            }
        }
    } while (!flag);
}

//复习单词的具体操作
void QModel::reviewWord(int userId) {
    int wrongWordNum=0;
    int userCount=0;
    char usersPath[MAX]="../../resource/users.txt";
    string wrongWordBookPath="../../resource/wrongBook";
    Customer users[MAX];
    Word wrongWordBook[MAX];

    userCount=Login::ReadUsersInf(usersPath,users);
    wrongWordNum=readFromWrongBookReturnCount(wrongWordBookPath+"/"+users[userId].getUsersName(),wrongWordBook);

    cout<<"你共有"<<wrongWordNum<<"个错题"<<endl;
    if (wrongWordNum==0){
        cout<<"你没有错题，继续努力"<<endl;
        return;
    }
    for(int i=0;i<wrongWordNum;i++){
        cout<<"英文释义:"<<wrongWordBook[i].getMeaning()<<endl;
        cout<<"输入英文"<<endl;
        string input;
        getline(cin,input);

        //复习的时候回答正确
        if (strcmp(input.c_str(),wrongWordBook[i].getWord())==0){
            cout<<"恭喜答对"<<endl;
            filesystem::remove(wrongWordBookPath+"/"+users[userId].getUsersName()+"/"+wrongWordBook[i].getWord()+".txt");
            users[userId].setScore(users[userId].getTotalScore()+20);

            if (changeUserScore("../../resource/users.txt",users,userCount)){
                cout<<"你的总成绩加20分"<<endl;
            } else{
                cout<<"成绩录入失败"<<endl;
                return;
            }
        }else{
            cout<<"很遗憾，回答错误"<<endl;
        }
    }
}

//写入分数到文本记录
int QModel::changeUserScore(string filePath, Customer *users,int userCount) {
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


