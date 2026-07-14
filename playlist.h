#ifndef PLAYLIST_H
#define PLAYLIST_H
#include<string>
#include<vector>
class Playlist
{
public:
    Playlist();
    int getId()const
    {
    return id;
    }
    int getListenerId()
    {
        return listenerId;
    }
    void addSong(int songId) { songIds.push_back(songId); }
    const std::vector<int>& getSongIds()const { return songIds; }
private:
    int listenerId;
    std::string name;
    int id;
     std::vector<int> songIds;
};

#endif // PLAYLIST_H
