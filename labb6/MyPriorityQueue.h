// This is the second .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"
//floor function for parent
#include "cmath"
#include "iostream"
#include <assert.h>

using namespace std;
template <typename T, typename C>
class MyPriorityQueue
{
    MyVector<T> vector_array;
    C strictly_larger_operator;
public:
    //Default constructor
    MyPriorityQueue() = default;
    //Destructor
    ~MyPriorityQueue() = default;
    //Pushes a value to the queue
    void push(const T& t);
    //Returns top element
    T top()const;
    //Pops last element
    void pop();
    //Return if queue is empty or not
    bool empty()const;
    //returns size of the queue
    unsigned size() const;

private:
    //Siftdown to remake to the structure of the queue
    void siftDown(int pos);
    //Returns if a positios is a leaf
    bool isLeaf(int position);
    //Returns index of left child of i
    int leftChild(int i) const;
    //Returns index of right child of i
    int rightChild(int i) const;
    //Returns index of left sibling of i
    int leftSibling(int i) const;
    //Returns index of right sibling of i
    int rightSibling(int i) const;
    //Returns index of parent of i
    int parent(int i) const;
    //Swaps the value of two indexes
    void swap(int insertIndex, int swapIndex);
};



template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
    vector_array.push_back(t);
    int key = vector_array.size()-1;

    while(key != 0 && strictly_larger_operator(vector_array[parent(key)], vector_array[key])){
        swap(key, parent(key));
        key = floor((key-1)/2);

    }

}

template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    assert(!vector_array.empty());
    return vector_array[0];
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
    assert(!vector_array.empty());
    if(vector_array.empty()){
        return;
    }else{
        int key = 0;
        swap(key,vector_array.size()-1);
        vector_array.pop_back();
        if(!vector_array.empty()){
            siftDown(0);
        }
    }
}

template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    return vector_array.empty();
}

template <typename T, typename C>
unsigned MyPriorityQueue<T,C>::size()const{
    return vector_array.size();
}

template <typename T, typename C>
int MyPriorityQueue<T,C>::leftChild(int i)const{
    if((2*i+1) >= (vector_array.size()-1)){
        return -1;
    }else{
        return 2*i+1;
    }
}

template <typename T, typename C>
int MyPriorityQueue<T,C>::rightChild(int i)const{
    if((2*i+2) >= (vector_array.size()-1)){
        return -1;
    }else{
        return 2*i+2;
    }
}

template <typename T, typename C>
int MyPriorityQueue<T,C>::leftSibling(int i)const{
    if(i%2 != 0 || i == 0){
        return -1;
    }else{
        return i-1;
    }
}

template <typename T, typename C>
int MyPriorityQueue<T,C>::rightSibling(int i)const{
    if(i%2 == 0 || i == (vector_array.size()-1)){
        return -1;
    }else{
        return i+1;
    }
}

template <typename T, typename C>
int MyPriorityQueue<T,C>::parent(int i)const{
    if(i == 0){
        return -1;
    }else{
        int value = floor((i-1)/2);
        return value;
    }
}
template <typename T, typename C>
bool MyPriorityQueue<T,C>::isLeaf(int position){
    if(position >= vector_array.size()/2 && position < vector_array.size()){

        return true;
    }
    return false;
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::swap(int insertIndex, int swapIndex){
    T temp = vector_array[insertIndex];
    vector_array[insertIndex] = vector_array[swapIndex];
    vector_array[swapIndex] = temp;
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::siftDown(int pos){
   if(pos < 0 || pos >= vector_array.size()){
       return;
   }
   while(!isLeaf(pos)){
   int index = leftChild(pos);
   if(index == -1){return;}
   if(index<(vector_array.size()-1) && strictly_larger_operator(vector_array[index], vector_array[index+1])){
    index++;
   }
   if(!strictly_larger_operator(vector_array[pos], vector_array[index])){
       return;
   }
   swap(pos, index);
   pos = index;
   }
}

















#endif // MY_PRIORITY_QUEUE_H
