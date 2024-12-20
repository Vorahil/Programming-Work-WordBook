//
// Created by TairanLiu on 24-12-18.
//
#include "ViewWords.h"

void ViewWords::viewWords() {
    Word wordBook[MAX];
    char dirname[MAX]="../../resource/WordBook";
    int wordCount = AddWord::readFileReturnId(dirname, wordBook);
    for(int i=0;i<wordCount;i++){
        cout<<"单词:"<<wordBook[i].getWord()<<"     \t"<<"词性"<<wordBook[i].getPartOfSpeech()<<"          \t"<<"释义："<<wordBook[i].getMeaning()<<endl;
    }
}

