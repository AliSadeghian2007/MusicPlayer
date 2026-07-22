#ifndef ACCOUNTREPOSITORY_H
#define ACCOUNTREPOSITORY_H
#include <memory>
#include "abstractrepository.h"
#include<string>
#include "user.h"
#include <vector>
class AccountRepository : public AbstractRepository<User>
{
private:
    int nextId;
protected:
    std::vector<std::unique_ptr<User>> users;
public:
    AccountRepository();
    int generateId();


    bool save(std::unique_ptr<User> item) override;
    bool remove(int id) override;
    User* search (int id) const override;

    std::vector<std::unique_ptr<User>>& getUsers()
    {
        return users;
    }


    User* searchByUserName(const std::string& name)const;



    bool loadFromFile(const std::string& path);
    bool saveToFile(const std::string& path) const;
};

#endif // ACCOUNTREPOSITORY_H
