#ifndef LISTENER_H
#define LISTENER_H

#include <vector>
#include "user.h"

class Listener : public User
{
public:
    Listener();
    Listener(int id, const std::string& username, const std::string& password,
             const std::string& fullName, const std::string& biography,
             const std::string& role, const std::string& profilePhotoPath);

    void setIdLikedSongs(int id);
    std::vector<int> getIdLikedSong() const;
    void deleteLikedSong(int i);

private:
    std::vector<int> likedSongs;
};

#endif
