#ifndef ABSTRACTREPOSITORY_H
#define ABSTRACTREPOSITORY_H
#include <memory>
#include<iostream>
template<class T>
class AbstractRepository
{
public:
    virtual ~AbstractRepository()=default;
    virtual bool save(std::unique_ptr<T> item)=0;
    virtual bool remove(int id)=0;
    virtual T* search(int id) const = 0;
};

#endif // ABSTRACTREPOSITORY_H
