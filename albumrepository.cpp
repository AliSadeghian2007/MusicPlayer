#include "albumrepository.h"
#include <fstream>
#include <iomanip>

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



bool AlbumRepository::saveToFile(const std::string &filePath) const
{
    std::ofstream out(filePath.c_str(), std::ios::trunc);
    if (!out.is_open())
    {
        return false;
    }

    for (int i = 0; i < static_cast<int>(albumha.size()); ++i)
    {
        const Album *album = albumha[i].get();
        if (album != nullptr)
        {
            out << album->getId() << ' '
                << album->getArtistId() << ' '
                << std::quoted(album->getName()) << ' '
                << std::quoted(album->getCoverPath()) << '\n';
        }
    }

    return true;
}

bool AlbumRepository::loadFromFile(const std::string &filePath)
{
    std::ifstream in(filePath.c_str());
    if (!in.is_open())
    {
        return true;
    }

    albumha.clear();

    int id = 0;
    int artistId = 0;
    std::string name;
    std::string coverPath;

    while (in >> id >> artistId >> std::quoted(name) >> std::quoted(coverPath))
    {
        std::unique_ptr<Album> album(
            new Album(id, artistId, name, coverPath));

        albumha.push_back(std::move(album));
    }

    return true;
}
