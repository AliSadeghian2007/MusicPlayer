#include "song.h"

Song::Song()
    : id(0),
    fileName(""),
    genre(""),
    releaseYear(0),
    coverPath(""),
    albumId(0),
    artistId(0),
    name("")
{
}

Song::Song( int id,int artistId, int albumId, const std::string& name,
           const std::string& fileName, const std::string& genre,
           int releaseYear, const std::string& coverPath)
    :
    id(id),
    fileName(fileName),
    genre(genre),
    releaseYear(releaseYear),
    coverPath(coverPath),
    albumId(albumId),
    artistId(artistId),
    name(name)
{
}

