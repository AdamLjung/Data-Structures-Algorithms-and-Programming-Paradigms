// This is the first .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"

template <typename T>
class MyVector
{

public:
    //constructor
    MyVector();
    //Destructor
    ~MyVector();
    //Copy constructor
    MyVector(const MyVector& other);
    //Copy assignment operator
    MyVector& operator =(const MyVector& other);
    //Pushes a value to the vector
    void push_back(const T&);
    //Pops a value from the vector
    void pop_back();
    //Operator []
    T& operator[](unsigned i);
    //Operator []
    const T& operator[](unsigned i)const;
    //Returns if vector is empty or not
    bool empty()const;
    //Pointer to the first element in the vector
    T* begin();
    //Pointer to the last element in the vector
    T* end();
    //Clears the vector
    void clear();
    //Returns the size of the vector
    unsigned size()const;

private:
    //Capacity of the vector
    int capacity;
    //Size of the vector
    int vecSize;
    //Elements of the vector
    T* myElems;

};

template<typename T>
MyVector<T>::MyVector(){
    vecSize = 0;
    capacity = 1;
    myElems = new T[capacity];
}

template<typename T>
MyVector<T>::~MyVector(){
    delete[] myElems;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other){
      vecSize = other.vecSize;
      capacity = other.capacity;
      myElems = new T[capacity];
      for(size_t i = 0; i < other.capacity; i++){
          myElems[i] = other.myElems[i];
      }
}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    if(this != &other){
        delete [] myElems;
        vecSize = other.vecSize;
        capacity = other.capacity;
        myElems = new T[capacity];
        for(size_t i = 0; i < capacity; i++){
            myElems[i] = other.myElems[i];
        }
    }
    return *this;
}

template<typename T>
void MyVector<T>::push_back(const T& e){
    if(vecSize != capacity){
        myElems[vecSize] = e;
        vecSize +=1;
    }else{
        T* temp = new T[capacity*2];
        capacity *=2;
        for(int i = 0; i < vecSize; i++){
           temp[i] = myElems[i];  
        }
        delete [] myElems;
        myElems = temp;
        myElems[vecSize] = e;
        vecSize++;
    }

}

template<typename T>
void MyVector<T>::pop_back(){
    if(vecSize > 0){
    myElems[vecSize] = 0;
    vecSize--;
    }
}

template<typename T>
T& MyVector<T>::operator[](unsigned i){
    return myElems[i];
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    return myElems[i];
}

template<typename T>
bool MyVector<T>::empty()const{
    if(vecSize == 0){
        return true;
    }else{
        return false;
    }
}

template<typename T>
void MyVector<T>::clear(){
    vecSize = 0;
    capacity = 1;
    delete [] myElems;
    myElems = new T[capacity];
}

template<typename T>
unsigned MyVector<T>::size()const{
    return vecSize;
}

template<typename T>
T* MyVector<T>::begin(){
   return &myElems[0];
}

template<typename T>
T* MyVector<T>::end(){
    return &myElems[vecSize];
}

#endif // MY_VECTOR_H
