#include "artistmanager.h"
#include "album.h"
#include "artist.h"
#include "song.h"
#include <memory>

ArtistManager::ArtistManager(AlbumRepository& albumRepo,
                             SongRepository& songRepo,
                             AccountRepository& accountRepo)
    : albumRepo(albumRepo),
    songRepo(songRepo),
    accountRepo(accountRepo)
{
}

bool ArtistManager::isArtist(int artistId) const
{
    User* user = accountRepo.search(artistId);

    if (user == nullptr)
    {
        return false;
    }

    Artist* artist = dynamic_cast<Artist*>(user);

    if (artist == nullptr)
    {
        return false;
    }

    return true;
}

void ArtistManager::createAlbum(const std::string& coverPath,
                                int artistId,
                                const std::string& name)
{
    if (!isArtist(artistId))
    {
        return;
    }

    std::unique_ptr<Album> album =
        std::make_unique<Album>(0, artistId, name, coverPath);

    albumRepo.save(std::move(album));
}

void ArtistManager::createSong(int albumId,
                               int artistId,
                               const std::string& name,
                               const std::string& fileName,
                               const std::string& genre,
                               int releaseYear,
                               const std::string& coverPath)
{
    if (!isArtist(artistId))
    {
        return;
    }

    int finalAlbumId = 0;

    if (albumId > 0)
    {
        Album* album = albumRepo.search(albumId);

        if (album != nullptr && album->getArtistId() == artistId)
        {
            finalAlbumId = albumId;
        }
    }

    std::unique_ptr<Song> song =
        std::make_unique<Song>(
            0,
            artistId,
            finalAlbumId,
            name,
            fileName,
            genre,
            releaseYear,
            coverPath);

    songRepo.save(std::move(song));
}

bool ArtistManager::editSong(int artistId,
                             int songId,
                             const std::string& name,
                             const std::string& fileName,
                             const std::string& genre,
                             int releaseYear,
                             const std::string& coverPath,
                             int albumId)
{
    if (!isArtist(artistId))
    {
        return false;
    }

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

bool ArtistManager::editAlbum(int artistId,
                              int albumId,
                              const std::string& name,
                              const std::string& coverPath)
{
    if (!isArtist(artistId))
    {
        return false;
    }

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
    if (!isArtist(artistId))
    {
        return false;
    }

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
    if (!isArtist(artistId))
    {
        return false;
    }

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
    if (!isArtist(artistId))
    {
        return std::vector<Album*>();
    }

    return albumRepo.albums(artistId);
}

std::vector<Song*> ArtistManager::getSingles(int artistId) const
{
    if (!isArtist(artistId))
    {
        return std::vector<Song*>();
    }

    return songRepo.singleSongs(artistId);
}

std::vector<Song*> ArtistManager::getAlbumSongs(int artistId, int albumId) const
{
    std::vector<Song*> result;

    if (!isArtist(artistId))
    {
        return result;
    }

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

