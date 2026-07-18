#ifndef ALBUM_H
#define ALBUM_H

#include <string>


class Album
{
public:
    Album(int id, int artistId, const std::string& name, const std::string& coverPath);

    int getId() const
    {
        return id;
    }

    int getArtistId() const
    {
        return artistId;
    }

    const std::string& getName() const
    {
        return name;
    }

    const std::string& getCoverPath() const
    {
        return coverPath;
    }

    void setId(int id)
    {
        this->id=id;
    }
private:
    std::string coverPath;
    int artistId;
    std::string name;
    int id;
};

#endif
