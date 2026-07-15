#include "user.h"

User::User()
    : id(0),
    username(""),
    password(""),
    fullName(""),
    biography(""),
    role(""),
    profilePhotoPath("")
{
}

User::User(int id, const std::string& username, const std::string& password,
           const std::string& fullName, const std::string& biography,
           const std::string& role, const std::string& profilePhotoPath)
    : id(id),
    username(username),
    password(password),
    fullName(fullName),
    biography(biography),
    role(role),
    profilePhotoPath(profilePhotoPath)
{
}
