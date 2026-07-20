#ifndef ARTISTREPOSITORY_H
#define ARTISTREPOSITORY_H

#include "accountrepository.h"
#include "artist.h"

class ArtistRepository : public AccountRepository
{
public:
    ArtistRepository();
    std::vector<Artist*> getArtists() const;

};

#endif // ARTISTREPOSITORY_H
