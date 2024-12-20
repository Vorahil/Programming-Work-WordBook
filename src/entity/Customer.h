//
// Created by TairanLiu on 24-12-17.
//

#ifndef PROGRAMMING_CUSTOMER_H
#define PROGRAMMING_CUSTOMER_H
#define MAX 10000

class Customer{
    private:
        char UsersName[MAX];
        char Password[MAX];
        int score;
        char ClockTime[MAX];
    public:
        char *getUsersName();
        void setUsersName(const char*Username);
        char *getPassword();
        void setPassword(const char *Password);
        void setScore(int score);
        int getTotalScore();
        void setClockTime(const char *ClockTime);
        char *getClockTime();
};


#endif //PROGRAMMING_CUSTOMER_H
