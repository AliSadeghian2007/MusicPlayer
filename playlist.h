#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>

class Playlist
{
public:
    Playlist(int id, int listenerId, const std::string& name);
    void setId(int id){this->id=id;}
    int getId() const;
    int getListenerId() const;
    void addSong(int songId);
    const std::vector<int>& getSongIds() const;
    std::string getName() const;
    void removeSong(int songId);

private:
    int listenerId;
    std::string name;
    int id;
    std::vector<int> songIds;
};

#endif

