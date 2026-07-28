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

    if (!success)
    {
        return false;
    }

    return repo.saveToFile("accounts.txt");


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

bool AccountManager::editAccount(
    const std::string& username,
    const std::string& newUsername,
    const std::string& newPassword)
{
    User* user = repo.searchByUserName(username);

    if (user == nullptr)
    {
        return false;
    }

    // Only reject the rename if some *other* account already owns
    // that username; renaming to the same username is a no-op here.
    if (newUsername != username)
    {
        User* existing = repo.searchByUserName(newUsername);

        if (existing != nullptr && existing != user)
        {
            return false;
        }
    }

    user->setUserName(newUsername);
    user->setPassword(newPassword);

    return repo.saveToFile("accounts.txt");
}

bool AccountManager::deleteAccount(const std::string& username)
{
    User* user = repo.searchByUserName(username);

    if (user == nullptr)
    {
        return false;
    }

    bool removed = repo.remove(user->getId());

    if (!removed)
    {
        return false;
    }

    return repo.saveToFile("accounts.txt");
}



bool AccountManager::usernameExists(const std::string& username) const
{
    return repo.searchByUserName(username) != nullptr;
}

bool AccountManager::passwordExists(const std::string& password) const
{
    const std::vector<std::unique_ptr<User>>& users = repo.getUsers();

    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->getPassword() == password)
        {
            return true;
        }
    }

    return false;
}

