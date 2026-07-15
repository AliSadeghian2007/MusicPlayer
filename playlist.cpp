#include "playlist.h"

Playlist::Playlist(int id, int listenerId, const std::string &name)
{
    this->id=id;
    this->listenerId=listenerId;
    this->name=name;
}
void Playlist::removeSong(int songId)
{
    for(int i=0;i<songIds.size();i++)
    {
        if(songIds[i]==songId)
        {
            songIds.erase(songIds.begin()+i);
            return;
        }

    }
    return;
}
