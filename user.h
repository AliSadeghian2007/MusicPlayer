#ifndef USER_H
#define USER_H

#include<string>
using namespace std;

class User
{
public:
    User();
protected:
    int id;
    string username;
    string password;
    string fullName;
    string biography;
    string role;
    string profilePhotoPath;
};

#endif // USER_H
