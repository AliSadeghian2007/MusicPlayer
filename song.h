#ifndef SONG_H
#define SONG_H

#include <string>
using namespace std;

class Song
{
public:
    Song();
private:
    int id;
    string fileName;
    string genre;
    int releaseYear;
    string coverPath;
    int albumId;
    int artistId;
    string name;
};

#endif // SONG_H
