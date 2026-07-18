#include "playlistrepository.h"

PlaylistRepository::PlaylistRepository() : nextId(1) {}

int PlaylistRepository::generateId()
{
    return nextId++;
}

bool PlaylistRepository::save(std::unique_ptr<Playlist> a)
{
    if (!a) return false;

    if (a->getId() == 0)
    {
        a->setId(generateId());
    }

    for (int i = 0; i < playlistha.size(); i++)
    {
        if (a->getId() == playlistha[i]->getId())
        {
            return false;
        }
    }

    playlistha.push_back(std::move(a));
    return true;
}


bool PlaylistRepository::remove(int id)
{
    int size=playlistha.size();
    for(int i=0;i<size;i++)
    {
        if(playlistha[i]->getId()==id)
        {
            playlistha.erase(playlistha.begin()+(i));
            return true;
        }
    }
    return false;
}



Playlist* PlaylistRepository::search(int id) const
{
    for(int i=0;i<playlistha.size();i++)
    {
        if(playlistha[i]->getId()==id )
        {
            return playlistha[i].get();
        }
    }
    return nullptr;
}



bool PlaylistRepository::insertSong(int playlistId,int songId)
{
    for (int i=0;i<playlistha.size();i++)
    {
        if (playlistha[i]->getId()==playlistId)
        {
            const std::vector<int>& a=playlistha[i]->getSongIds();
            for (int j=0;j<a.size();j++)
            {
                if(songId==a[j])
                {
                    return false;
                }
            }
            playlistha[i]->addSong(songId);
            return true;
        }
    }
    return false;



}


bool PlaylistRepository::removeSong(int playlistId,int songId)
{
    for (int i=0;i<playlistha.size();i++)
    {
        if (playlistha[i]->getId()==playlistId)
        {
            const std::vector<int>& a=playlistha[i]->getSongIds();
            for (int j=0;j<a.size();j++)
            {
                if(songId==a[j])
                {
                    playlistha[i]->removeSong(songId);
                    return true;
                }
            }
            return false;
        }
    }
    return false;


}


std::vector<Playlist*> PlaylistRepository::playlists(int listenerId) const
{
    std::vector<Playlist*>result;
    for(int i=0;i<playlistha.size();i++)
    {
        if(playlistha[i]->getListenerId()==listenerId)
        {
            result.push_back(playlistha[i].get());
        }
    }
    return result;

}