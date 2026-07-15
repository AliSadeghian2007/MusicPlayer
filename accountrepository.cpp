#include "accountrepository.h"

AccountRepository::AccountRepository() {}


bool AccountRepository::save(std::unique_ptr<User>a)
{
    for(int i=0;i<users.size();i++)
    {
        if (a->getId()==users[i]->getId() || a->getUserName()==users[i]->getUserName())
        {

            return false;
        }
    }
    users.push_back(std::move(a));
    return true;
}


bool AccountRepository::remove(int id)
{
    int size=users.size();
    for(int i=0;i<size;i++)
    {
        if(users[i]->getId()==id)
        {
            users.erase(users.begin()+(i));
            return true;
        }
    }
    return false;
}



User* AccountRepository::search(int id) const
{
    for(int i=0;i<users.size();i++)
    {
        if(users[i]->getId()==id)
        {
            return users[i].get();
        }
    }
    return nullptr;
}

User* AccountRepository::searchByUserName(const std::string& name)const
{
    for(int i=0;i<users.size();i++)
    {
        if(users[i]->getUserName()==name)
        {
            return users[i].get();
        }
    }
    return nullptr;
}