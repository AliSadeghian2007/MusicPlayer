#ifndef ALBUMREPOSITORY_H
#define ALBUMREPOSITORY_H
#include "album.h"
#include "abstractrepository.h"
#include <vector>
#include <memory>

class AlbumRepository : public AbstractRepository<Album>
{
private:
    std::vector<std::unique_ptr<Album>>albumha;
public:
    AlbumRepository();
    bool save(std::unique_ptr<Album> item) override;
    bool remove(int id) override;
    Album* search (int id) const override;

    std::vector<Album*> albums(int artistId)const;
};

#endif // ALBUMREPOSITORY_H
