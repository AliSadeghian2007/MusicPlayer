#include "listenermanager.h"

ListenerManager::ListenerManager()
{
    songRepository.setListenerRepository(&listenerRepository);
    songRepository.setPlaylistRepository(&playlistRepository);
}


std::vector<Artist*> ListenerManager::getAllArtists() const
{
    return artistRepository.getArtists();
}

std::vector<Album*> ListenerManager::getArtistAlbums(int artistId) const
{
    return albumRepository.albums(artistId);
}

std::vector<Song*> ListenerManager::getArtistSingles(int artistId) const
{
    return songRepository.singleSongs(artistId);
}

Artist* ListenerManager::getArtistById(int artistId) const
{
    User* user = artistRepository.search(artistId);
    Artist* artist = dynamic_cast<Artist*>(user);
    return artist;
}



std::vector<Playlist*> ListenerManager::getPlaylistsByUserId(int userId) const
{
    return playlistRepository.playlists(userId);
}


std::vector<Song*> ListenerManager::getSongsInPlaylist(int playlistId) const
{
    std::vector<Song*> result;


    Playlist* playlist = playlistRepository.search(playlistId);
    if (playlist == nullptr) {
        return result;
    }


    const std::vector<int>& songIds = playlist->getSongIds();


    for (size_t i = 0; i < songIds.size(); ++i) {
        Song* song = songRepository.search(songIds[i]);
        if (song != nullptr) {
            result.push_back(song);
        }
    }

    return result;
}




bool ListenerManager::createPlaylist(
    int listenerId,
    const std::string& name)
{
    if (name.empty())
    {
        return false;
    }

    std::unique_ptr<Playlist> playlist=std::make_unique<Playlist>(0,listenerId,name);

    return playlistRepository.save(std::move(playlist));
}




bool ListenerManager::editPlaylist(
    int playlistId,
    int userId,
    const std::string& newName)
{
    Playlist* playlist = playlistRepository.search(playlistId);

    if (playlist == nullptr)
    {
        return false;
    }

    if (playlist->getListenerId() != userId)
    {
        return false;
    }

    if (newName.empty())
    {
        return false;
    }

    playlist->setName(newName);

    return true;
}


bool ListenerManager::addSongToPlaylist(
    int playlistId,
    int userId,
    int songId)
{
    Playlist* playlist = playlistRepository.search(playlistId);

    if (playlist == nullptr)
    {
        return false;
    }

    if (playlist->getListenerId() != userId)
    {
        return false;
    }

    Song* song = songRepository.search(songId);

    if (song == nullptr)
    {
        return false;
    }

    return playlistRepository.insertSong(playlistId, songId);
}



bool ListenerManager::removeSongFromPlaylist(
    int playlistId,
    int userId,
    int songId)
{
    Playlist* playlist = playlistRepository.search(playlistId);

    if (playlist == nullptr)
    {
        return false;
    }

    if (playlist->getListenerId() != userId)
    {
        return false;
    }

    return playlistRepository.removeSong(playlistId, songId);
}

bool ListenerManager::deletePlaylist(int listenerId, int playlistId)
{
    Playlist* playlist = playlistRepository.search(playlistId);

    if (playlist == nullptr)
    {
        return false;
    }

    if (playlist->getListenerId() != listenerId)
    {
        return false;
    }

    return playlistRepository.remove(playlistId);
}

bool ListenerManager::likeSong(int listenerId, int songId)
{
    Song* song = songRepository.search(songId);
    if (song == nullptr)
    {
        return false;
    }

    if (listenerRepository.isLiked(listenerId, songId))
    {
        return false;
    }

    listenerRepository.updatedLike(listenerId, songId, true);
    return listenerRepository.isLiked(listenerId, songId);
}

bool ListenerManager::unlikeSong(int listenerId, int songId)
{
    if (!listenerRepository.isLiked(listenerId, songId))
    {
        return false;
    }

    listenerRepository.updatedLike(listenerId, songId, false);
    return !listenerRepository.isLiked(listenerId, songId);
}

bool ListenerManager::isSongLiked(int listenerId, int songId) const
{
    return listenerRepository.isLiked(listenerId, songId);
}

std::vector<Song*> ListenerManager::getLikedSongs(int listenerId) const
{
    return songRepository.getByLikedSongs(listenerId);
}





