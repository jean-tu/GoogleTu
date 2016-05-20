#ifndef MYSET_H
#define MYSET_H

#include <set>
#include <string>

// avoid circular reference
//class WebPage;

template<typename T> 
class myset: public std::set<T>
{
public:
  myset<T>();
  myset<T> set_intersection(const myset<T>& other);
  myset<T> set_union(const myset<T>& other);
};

template<class T> 
myset<T>::myset() : std::set<T>() {}

template<class T> 
myset<T> myset<T>::set_intersection(const myset<T>& other) {
  myset<T> result;
    for(typename myset<T>::iterator it = this->begin(); it != this->end(); ++it){
    if(other.find(*it) != other.end()){
      result.insert(*it);
    }
  }
  return result;
}

template<class T> 
myset<T> myset<T>::set_union(const myset<T>& other) {
  myset<T> result = other;
    for(typename myset<T>::iterator it = this->begin(); it != this->end(); ++it){
    if(result.find(*it) == result.end()){
      result.insert(*it);
    }
  }
  return result;
}

#endif
