//
// Created by user on 04-Aug-20.
//

#ifndef CPP_EXAM_VLVECTOR_HPP
#define CPP_EXAM_VLVECTOR_HPP

#include <fstream>
#include <cmath>
#include <cstdlib>

#define DEFAULT_SIZE 16
#define EMPTY 0
#define INCREASE_FACTOR 3



template <class T, int statSize = DEFAULT_SIZE>
class VLVector
{

private:
    T _staticArr[statSize];
    size_t _currSize, _currCap;
    T* _dynamicArr;


    /**
     * calculates the new size of the array according to given formula.
     */
    int _getNewSize() const
    {
        return floorf(INCREASE_FACTOR * (this->_currSize + 1) * 0.5);
    }

    /**
     * copies the elements from the static array into the dynamic array.
     */
    void _copyToDynamic()
    {
        for(int i = 0; i < this->_currSize; i++)
        {
            (this->_dynamicArr)[i] = (this->_staticArr)[i];
        }
    }

    /**
     * increments size of the given array, all items are copied into the larger array. only called if needed.
     * this method allocates memory on the heap but doesnt free it!
     */
    void _incrementCapacity()
    {
        this->_currCap = this->_getNewSize(); //update new capacity
        if(this->_currSize == statSize)
        {
            /*the static memory is full, move to dynamic memory*/
            _dynamicArr = new(std::nothrow) T * [ this->_currCap];
            this->_copyToDynamic();
            std::fill(std::begin(this->_staticArr), std::end(this->_staticArr), 0);//zero static array.
        }
        else if(this->_currsize == this->_currCap)
        {
            /*need to increase dynamic memory*/
            _dynamicArr = (T*) realloc(_dynamicArr, this->_currCap * sizeof(T*));
        }
    }

public:

    /**
     * iterator typedef.
     */
    typedef T* iterator;

    /**
     * creates a default empty VLVector with the given generic size.
     */
    explicit VLVector() : _currSize(EMPTY), _currCap(statSize) {}


    /**
     * @return - the current number of elements in the vector.
     */
    size_t size() const
    {
        return this->_currSize;
    }

    /**
     * @return - the current capacity of the vector.
     */
    size_t capacity() const
    {
        return this->_currCap;
    }

    /**
     * @return - true if the size is 0 false else.
     */
    bool empty() const
    {
        return this->_currSize == EMPTY;

    }

    /**
     * @param idx - index to get from.
     * @return - the value at the given index.
     */
    T at(const int idx) const
    {
        if(this->_currCap < statSize) //using static memory.
        {
            return this->_staticArr[idx];
        }
        else //currently using dynamically allocated memory
        {
            return this->_dynamicArr[idx];
        }
    }

    /**
     * takes the given input and inserts it at the end of the vector.
     * @param val -  reference value to insert.
     */
    void push_back(const T& val)
    {
        if(this->_currSize + 1 > this->_currCap) //incrementation needed, definitely allocated memory
        {
            this->_incrementCapacity();
            this->_dynamicArr[this->_currSize] = val;
        }
        else
        {
            if(this->_currSize > statSize)
            {
                this->_dynamicArr[this->_currSize] = val;
            }
            else
            {
                this->_staticArr[this->_currSize] = val;
            }
        }
        (this->_currSize)++;
    }




};

#endif //CPP_EXAM_VLVECTOR_HPP
