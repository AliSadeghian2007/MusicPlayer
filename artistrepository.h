#ifndef ARTISTREPOSITORY_H
#define ARTISTREPOSITORY_H

#include <vector>
#include "accountrepository.h"
#include "artist.h"

class ArtistRepository
{
private:
    AccountRepository& accountRepository;

public:
    ArtistRepository(AccountRepository& accountRepository);

    std::vector<Artist*> getArtists() const;
    User* search(int id) const;
};

#endif // ARTISTREPOSITORY_H
