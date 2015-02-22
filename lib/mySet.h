#ifndef MYSET_H
#define MYSET_H
#include <deque>
#include <set>
using namespace std;

template <class T>
class mySet : public set<T>{
  public:
    bool contains (const T & item) const;
    mySet<T> setIntersection (mySet<T> & other) const;
    mySet<T> setUnion (mySet<T> & other) const;
};

template <class T>
bool mySet<T>::contains (const T & item) const{
  //cout << "internalStorage size: " << internalStorage.size() << endl;
  typename set<T>::iterator it;
  for(it = this->begin(); it != this->end(); ++it){
  //for(int i = 0; i < internalStorage.size(); i++){
    if (*it == item){
      return true;
    }
  }
  return false;
}

template <class T>
mySet<T> mySet<T>::setIntersection (mySet<T> & other) const{
        /* Returns the intersection of the current set with other.
         That is, returns the set of all items that are both in this
         and in other. */
  mySet<T>* intersection_set = new mySet<T>;
  //iterator 1 is for this, iterator 2 is for other
  typename set<T>::iterator it1, it2;
  for (it1 = this->begin(); it1 != this->end(); ++it1){
    for (it2 = other.begin(); it2 != other.end(); ++it2){
      if (*it1 == *it2 && //make sure this implementation works!
          !intersection_set->contains(*it1))
          intersection_set->insert(*it1);
    }
  }
  return *intersection_set;
}

template <class T>
mySet<T> mySet<T>::setUnion (mySet<T> & other) const{
  /* Returns the union of the current set with other.
     That is, returns the set of all items that are in this set
     or in other (or both).
     The resulting set should not contain duplicates. */
  mySet<T>* union_set = new mySet<T>;
  typename set<T>::iterator it1, it2;
  for (it1 = this->begin(); it1 != this->end(); ++it1){
  //for (int i =0; i < this->size(); i++){
      if (!union_set->contains(*it1))
          union_set->insert(*it1);
  }
  for (it2 = other.begin(); it2 != other.end(); ++it2){
  //for (int j = 0; j < other.size(); j++){
      if (!union_set->contains(*it2))
          union_set->insert(*it2);
    }
  return *union_set;
}

#endif
