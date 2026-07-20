#include "artistrepository.h"

ArtistRepository::ArtistRepository() {}
std::vector<Artist*> ArtistRepository::getArtists() const
{
    std::vector<Artist*> result;

    for (size_t i = 0; i < users.size(); ++i)
    {

        Artist* artist = dynamic_cast<Artist*>(users[i].get());

        if (artist != nullptr)
        {
            result.push_back(artist);
        }
    }

    return result;
}
