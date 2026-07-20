#ifndef LISTENRREPOSITORY_H
#define LISTENRREPOSITORY_H

#include "accountrepository.h"

class listenrRepository : public AccountRepository
{
public:
    listenrRepository();

    void updatedLike(int listenerId, int songId, bool liked);

    bool isLiked(int listenerId, int songId) const;
};

#endif // LISTENRREPOSITORY_H
