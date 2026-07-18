#include "artistmanager.h"

ArtistManager::ArtistManager() {}
void ArtistManager::createAlbum(std::string coverPath,int artistId,std::string name,int id)
{
    std::unique_ptr<Album> a= std::make_unique<Album>(id, artistId, name, coverPath);
    albumRepo.save(std::move(a));
}