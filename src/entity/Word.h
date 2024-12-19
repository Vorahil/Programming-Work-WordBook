//
// Created by TairanLiu on 24-12-17.
//

#ifndef PROGRAMMING_WORD_H
#define PROGRAMMING_WORD_H
class Word{
public:
    void setWord(const char* word);
    void setPartOfSpeech(const char* partOfSpeech);
    void setMeaning(const char* meaning);
    char *getWord();
    char *getPartOfSpeech();
    char *getMeaning();
private:
    char word[100];     // 单词
    char partOfSpeech[100];  // 词性
    char meaning[1000];  // 中文意思
};
#endif //PROGRAMMING_WORD_H
