//
// Created by TairanLiu on 24-12-18.
//
#include "ModifyWord.h"

void ModifyWord::modifyWord() {
    Word wordBook[MAX];
    char word[MAX];
    char partOfSpeech[MAX];
    char meaning[MAX];
    string input;
    while (true) {
        cout << "输入你要修改的单词" << endl;
        getline(cin, input);
        if (AddWord::hasContent(input.c_str())) {
            strcpy(word, input.c_str());
            break;
        }
        cout << "输入有效内容" << endl;
    }

    char dirname[MAX] = "C:/CodeWork/C/Programming/resource/WordBook";
    int wordCount = AddWord::readFileReturnId(dirname, wordBook);
    for (int i = 0; i < wordCount; i++) {
        if (strcmp(wordBook[i].getWord(), word) == 0) {
            int num;
            //输入词性
            bool flag = true;
            while (flag) {
                cout << "选择词性" << endl;
                cout << "1.名词" << endl;
                cout << "2.代词" << endl;
                cout << "3.形容词" << endl;
                cout << "4.动词" << endl;
                cout << "5.副词" << endl;
                cout << "6.介词" << endl;
                cout << "7.连词" << endl;
                cout << "8.感叹词" << endl;
                cout << "9.不变" << endl;
                cout << "请输入词性对应的数字 (1-9): ";
                getline(cin, input);
                num = stoi(input);
                switch (num) {
                    case 1:
                        strcpy(partOfSpeech, "Noun");
                        flag = false;
                        break;
                    case 2:
                        strcpy(partOfSpeech, "Pronoun");
                        flag = false;
                        break;
                    case 3:
                        strcpy(partOfSpeech, "Adjective");
                        flag = false;
                        break;
                    case 4:
                        strcpy(partOfSpeech, "Verb");
                        flag = false;
                        break;
                    case 5:
                        strcpy(partOfSpeech, "Adverb");
                        flag = false;
                        break;
                    case 6:
                        strcpy(partOfSpeech, "Preposition");
                        flag = false;
                        break;
                    case 7:
                        strcpy(partOfSpeech, "Conjunction");
                        flag = false;
                        break;
                    case 8:
                        strcpy(partOfSpeech, "Interjection");
                        flag = false;
                        break;
                    case 9:
                        strcpy(partOfSpeech,wordBook[i].getPartOfSpeech());
                        flag = false;
                        break;
                    default:
                        cout << "请输入有效数字" << endl;
                        break;
                }
            }

            //输入中文解释
            cout << "输入新的中文解释" << endl;
            getline(cin, input);
            strcpy(meaning, input.c_str());
            if (!AddWord::hasContent(meaning)) {
                cout << "请输入有效中文" << endl;
                continue;
            }
            wordBook[i].setPartOfSpeech(partOfSpeech);
            wordBook[i].setMeaning(meaning);
            // 在新目录中创建并写入文件
            string filename(wordBook[i].getWord());
            string filenamePath = filename + ".txt";
            string fullPath = "C:/CodeWork/C/Programming/resource/WordBook"; // 完整路径

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