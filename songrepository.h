#ifndef SONGREPOSITORY_H
#define SONGREPOSITORY_H
#include<vector>
#include<memory>
#include "abstractrepository.h"
#include "song.h"
class PlaylistRepository;
class listenrRepository;

class SongRepository : public AbstractRepository<Song>
{
private:
    std::vector<std::unique_ptr<Song>>songs;
    PlaylistRepository* playlistRepo=nullptr;
    listenrRepository* listenerRepo=nullptr;
    int nextId;
public:
    SongRepository();
    int generateId();
    bool save(std::unique_ptr<Song> item) override ;
    bool remove(int id) override;
    Song* search (int id) const override;

    void setListenerRepository(listenrRepository* Repo){listenerRepo=Repo;}
    void setPlaylistRepository(PlaylistRepository* repo){playlistRepo=repo;}
    std::vector<Song*> singleSongs(int artistId) const;
    std::vector<Song*> getByAlbum(int albumId) const;
    std::vector<Song*> getByArtist(int artistId) const;
    std::vector<Song*> getByPlaylist(int playlistId) const;
    std::vector<Song*> getByLikedSongs(int listenerId) const ;


};

#endif // SONGREPOSITORY_H
