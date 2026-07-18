#include "album.h"

Album::Album(int id,int artistId,const std::string&name,const std::string& coverPath)
{
    this->id=id;
    this->coverPath=coverPath;
    this->artistId=artistId;
    this->name=name;
}
