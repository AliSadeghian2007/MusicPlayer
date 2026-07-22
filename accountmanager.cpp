#include "accountmanager.h"

#include <memory>

#include "artist.h"
#include "listener.h"

AccountManager::AccountManager(AccountRepository& repo)
    : repo(repo)
{
}

bool AccountManager::registerAccount(
    const std::string& username,
    const std::string& password,
    const std::string& fullName,
    const std::string& biography,
    const std::string& role,
    const std::string& profilePhotoPath)
{
    std::unique_ptr<User> account;

    if (role == "Listener")
    {
        account = std::make_unique<Listener>(
            0,
            username,
            password,
            fullName,
            biography,
            role,
            profilePhotoPath);
    }
    else if (role == "Artist")
    {
        account = std::make_unique<Artist>(
            0,
            username,
            password,
            fullName,
            biography,
            role,
            profilePhotoPath);
    }
    else
    {
        account = std::make_unique<User>(
            0,
            username,
            password,
            fullName,
            biography,
            role,
            profilePhotoPath);
    }

    bool success = repo.save(std::move(account));

    if (success)
    {
        repo.saveToFile("accounts.txt");
    }

    return success;

}

User* AccountManager::Login(std::string username, std::string password)
{
    User* user = repo.searchByUserName(username);

    if (user == nullptr)
    {
        return nullptr;
    }

    if (user->getPassword() == password)
    {
        return user;
    }

    return nullptr;
}

void AccountManager::editAccount(
    const std::string& username,
    const std::string& newUsername,
    const std::string& newPassword)
{
    User* user = repo.searchByUserName(username);

    if (user == nullptr)
    {
        return;
    }

    user->setUserName(newUsername);
    user->setPassword(newPassword);
}

void AccountManager::deleteAccount(const std::string& username)
{
    User* user = repo.searchByUserName(username);

    if (user == nullptr)
    {
        return;
    }

    repo.remove(user->getId());
}
