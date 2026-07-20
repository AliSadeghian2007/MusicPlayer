#ifndef LISTENERMANAGER_H
#define LISTENERMANAGER_H

#include <vector>
#include "artistrepository.h"
#include "albumrepository.h"
#include "songrepository.h"
#include "playlistrepository.h"
#include "listenrrepository.h"
class ListenerManager
{
private:
    ArtistRepository artistRepository;
    AlbumRepository albumRepository;
    SongRepository songRepository;
    PlaylistRepository playlistRepository;
    listenrRepository listenerRepository;

public:
    ListenerManager();
    std::vector<Artist*> getAllArtists() const;
    std::vector<Album*> getArtistAlbums(int artistId) const;
    std::vector<Song*> getArtistSingles(int artistId) const;
    Artist* getArtistById(int artistId) const;

    std::vector<Playlist*> getPlaylistsByUserId(int userId) const;
    std::vector<Song*> getSongsInPlaylist(int playlistId) const;


    bool createPlaylist(int listenerId, const std::string& name);


    bool editPlaylist(int playlistId, int userId, const std::string& newName);
    bool addSongToPlaylist(int playlistId, int userId, int songId);
    bool removeSongFromPlaylist(int playlistId, int userId, int songId);


    bool deletePlaylist(int listenerId, int playlistId);


    bool likeSong(int listenerId, int songId);
    bool unlikeSong(int listenerId, int songId);
    bool isSongLiked(int listenerId, int songId) const;
    std::vector<Song*> getLikedSongs(int listenerId) const;

};

#endif
