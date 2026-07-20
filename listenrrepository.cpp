#include "listenrrepository.h"

#include <vector>
#include "listener.h"

listenrRepository::listenrRepository(AccountRepository& accountRepository)
    : accountRepository(accountRepository)
{
}

User* listenrRepository::search(int id) const
{
    return accountRepository.search(id);
}

void listenrRepository::updatedLike(int listenerId, int songId, bool liked)
{
    User* user = accountRepository.search(listenerId);

    if (user == nullptr)
    {
        return;
    }

    Listener* foundListener = dynamic_cast<Listener*>(user);

    if (foundListener == nullptr)
    {
        return;
    }

    std::vector<int> likedSongs = foundListener->getIdLikedSong();

    if (liked)
    {
        for (size_t i = 0; i < likedSongs.size(); ++i)
        {
            if (likedSongs[i] == songId)
            {
                return;
            }
        }

        foundListener->setIdLikedSongs(songId);
        return;
    }

    for (size_t i = 0; i < likedSongs.size(); ++i)
    {
        if (likedSongs[i] == songId)
        {
            foundListener->deleteLikedSong(static_cast<int>(i));
            return;
        }
    }
}

bool listenrRepository::isLiked(int listenerId, int songId) const
{
    User* user = accountRepository.search(listenerId);

    if (user == nullptr)
    {
        return false;
    }

    Listener* foundListener = dynamic_cast<Listener*>(user);

    if (foundListener == nullptr)
    {
        return false;
    }

    std::vector<int> likedSongs = foundListener->getIdLikedSong();

    for (size_t i = 0; i < likedSongs.size(); ++i)
    {
        if (likedSongs[i] == songId)
        {
            return true;
        }
    }

    return false;
}

