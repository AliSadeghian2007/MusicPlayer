#include "playlist.h"

Playlist::Playlist(int id, int listenerId, const std::string& name)
    : listenerId(listenerId),
    name(name),id(id)
{
}

int Playlist::getId() const
{
    return id;
}

int Playlist::getListenerId() const
{
    return listenerId;
}

void Playlist::addSong(int songId)
{
    songIds.push_back(songId);
}

const std::vector<int>& Playlist::getSongIds() const
{
    return songIds;
}

std::string Playlist::getName() const
{
    return name;
}

void Playlist::removeSong(int songId)
{
    for (int i = 0; i < static_cast<int>(songIds.size()); ++i)
    {
        if (songIds[i] == songId)
        {
            songIds.erase(songIds.begin() + i);
            return;
        }
    }
}
