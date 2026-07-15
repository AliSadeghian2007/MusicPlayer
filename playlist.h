#ifndef PLAYLIST_H
#define PLAYLIST_H
#include<string>
#include<vector>
class Playlist
{
public:
    Playlist(int id, int listenerId, const std::string& name);
    int getId()const
    {
    return id;
    }
    int getListenerId() const
    {
        return listenerId;
    }
    void addSong(int songId) { songIds.push_back(songId); }
    const std::vector<int>& getSongIds()const { return songIds; }
    std::string getName() const{return name;}
    void removeSong(int songId);

private:
    int listenerId;
    std::string name;
    int id;
    std::vector<int> songIds;
};

#endif // PLAYLIST_H
