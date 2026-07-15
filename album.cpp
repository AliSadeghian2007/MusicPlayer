#include "album.h"

Album::Album(int id,int artistid,const std::string&name,const std::string& coverPath)
{
    this->coverPath=coverPath;
    this->artistId=artistId;
    this->name=name;
    this->id=id;
}
