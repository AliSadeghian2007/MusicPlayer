#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <string>

#include "accountrepository.h"
#include "user.h"

class AccountManager
{
private:
    AccountRepository& repo;

public:
    explicit AccountManager(AccountRepository& repo);

    bool registerAccount(const std::string& username,
                         const std::string& password,
                         const std::string& fullName,
                         const std::string& biography,
                         const std::string& role,
                         const std::string& profilePhotoPath);

    User* Login(std::string username, std::string password);

    void editAccount(const std::string& username,
                     const std::string& newUsername,
                     const std::string& newPassword);

    void deleteAccount(const std::string& username);

    bool usernameExists(const std::string& username) const;
    bool passwordExists(const std::string& password) const;

};

#endif // ACCOUNTMANAGER_H

