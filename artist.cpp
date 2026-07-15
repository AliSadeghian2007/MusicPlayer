#include "artist.h"

Artist::Artist()
    : User()
{
}

Artist::Artist(int id, const std::string& username, const std::string& password,
               const std::string& fullName, const std::string& biography,
               const std::string& role, const std::string& profilePhotoPath)
    : User(id, username, password, fullName, biography, role, profilePhotoPath)
{
}
