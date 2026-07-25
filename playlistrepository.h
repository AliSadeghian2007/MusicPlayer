#ifndef PLAYLISTREPOSITORY_H
#define PLAYLISTREPOSITORY_H

#include "abstractrepository.h"
#include "playlist.h"
#include <memory>
#include <vector>
#include <string>

class PlaylistRepository : public AbstractRepository<Playlist>
{
private:
    std::vector<std::unique_ptr<Playlist>> playlistha;
    int nextId;
    std::string filePath;


public:
    PlaylistRepository();

    void loadFromFile();
    void saveToFile() const;

    int generateId();
    bool save(std::unique_ptr<Playlist> item) override;
    bool remove(int id) override;
    Playlist* search(int id) const override;

    bool insertSong(int playlistId, int songId);
    bool removeSong(int playlistId, int songId);
    std::vector<Playlist*> playlists(int listenerId) const;
};

#endif
