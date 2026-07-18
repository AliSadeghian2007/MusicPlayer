#ifndef SHAREDFEATURESMANAGER_H
#define SHAREDFEATURESMANAGER_H

#include <vector>
#include <string>

#include "song.h"
#include "album.h"
#include "playlist.h"
#include "artist.h"
#include "songrepository.h"
#include "albumrepository.h"
#include "playlistrepository.h"
#include "accountrepository.h"

class SharedFeaturesManager
{
private:
    SongRepository& songRepo;
    AlbumRepository& albumRepo;
    PlaylistRepository& playlistRepo;
    AccountRepository& accountRepo;

public:
    SharedFeaturesManager(SongRepository& songRepo,
                          AlbumRepository& albumRepo,
                          PlaylistRepository& playlistRepo,
                          AccountRepository& accountRepo);



    std::vector<Song> searchSongsByName(const std::vector<Song>& songs,
                                        const std::string& name) const;
    Artist* searchArtistsByName(const std::string& name) const;

    std::vector<Song> filterSongsByGenre(const std::vector<Song>& songs,
                                         const std::string& genre) const;
    std::vector<Song> filterSongsByReleaseYear(const std::vector<Song>& songs,
                                               int releaseYear) const;

    std::vector<Song> sortSongsByName(std::vector<Song> songs,bool ascending) const;
    std::vector<Song> sortSongsByReleaseYear(std::vector<Song> songs,bool ascending) const;
    std::vector<Song> sortSongsByGenre(std::vector<Song> songs,bool ascending) const;

    std::vector<Album> sortAlbumsByName(std::vector<Album> albums,bool ascending) const;
    std::vector<Playlist> sortPlaylistsByName(std::vector<Playlist> playlists,bool ascending) const;
};

#endif // SHAREDFEATURESMANAGER_H
