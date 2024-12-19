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
        cout<<"0.退出"<<endl;
        getline(cin, input);
        choice = stoi(input);
        switch (choice) {
            case 1:
                ChoiceQ::chooseWay(i);
                choice=0;
                break;
            case 2:
                break;
            case 0:
                cout<<"欢迎下次使用"<<endl;
                break;
            default:
                cout<<"输入正确的数字"<<endl;
                break;
        }
    }while (!choice);
}

void QModel::toWrongBook(string fullPath, string filenamePath,Word word) {
    filesystem::path filePath = filesystem::path(fullPath) / filenamePath;
    ofstream file(filePath);
    if (file.is_open()) {
        file << word.getPartOfSpeech() << endl;
        file << word.getMeaning() << endl;
        file.close();
        cout<<"文件写入"<<filePath<<endl;
        return;
    } else {
        cout<<"未打开文件"<<endl;
        return;
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
            // 使用二进制模式打开文件
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

