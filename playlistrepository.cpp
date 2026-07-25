#include "playlistrepository.h"
#include <fstream>
#include <sstream>
#include <iomanip>

PlaylistRepository::PlaylistRepository() : nextId(1), filePath("playlists.txt")
{
    loadFromFile();
}

int PlaylistRepository::generateId()
{
    return nextId++;
}

void PlaylistRepository::saveToFile() const
{
    std::ofstream file(filePath.c_str(), std::ios::trunc);
    if (!file.is_open()) return;

    for (int i = 0; i < static_cast<int>(playlistha.size()); ++i)
    {
        Playlist* p = playlistha[i].get();
        const std::vector<int>& songs = p->getSongIds();


        file << p->getId() << " "
             << p->getListenerId() << " "
             << std::quoted(p->getName()) << " "
             << songs.size();

        for (int j = 0; j < static_cast<int>(songs.size()); ++j)
        {
            file << " " << songs[j];
        }
        file << "\n";
    }
    file.close();
}

void PlaylistRepository::loadFromFile()
{
    std::ifstream file(filePath.c_str());
    if (!file.is_open()) return;

    playlistha.clear();
    int maxId = 0;

    int id, listenerId, songCount;
    std::string name;


    while (file >> id >> listenerId >> std::quoted(name) >> songCount)
    {
        std::unique_ptr<Playlist> playlist(new Playlist(id, listenerId, name));

        for (int i = 0; i < songCount; ++i)
        {
            int sId;
            file >> sId;
            playlist->addSong(sId);
        }

        if (id > maxId) maxId = id;
        playlistha.push_back(std::move(playlist));
    }

    nextId = maxId + 1;
    file.close();
}

bool PlaylistRepository::save(std::unique_ptr<Playlist> item)
{
    if (!item) return false;

    if (item->getId() == 0)
    {
        item->setId(generateId());
    }


    for (int i = 0; i < static_cast<int>(playlistha.size()); ++i)
    {
        if (playlistha[i]->getId() == item->getId()) return false;
    }

    playlistha.push_back(std::move(item));
    saveToFile();
    return true;
}

bool PlaylistRepository::remove(int id)
{
    for (int i = 0; i < static_cast<int>(playlistha.size()); ++i)
    {
        if (playlistha[i]->getId() == id)
        {
            playlistha.erase(playlistha.begin() + i);
            saveToFile();
            return true;
        }
    }
    return false;
}

Playlist* PlaylistRepository::search(int id) const
{
    for (int i = 0; i < static_cast<int>(playlistha.size()); ++i)
    {
        if (playlistha[i]->getId() == id) return playlistha[i].get();
    }
    return nullptr;
}

bool PlaylistRepository::insertSong(int playlistId, int songId)
{
    Playlist* p = search(playlistId);
    if (!p) return false;


    const std::vector<int>& songs = p->getSongIds();
    for (int i = 0; i < static_cast<int>(songs.size()); ++i)
    {
        if (songs[i] == songId) return false;
    }

    p->addSong(songId);
    saveToFile();
    return true;
}

bool PlaylistRepository::removeSong(int playlistId, int songId)
{
    Playlist* p = search(playlistId);
    if (!p) return false;

    p->removeSong(songId);
    saveToFile();
    return true;
}

std::vector<Playlist*> PlaylistRepository::playlists(int listenerId) const
{
    std::vector<Playlist*> result;
    for (int i = 0; i < static_cast<int>(playlistha.size()); ++i)
    {
        if (playlistha[i]->getListenerId() == listenerId)
        {
            result.push_back(playlistha[i].get());
        }
    }
    return result;
}
