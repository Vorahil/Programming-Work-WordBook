//
// Created by TairanLiu on 24-12-17.
//

#include "Word.h"

void Word::setWord(const char *word) {
    strcpy(this->word,word);
}

void Word::setPartOfSpeech(const char *partOfSpeech) {
    strcpy(this->partOfSpeech,partOfSpeech);

}

void Word::setMeaning(const char *meaning) {
    strcpy(this->meaning,meaning);

}

char *Word::getWord() {
    return this->word;
}

char *Word::getPartOfSpeech() {
    return this->partOfSpeech;
}

char *Word::getMeaning() {
    return this->meaning;
}

