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
    int nextId;
public:
    AlbumRepository();
    int generateId();
    bool save(std::unique_ptr<Album> item) override;
    bool remove(int id) override;
    Album* search (int id) const override;

    std::vector<Album*> albums(int artistId)const;

    bool saveToFile(const std::string &filePath) const;
    bool loadFromFile(const std::string &filePath);

};

#endif // ALBUMREPOSITORY_H
