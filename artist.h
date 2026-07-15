#ifndef ARTIST_H
#define ARTIST_H

#include "user.h"

class Artist : public User
{
public:
    Artist();
    Artist(int id, const std::string& username, const std::string& password,
           const std::string& fullName, const std::string& biography,
           const std::string& role, const std::string& profilePhotoPath);
};

#endif // ARTIST_H
