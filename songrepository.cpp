#include "songrepository.h"
#include "listenrrepository.h"
#include "playlist.h"
#include "playlistrepository.h"
#include "listener.h"
SongRepository::SongRepository() : nextId(1) {}

int SongRepository::generateId()
{
    return nextId++;
}

bool SongRepository::save(std::unique_ptr<Song> a)
{
    if (!a) return false;

    if (a->get_Id() == 0)
    {
        a->setId(generateId());
    }

    for (int i = 0; i < songs.size(); i++)
    {
        if (a->get_Id() == songs[i]->get_Id())
        {
            return false;
        }
    }

    songs.push_back(std::move(a));
    return true;
}


bool SongRepository::remove(int id)
{
    int size=songs.size();
    for(int i=0;i<size;i++)
    {
        if(songs[i]->get_Id()==id)
        {
            songs.erase(songs.begin()+(i));
            return true;
        }
    }
    return false;
}



Song* SongRepository::search(int id) const
{
    for(int i=0;i<songs.size();i++)
    {
        if(songs[i]->get_Id()==id)
        {
            return songs[i].get();
        }
    }
    return nullptr;
}

std::vector<Song*> SongRepository::singleSongs(int artistId) const
{
    std::vector<Song*>singel;
    int size=songs.size();
    for(int i=0;i<size;i++)
    {
        if(songs[i]->getartistId()==artistId && songs[i]->getAlbumId()==-1)
        {
            singel.push_back(songs[i].get());
        }
    }
    return singel;
}


std::vector<Song*> SongRepository::getByAlbum(int albumId) const
{
    std::vector<Song*> albumSongs;
    int size=songs.size();
    for(int i=0;i<size;i++)
    {
        if( songs[i]->getAlbumId()==albumId)
        {
            albumSongs.push_back(songs[i].get());
        }
    }
    return albumSongs;
}


std::vector<Song*> SongRepository::getByArtist(int artistId) const
{
    std::vector<Song*> artistSongs;
    int size=songs.size();
    for(int i=0;i<size;i++)
    {
        if( songs[i]->getartistId()==artistId)
        {
            artistSongs.push_back(songs[i].get());
        }
    }
    return artistSongs;
}


std::vector<Song*> SongRepository::getByPlaylist(int playlistId) const
{
    std::vector<Song*> result;

    if(!playlistRepo) return result;
    Playlist* targetPlaylist=playlistRepo->search(playlistId);
    if (targetPlaylist)
    {
        std::vector<int> ids=targetPlaylist->getSongIds();

        for (int i = 0; i < ids.size(); i++)
        {
            Song* s = search(ids[i]);
            if (s)
            {
                result.push_back(s);
            }
        }

    }
    return result;
}



std::vector<Song*> SongRepository::getByLikedSongs(int listenerId) const
{
    std::vector<Song*>result;
    if(!listenerRepo)
    {
        return result;
    }
    User* user=listenerRepo->search(listenerId);
    if(user==nullptr){return result;}

    Listener* foundListener=dynamic_cast<Listener*>(user);
    if(foundListener==nullptr){return result;}

    std::vector<int>likedSongIds=foundListener->getIdLikedSong();
    for(int i=0;i<likedSongIds.size();i++)
    {
        Song* song=search(likedSongIds[i]);
        if(song!=nullptr)
        {
            result.push_back(song);
        }
    }
    return result;



}