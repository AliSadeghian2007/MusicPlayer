#include "listenrrepository.h"
#include "listener.h"

listenrRepository::listenrRepository() {}


void listenrRepository::updatedLike(int listenerId,int songId,bool liked)
{
    Listener* a = nullptr;

    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->getId() == listenerId)
        {
            a = dynamic_cast<Listener*>(users[i].get());
            break;
        }
    }

    if (a == nullptr)
    {
        return;
    }

    std::vector<int> b = a->getIdLikedSong();

    if (liked == true)
    {

        for (int i = 0; i < b.size(); i++)
        {
            if (b[i] == songId)
            {
                return;
            }
        }

        a->setIdLikedSongs(songId);
    }
    else
    {
        for (int i = 0; i < b.size(); i++)
        {
            if (b[i] == songId)
            {
                a->deleteLikedSong(i);
                return;
            }
        }

    }
}



bool listenrRepository::isLiked(int listenerId,int songId)
{
    Listener* a=nullptr;

    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->getId() == listenerId)
        {
            a = dynamic_cast<Listener*>(users[i].get());
            break;
        }
    }

    if (a == nullptr)
    {
        return false;
    }
    std::vector<int> songs = a->getIdLikedSong();

    for (int i = 0; i < songs.size(); i++)
    {
        if (songs[i] == songId)
        {
            return true;
        }
    }

    return false;


}