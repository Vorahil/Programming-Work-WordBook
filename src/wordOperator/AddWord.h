//
// Created by TairanLiu on 24-12-17.
//
#include "../entity/Word.h"
#include "filesystem"
#include <cstring>
#include <fstream>
#include "iostream"
#ifndef PROGRAMMING_ADD_H
#define PROGRAMMING_ADD_H
#define MAX 10000
using namespace std;
class AddWord {
public:
    static bool addWordToFile(string fullPath,string filenamePath,Word wordBook[],int wordCount);
    static void addWord();
    static int readFileReturnId(const filesystem::path &dirPath,Word wordBook[]);
    static bool hasContent(const char *str);
};
#endif //PROGRAMMING_ADD_H
