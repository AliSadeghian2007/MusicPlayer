#ifndef ALBUM_H
#define ALBUM_H
#include<string>
using namespace std;
class Album
{
public:
    Album();
private:
    string coverPath;
    int artistId;
    string name;
    int id;
};

#endif // ALBUM_H
