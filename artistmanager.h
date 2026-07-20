#ifndef ARTISTMANAGER_H
#define ARTISTMANAGER_H

#include "accountrepository.h"
#include "albumrepository.h"
#include "songrepository.h"
#include <string>
#include <vector>

class ArtistManager
{
private:
    AlbumRepository& albumRepo;
    SongRepository& songRepo;
    AccountRepository& accountRepo;

    bool isArtist(int artistId) const;

public:
    ArtistManager(AlbumRepository& albumRepo,
                  SongRepository& songRepo,
                  AccountRepository& accountRepo);

    void createAlbum(const std::string& coverPath, int artistId, const std::string& name);

    void createSong(int albumId, int artistId, const std::string& name,
                    const std::string& fileName, const std::string& genre,
                    int releaseYear, const std::string& coverPath);

    bool editSong(int artistId, int songId, const std::string& name,
                  const std::string& fileName, const std::string& genre,
                  int releaseYear, const std::string& coverPath, int albumId);

    bool editAlbum(int artistId, int albumId, const std::string& name,
                   const std::string& coverPath);

    bool deleteSong(int artistId, int songId);
    bool deleteAlbum(int artistId, int albumId);

    std::vector<Album*> getAlbums(int artistId) const;
    std::vector<Song*> getSingles(int artistId) const;
    std::vector<Song*> getAlbumSongs(int artistId, int albumId) const;
};

#endif
