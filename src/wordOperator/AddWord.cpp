//
// Created by TairanLiu on 24-12-18.
//
#include "AddWord.h"

/**
 * 添加单词
 */
void AddWord::addWord() {
    string input;
    Word wordbook[MAX];
    char filename[MAX] = "C:/CodeWork/C/Programming/resource/WordBook";
    char word[MAX], partOfSpeech[MAX], meaning[MAX];
    int wordCount = readFileReturnId(filename, wordbook);
    do {
        int num;
        //输入英文原型
        cout << "输入英文" << endl;
        getline(cin,input);
        strcpy(word,input.c_str());
        if (!hasContent(word)) {
            cout << "请输入有效单词" << endl;
            continue;
        }
        for(int i=0;i<wordCount;i++){
            if (strcmp(wordbook[i].getWord(),word)==0){
                cout<<"单词已存在"<<endl;
                return;
            }
        }
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
            cout << "请输入词性对应的数字 (1-8): ";
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
                default:
                    cout << "请输入有效数字" << endl;
                    break;
            }
        }

        //输入中文解释
        flag= true;
        while (flag){
            cout << "输入中文解释" << endl;
            getline(cin,input);
            strcpy(meaning,input.c_str());
            if (!hasContent(meaning)) {
                cout << "请输入有效中文" << endl;
                continue;
            }
            flag= false;
        }


        //存放单词
        wordbook[wordCount].setWord(word);
        wordbook[wordCount].setPartOfSpeech(partOfSpeech);
        wordbook[wordCount].setMeaning(meaning);

        string filename(wordbook[wordCount].getWord());
        string filenamePath = filename+".txt";
        string fullPath = "C:/CodeWork/C/Programming/resource/WordBook"; // 完整路径

        // 在新目录中创建并写入文件
        if (addWordToFile(fullPath,filenamePath,wordbook,wordCount)){
            cout << "写入成功" << endl;
            return;
        } else{
            cout<<"写入失败"<<endl;
            continue;
        }
    } while (true);
}

/**
 * 读取文件
 * @param dirPath 文件夹地址
 * @param wordBook 单词本：单词数组
 * @param Word 单词实体类
 * @return 文件下一个单词的下标或文件总共的数字
 */
int AddWord::readFileReturnId(const filesystem::path &dirPath, Word wordBook[]) {
    int wordIndex = 0;
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

            wordBook[wordIndex].setWord(word);
            wordBook[wordIndex].setPartOfSpeech(partOfSpeech);
            wordBook[wordIndex].setMeaning(meaning);
            file.close();
            wordIndex++;
        }
    } else {
        cout << "文件不存在" << endl;
        return -1;
    }
    return wordIndex;
}

/**
 * 判断是否有空
 * @param str 传入字符数组里的指针
 * @return 是否为空，是返回true
 */
bool AddWord::hasContent(const char *str) {
    while (*str) {
        if (*str != ' ') {
            return true;
        }
        str++;
    }
    return false;
}

/**
 * 将单词写入文件
 * @param fullPath 文件夹地址
 * @param filenamePath 文件名
 * @param wordBook 单词本
 * @param wordCount 单词下标
 * @return
 */
bool AddWord::addWordToFile(string fullPath, string filenamePath, Word wordBook[], int wordCount) {
    filesystem::path filePath = filesystem::path(fullPath) / filenamePath;
    ofstream file(filePath);
    if (file.is_open()) {
        file << wordBook[wordCount].getPartOfSpeech() << endl;
        file << wordBook[wordCount].getMeaning() << endl;
        file.close();
        cout<<"文件写入"<<filePath<<endl;
        return true;
    } else {
        cout<<"未打开文件"<<endl;
        return false;
    }
}
