#ifndef LISTENER_H
#define LISTENER_H
#include<vector>
#include "user.h"

class Listener : public User
{
private:
    std::vector<int>likedSongs;
public:
    Listener();
    void setIdLikedSongs(int id);
    std::vector<int> getIdLikedSong() const;
    void deleteLikedSong(int i);
};

#endif // LISTENER_H
