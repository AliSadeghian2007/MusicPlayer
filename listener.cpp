#include "listener.h"

Listener::Listener()
    : User()
{
}

Listener::Listener(int id, const std::string& username, const std::string& password,
                   const std::string& fullName, const std::string& biography,
                   const std::string& role, const std::string& profilePhotoPath)
    : User(id, username, password, fullName, biography, role, profilePhotoPath)
{
}

void Listener::setIdLikedSongs(int id)
{
    likedSongs.push_back(id);
}

std::vector<int> Listener::getIdLikedSong() const
{
    return likedSongs;
}

void Listener::deleteLikedSong(int i)
{
    likedSongs.erase(likedSongs.begin() + i);
}
