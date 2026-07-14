#ifndef PLAYLISTREPOSITORY_H
#define PLAYLISTREPOSITORY_H
#include<vector>
#include<memory>
#include "abstractrepository.h"
#include "playlist.h"
class PlaylistRepository : public AbstractRepository<Playlist>
{
private:
    std::vector<std::unique_ptr<Playlist>> playlistha;
public:
    PlaylistRepository();
    bool save(std::unique_ptr<Playlist> item) override;
    bool remove(int id) override;
    Playlist* search (int id) const override;

    bool insertSong(int playlistId,int songId);
    bool removeSong(int playlistId,int songId);
    std::vector<Playlist*> playlists(int listenerId);

};

#endif // PLAYLISTREPOSITORY_H
