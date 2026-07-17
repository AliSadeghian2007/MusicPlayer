#include "accountmanager.h"
#include<memory>
int AccountManager::nextid = 1;
AccountManager::AccountManager() {}
void AccountManager::registerAccount(const std::string& username,
                     const std::string& password,
                     const std::string& fullName,
                     const std::string& biography,
                     const std::string& role,
                     const std::string& profilePhotoPath)
{
     int newid = nextid++;
    std::unique_ptr<User>a=std::make_unique<User>(newid, username, password, fullName, biography, role, profilePhotoPath);
    repo.save(std::move(a));
}


User* AccountManager::Login(std::string username, std::string password)
{
    User* b = repo.searchByUserName(username);
    if (!b) {
        return nullptr;
    }

    if (b->getPassword() == password) {
        return b;
    }

    return nullptr;
}



void AccountManager::editAccount(const std::string& username,
                                 const std::string& newUsername,
                                 const std::string& newPassword)
{
    User* user = repo.searchByUserName(username);
    if (!user) {
        return;
    }

    user->setUserName(newUsername);
    user->setPassword(newPassword);
}

void AccountManager::deleteAccount(const std::string &username)
{
    User* b=repo.searchByUserName(username);
    if(b)
    {
        repo.remove(b->getId());
    }
    else{return;}

}
