//
// Created by TairanLiu on 24-12-17.
//
#include <cstring>
#include "Customer.h"

char *Customer::getUsersName() {
    return this->UsersName;
}

void Customer::setUsersName(const char *UsersName) {
    strcpy(this->UsersName, UsersName);
}

char *Customer::getPassword() {
    return this->Password;
}
void Customer::setPassword(const char *Password) {
    strcpy(this->Password,Password);
}

void Customer::setScore(int score) {
    this->score=score;
}

int Customer::getTotalScore() {
    return this->score;
}

void Customer::setClockTime(const char *ClockTime) {
    strcpy(this->ClockTime,ClockTime);
}

char *Customer::getClockTime() {
    return this->ClockTime;
}
