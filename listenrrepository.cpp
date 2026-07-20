
#include "listenrrepository.h"
#include "listener.h"

listenrRepository::listenrRepository()
{
}

void listenrRepository::updatedLike(int listenerId, int songId, bool liked)
{
    Listener* foundListener = nullptr;

    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->getId() == listenerId)
        {
            foundListener = dynamic_cast<Listener*>(users[i].get());
            break;
        }
    }

    if (foundListener == nullptr)
    {
        return;
    }

    std::vector<int> likedSongs = foundListener->getIdLikedSong();

    if (liked == true)
    {

        for (int i = 0; i < likedSongs.size(); i++)
        {
            if (likedSongs[i] == songId)
            {
                return;
            }
        }

        foundListener->setIdLikedSongs(songId);
    }
    else
    {

        for (int i = 0; i < likedSongs.size(); i++)
        {
            if (likedSongs[i] == songId)
            {
                foundListener->deleteLikedSong(i);
                return;
            }
        }
    }
}

bool listenrRepository::isLiked(int listenerId, int songId) const
{
    Listener* foundListener = nullptr;

    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->getId() == listenerId)
        {
            foundListener = dynamic_cast<Listener*>(users[i].get());
            break;
        }
    }

    if (foundListener == nullptr)
    {
        return false;
    }

    std::vector<int> likedSongs = foundListener->getIdLikedSong();

    for (int i = 0; i < likedSongs.size(); i++)
    {
        if (likedSongs[i] == songId)
        {
            return true;
        }
    }

    return false;
}
