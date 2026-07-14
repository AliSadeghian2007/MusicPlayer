#ifndef USER_H
#define USER_H

#include<string>

class User
{
public:
    User();
    virtual ~User()=default;
    int getId(){return id;}
    std::string getUserName(){return username;}

protected:
    int id;
    std::string username;
    std::string password;
    std::string fullName;
    std::string biography;
    std::string role;
    std::string profilePhotoPath;
};

#endif // USER_H
