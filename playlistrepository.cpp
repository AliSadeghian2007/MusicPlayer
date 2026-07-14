#include "playlistrepository.h"

PlaylistRepository::PlaylistRepository() {}
bool PlaylistRepository::save(std::unique_ptr<Playlist>a)
{
    if (!a) return false;

    for(int i=0;i<playlistha.size();i++)
    {

        if (a->getId()==playlistha[i]->getId())
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