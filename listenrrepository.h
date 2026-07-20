#ifndef LISTENRREPOSITORY_H
#define LISTENRREPOSITORY_H

#include "accountrepository.h"

class listenrRepository
{
private:
    AccountRepository& accountRepository;

public:
    listenrRepository(AccountRepository& accountRepository);

    User* search(int id) const;
    void updatedLike(int listenerId, int songId, bool liked);
    bool isLiked(int listenerId, int songId) const;
};

#endif // LISTENRREPOSITORY_H
