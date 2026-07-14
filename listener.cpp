#include "listener.h"

Listener::Listener()
{

}
void Listener::setIdLikedSongs(int id)
{
    likedSongs.push_back(id);
}
std::vector<int> Listener::getIdLikedSong()
{
    return likedSongs;
}
void Listener::deleteLikedSong(int i)
{
    likedSongs.erase(likedSongs.begin()+i);
}