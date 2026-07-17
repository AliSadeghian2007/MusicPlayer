#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H
#include "user.h"
#include "accountrepository.h"
class AccountManager
{
private:
    static int nextid;
    AccountRepository repo;
public:
    AccountManager();



    void registerAccount(const std::string& username,
                         const std::string& password,
                         const std::string& fullName,
                         const std::string& biography,
                         const std::string& role,
                         const std::string& profilePhotoPath);

    User* Login(std::string username,std::string password);
    void editAccount(const std::string &username,const std::string &newUsername,const std::string &newPassword);
    void deleteAccount(const std::string &username);

};
#endif // ACCOUNTMANAGER_H
