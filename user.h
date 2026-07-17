#ifndef USER_H
#define USER_H

#include<string>

class User
{
public:
    User();
    User(int id, const std::string& username, const std::string& password,
         const std::string& fullName, const std::string& biography,
         const std::string& role, const std::string& profilePhotoPath);

    virtual ~User() = default;

    std::string getPassword(){return password;}
    int getId() const { return id; }
    std::string getUserName() const { return username; }

    void setId(int id) { this->id = id; }
    void setUserName(const std::string& username) { this->username = username; }
    void setPassword(const std::string& password) { this->password = password; }
    void setFullName(const std::string& fullName) { this->fullName = fullName; }
    void setBiography(const std::string& biography) { this->biography = biography; }
    void setRole(const std::string& role) { this->role = role; }
    void setProfilePhotoPath(const std::string& profilePhotoPath) { this->profilePhotoPath = profilePhotoPath; }

protected:
    int id;
    std::string username;
    std::string password;
    std::string fullName;
    std::string biography;
    std::string role;
    std::string profilePhotoPath;
};

#endif
