#include "albumrepository.h"

AlbumRepository::AlbumRepository() : nextId(1) {}

int AlbumRepository::generateId()
{
    return nextId++;
}
bool AlbumRepository::save(std::unique_ptr<Album> a)
{
    if (!a) return false;

    if (a->getId() == 0)
    {
        a->setId(generateId());
    }

    for (int i = 0; i < albumha.size(); i++)
    {
        if (a->getId() == albumha[i]->getId())
        {
            return false;
        }
    }

    albumha.push_back(std::move(a));
    return true;
}


bool AlbumRepository::remove(int id)
{
    int size=albumha.size();
    for(int i=0;i<size;i++)
    {
        if(albumha[i]->getId()==id)
        {
            albumha.erase(albumha.begin()+(i));
            return true;
        }
    }
    return false;
}



Album* AlbumRepository::search(int id) const
{
    for(int i=0;i<albumha.size();i++)
    {
        if(albumha[i]->getId()==id)
        {
            return albumha[i].get();
        }
    }
    return nullptr;
}







std::vector<Album*> AlbumRepository::albums(int artistId) const
{
    std::vector<Album*>result;
    for(int i=0;i<albumha.size();i++)
    {
        if(albumha[i]->getArtistId()==artistId)
        {
            result.push_back(albumha[i].get());
        }
    }
    return result;
}