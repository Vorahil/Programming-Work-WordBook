//
// Created by TairanLiu on 24-12-18.
//
#include "DeleteWord.h"

void DeleteWord::deleteWord() {
    Word wordBook[MAX];
    char word[MAX];
    string input;
    while (true){
        cout<<"输入你要删除的单词"<<endl;
        getline(cin,input);
        if (AddWord::hasContent(input.c_str())){
            strcpy(word,input.c_str());
            break;
        }
        cout<<"输入有效内容"<<endl;
    }

    char dirname[MAX]="C:/CodeWork/C/Programming/resource/WordBook";
    char filename[MAX]="C:/CodeWork/C/Programming/resource/WordBook";
    strcat(filename,"/");
    strcat(filename,word);
    strcat(filename,".txt");
    int wordCount = AddWord::readFileReturnId(dirname, wordBook);
    for(int i=0;i<wordCount;i++){
        if (strcmp(wordBook[i].getWord(),word)==0){
            filesystem::remove(string(filename));
            cout<<"删除成功"<<endl;
            return;
        }
    }
    cout<<"单词不存在"<<endl;
}

