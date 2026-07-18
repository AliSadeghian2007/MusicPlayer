#include "sharedfeaturesmanager.h"
#include<algorithm>
SharedFeaturesManager::SharedFeaturesManager(SongRepository& songRepo,
                                             AlbumRepository& albumRepo,
                                             PlaylistRepository& playlistRepo,
                                             AccountRepository& accountRepo)
    : songRepo(songRepo),
    albumRepo(albumRepo),
    playlistRepo(playlistRepo),
    accountRepo(accountRepo)
{
}

std::vector<Song> SharedFeaturesManager::searchSongsByName(const std::vector<Song>& songs, const std::string& name) const
{
    std::vector<Song> result;

    for (int i = 0; i < songs.size(); i++)
    {
        if (songs[i].getName() == name)
        {
            result.push_back(songs[i]);
        }
    }

    return result;
}

Artist* SharedFeaturesManager::searchArtistsByName(const std::string& name) const
{
    User* user = accountRepo.searchByUserName(name);
    return dynamic_cast<Artist*>(user);

}


std::vector<Song> SharedFeaturesManager::filterSongsByGenre(const std::vector<Song>& songs, const std::string& genre) const
{
    std::vector<Song> result;
    for(int i=0;i<songs.size();i++)
    {
        if(songs[i].getGenre()==genre)
        {
            result.push_back(songs[i]);
        }
    }
    return result;
}



std::vector<Song> SharedFeaturesManager::filterSongsByReleaseYear(const std::vector<Song>& songs,int releaseYear) const
{
    std::vector<Song> result;
    for(int i=0;i<songs.size();i++)
    {
        if(songs[i].getReleaseYear()==releaseYear)
        {
            result.push_back(songs[i]);
        }
    }
    return result;
}



std::vector<Song> SharedFeaturesManager::sortSongsByName(std::vector<Song> songs, bool ascending) const
{
    if (ascending)
    {
        std::sort(songs.begin(), songs.end(), [](const Song& a, const Song& b) {
            return a.getName() < b.getName();
        });
    }
    else
    {
        std::sort(songs.begin(), songs.end(), [](const Song& a, const Song& b) {
            return a.getName() > b.getName();
        });
    }

    return songs;
}

std::vector<Song> SharedFeaturesManager::sortSongsByReleaseYear(std::vector<Song> songs, bool ascending) const
{
    if (ascending)
    {
        std::sort(songs.begin(), songs.end(), [](const Song& a, const Song& b) {
            return a.getReleaseYear() < b.getReleaseYear();
        });
    }
    else
    {
        std::sort(songs.begin(), songs.end(), [](const Song& a, const Song& b) {
            return a.getReleaseYear() > b.getReleaseYear();
        });
    }

    return songs;
}

std::vector<Song> SharedFeaturesManager::sortSongsByGenre(std::vector<Song> songs, bool ascending) const
{
    if (ascending)
    {
        std::sort(songs.begin(), songs.end(), [](const Song& a, const Song& b) {
            return a.getGenre() < b.getGenre();
        });
    }
    else
    {
        std::sort(songs.begin(), songs.end(), [](const Song& a, const Song& b) {
            return a.getGenre() > b.getGenre();
        });
    }

    return songs;
}

std::vector<Album> SharedFeaturesManager::sortAlbumsByName(std::vector<Album> albums, bool ascending) const
{
    if (ascending)
    {
        std::sort(albums.begin(), albums.end(), [](const Album& a, const Album& b) {
            return a.getName() < b.getName();
        });
    }
    else
    {
        std::sort(albums.begin(), albums.end(), [](const Album& a, const Album& b) {
            return a.getName() > b.getName();
        });
    }

    return albums;
}

std::vector<Playlist> SharedFeaturesManager::sortPlaylistsByName(std::vector<Playlist> playlists, bool ascending) const
{
    if (ascending)
    {
        std::sort(playlists.begin(), playlists.end(), [](const Playlist& a, const Playlist& b) {
            return a.getName() < b.getName();
        });
    }
    else
    {
        std::sort(playlists.begin(), playlists.end(), [](const Playlist& a, const Playlist& b) {
            return a.getName() > b.getName();
        });
    }

    return playlists;
}
