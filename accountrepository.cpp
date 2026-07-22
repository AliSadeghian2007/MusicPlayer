#include "accountrepository.h"
#include "artist.h"
#include "listener.h"

#include <fstream>



static std::vector<std::string> splitLine(const std::string& line, char delimiter)
{
    std::vector<std::string> fields;
    std::string field;

    for (int i = 0; i < static_cast<int>(line.size()); i++)
    {
        if (line[i] == delimiter)
        {
            fields.push_back(field);
            field.clear();
        }
        else
        {
            field += line[i];
        }
    }

    fields.push_back(field);
    return fields;
}


AccountRepository::AccountRepository() : nextId(1) {}

int AccountRepository::generateId()
{
    return nextId++;
}



bool AccountRepository::save(std::unique_ptr<User> a)
{
    if (!a) return false;

    if (a->getId() == 0)
    {
        a->setId(generateId());
    }

    for (int i = 0; i < users.size(); i++)
    {
        if (a->getId() == users[i]->getId() ||
            a->getUserName() == users[i]->getUserName() ||
            a->getPassword() == users[i]->getPassword())
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


bool AccountRepository::saveToFile(const std::string& path) const
{
    std::ofstream fout(path);

    if (!fout.is_open())
    {
        return false;
    }

    for (int i = 0; i < static_cast<int>(users.size()); i++)
    {
        User* user = users[i].get();
        std::string type = "User";

        if (dynamic_cast<Artist*>(user) != nullptr)
        {
            type = "Artist";
        }
        else if (dynamic_cast<Listener*>(user) != nullptr)
        {
            type = "Listener";
        }

        fout << type << '|'
             << user->getId() << '|'
             << user->getUserName() << '|'
             << user->getPassword() << '|'
             << user->getFullName() << '|'
             << user->getBiography() << '|'
             << user->getRole() << '|'
             << user->getProfilePhotoPath()
             << '\n';

        if (!fout)
        {
            return false;
        }
    }

    return true;
}





bool AccountRepository::loadFromFile(const std::string& path)
{
    std::ifstream fin(path);

    if (!fin.is_open())
    {
        return true;
    }

    std::vector<std::unique_ptr<User>> loadedUsers;
    std::string line;
    int loadedNextId = 1;

    while (std::getline(fin, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::vector<std::string> fields = splitLine(line, '|');

        if (fields.size() != 8)
        {
            return false;
        }

        std::string type = fields[0];
        int id = 0;

        try
        {
            id = std::stoi(fields[1]);
        }
        catch (...)
        {
            return false;
        }

        std::string username = fields[2];
        std::string password = fields[3];
        std::string fullName = fields[4];
        std::string biography = fields[5];
        std::string role = fields[6];
        std::string profilePhotoPath = fields[7];

        std::unique_ptr<User> account;

        if (type == "Artist")
        {
            account = std::make_unique<Artist>(
                id,
                username,
                password,
                fullName,
                biography,
                role,
                profilePhotoPath
                );
        }
        else if (type == "Listener")
        {
            account = std::make_unique<Listener>(
                id,
                username,
                password,
                fullName,
                biography,
                role,
                profilePhotoPath
                );
        }
        else if (type == "User")
        {
            account = std::make_unique<User>(
                id,
                username,
                password,
                fullName,
                biography,
                role,
                profilePhotoPath
                );
        }
        else
        {
            return false;
        }

        for (int i = 0; i < static_cast<int>(loadedUsers.size()); i++)
        {
            if (loadedUsers[i]->getId() == account->getId())
            {
                return false;
            }

            if (loadedUsers[i]->getUserName() == account->getUserName())
            {
                return false;
            }
        }

        if (id >= loadedNextId)
        {
            loadedNextId = id + 1;
        }

        loadedUsers.push_back(std::move(account));
    }

    users = std::move(loadedUsers);
    nextId = loadedNextId;

    return true;
}
