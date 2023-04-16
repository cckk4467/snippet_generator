// @title: exception
// @description: custom exception
// @prefix: npoe
#include <bits/stdc++.h>
#include <string.h>
using namespace std;

class duplicated_argument : public exception {
    char res[128];
   public:
    duplicated_argument(const char* filename, const char* para){
            strcpy(res,"In file ");
            strcat(res,filename);
            strcat(res,": occured @");
            strcat(res,para);
            strcat(res," duplications");
        }
    const char* what() const noexcept override {
        return res;
    }
};
class argument_miss : public exception {
    char res[128];
   public:
    argument_miss(const char* filename, const char* para){
            strcpy(res,"In file ");
            strcat(res,filename);
            strcat(res,": miss @");
            strcat(res,para);
        }
    const char* what() const noexcept override {
        return res;
    }
};