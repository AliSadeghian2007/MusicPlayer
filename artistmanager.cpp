#include "artistmanager.h"
#include "album.h"
#include "song.h"
#include <memory>

ArtistManager::ArtistManager() {}

void ArtistManager::createAlbum(const std::string& coverPath, int artistId, const std::string& name)
{
    std::unique_ptr<Album> album = std::make_unique<Album>(0, artistId, name, coverPath);
    albumRepo.save(std::move(album));
}

void ArtistManager::createSong(int albumId, int artistId, const std::string& name,
                               const std::string& fileName, const std::string& genre,
                               int releaseYear, const std::string& coverPath)
{
    int finalAlbumId = 0;

    if (albumId > 0)
    {
        Album* album = albumRepo.search(albumId);
        if (album != nullptr && album->getArtistId() == artistId)
        {
            finalAlbumId = albumId;
        }
    }

    std::unique_ptr<Song> song = std::make_unique<Song>(
        0,
        artistId,
        finalAlbumId,
        name,
        fileName,
        genre,
        releaseYear,
        coverPath
        );

    songRepo.save(std::move(song));
}

bool ArtistManager::editSong(int artistId, int songId, const std::string& name,
                             const std::string& fileName, const std::string& genre,
                             int releaseYear, const std::string& coverPath, int albumId)
{
    Song* song = songRepo.search(songId);
    if (song == nullptr)
    {
        return false;
    }

    if (song->getartistId() != artistId)
    {
        return false;
    }

    int finalAlbumId = 0;

    if (albumId > 0)
    {
        Album* album = albumRepo.search(albumId);
        if (album == nullptr)
        {
            return false;
        }

        if (album->getArtistId() != artistId)
        {
            return false;
        }

        finalAlbumId = albumId;
    }

    song->setName(name);
    song->setFileName(fileName);
    song->setGenre(genre);
    song->setReleaseYear(releaseYear);
    song->setCoverPath(coverPath);
    song->setAlbumId(finalAlbumId);

    return true;
}

bool ArtistManager::editAlbum(int artistId, int albumId, const std::string& name,
                              const std::string& coverPath)
{
    Album* album = albumRepo.search(albumId);
    if (album == nullptr)
    {
        return false;
    }

    if (album->getArtistId() != artistId)
    {
        return false;
    }

    album->setName(name);
    album->setCoverPath(coverPath);

    return true;
}


bool ArtistManager::deleteSong(int artistId, int songId)
{
    Song* song = songRepo.search(songId);
    if (song == nullptr)
    {
        return false;
    }

    if (song->getartistId() != artistId)
    {
        return false;
    }

    return songRepo.remove(songId);
}

bool ArtistManager::deleteAlbum(int artistId, int albumId)
{
    Album* album = albumRepo.search(albumId);
    if (album == nullptr)
    {
        return false;
    }

    if (album->getArtistId() != artistId)
    {
        return false;
    }

    std::vector<Song*> songs = songRepo.getByAlbum(albumId);

    for (size_t i = 0; i < songs.size(); i++)
    {
        if (songs[i] != nullptr)
        {
            songRepo.remove(songs[i]->get_Id());
        }
    }

    return albumRepo.remove(albumId);
}

std::vector<Album*> ArtistManager::getAlbums(int artistId) const
{
    return albumRepo.albums(artistId);
}

std::vector<Song*> ArtistManager::getSingles(int artistId) const
{
    return songRepo.singleSongs(artistId);
}

std::vector<Song*> ArtistManager::getAlbumSongs(int artistId, int albumId) const
{
    std::vector<Song*> result;

    Album* album = albumRepo.search(albumId);
    if (album == nullptr)
    {
        return result;
    }

    if (album->getArtistId() != artistId)
    {
        return result;
    }

    result = songRepo.getByAlbum(albumId);
    return result;
}






