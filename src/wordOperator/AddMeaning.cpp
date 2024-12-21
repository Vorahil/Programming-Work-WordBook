//
// Created by TairanLiu on 24-12-18.
//
#include "AddMeaning.h"

/**
 * 添加释义
 */
void AddMeaning::addMeaning() {
    Word wordBook[MAX];
    char word[MAX];
    char partOfSpeech[MAX];
    char meaning[MAX];
    char tmeaning[MAX];
    string input;
    while (true) {
        cout << "输入你要添加中文解释的单词" << endl;
        getline(cin, input);
        if (AddWord::hasContent(input.c_str())) {
            strcpy(word, input.c_str());
            break;
        }
        cout << "输入有效内容" << endl;
    }

    char dirname[MAX] = "../../resource/WordBook";
    int wordCount = AddWord::readFileReturnId(dirname, wordBook);
    for (int i = 0; i < wordCount; i++) {
        if (strcmp(wordBook[i].getWord(), word) == 0) {
            //输入中文解释
            cout << "输入添加的中文解释" << endl;
            getline(cin, input);
            strcpy(tmeaning, input.c_str());
            if (!AddWord::hasContent(tmeaning)) {
                cout << "请输入有效中文" << endl;
                continue;
            }
            //添加新的释义
            strcpy(meaning,wordBook[i].getMeaning());
            strcat(meaning,tmeaning);
            wordBook[i].setMeaning(meaning);
            // 在新目录中创建并写入文件
            string filename(wordBook[i].getWord());
            string filenamePath = filename + ".txt";
            string fullPath = "../../resource/WordBook"; // 完整路径

            if (AddWord::addWordToFile(fullPath, filenamePath, wordBook, i)) {
                cout << "写入成功" << endl;
                return;
            } else {
                cout << "写入失败" << endl;
                continue;
            }
        }
    }
    cout << "单词不存在" << endl;
}

