#ifndef SONG_H
#define SONG_H

#include <string>

class Song
{
public:
    Song();

    Song(int id, int artistId, int albumId, const std::string& name,
         const std::string& fileName, const std::string& genre,
         int releaseYear, const std::string& coverPath);

    int get_Id() const { return id; }
    int getartistId() const { return artistId; }
    int getAlbumId() const { return albumId; }

    int getReleaseYear() const { return releaseYear; }
    const std::string& getFileName() const { return fileName; }
    const std::string& getGenre() const { return genre; }
    const std::string& getCoverPath() const { return coverPath; }
    const std::string& getName() const { return name; }

    void setId(int id) { this->id = id; }
    void setartistId(int artistId) { this->artistId = artistId; }
    void setAlbumId(int albumId) { this->albumId = albumId; }
    void setReleaseYear(int releaseYear) { this->releaseYear = releaseYear; }
    void setFileName(const std::string& fileName) { this->fileName = fileName; }
    void setGenre(const std::string& genre) { this->genre = genre; }
    void setCoverPath(const std::string& coverPath) { this->coverPath = coverPath; }
    void setName(const std::string& name) { this->name = name; }

private:
    int id;
    std::string fileName;
    std::string genre;
    int releaseYear;
    std::string coverPath;
    int albumId;
    int artistId;
    std::string name;
};

#endif // SONG_H
