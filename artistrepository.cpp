#include "artistrepository.h"

ArtistRepository::ArtistRepository(AccountRepository& accountRepository)
    : accountRepository(accountRepository)
{
}

std::vector<Artist*> ArtistRepository::getArtists() const
{
    std::vector<Artist*> result;

    std::vector<std::unique_ptr<User>>& users = accountRepository.getUsers();

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

User* ArtistRepository::search(int id) const
{
    return accountRepository.search(id);
}

