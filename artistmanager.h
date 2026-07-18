#ifndef ARTISTMANAGER_H
#define ARTISTMANAGER_H
#include "albumrepository.h"
class ArtistManager
{
private:
    AlbumRepository albumRepo;
public:
    ArtistManager();

    void createAlbum(std::string coverPath,int artistId,std::string name,int id);
};

#endif // ARTISTMANAGER_H
