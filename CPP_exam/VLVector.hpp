//
// Created by user on 04-Aug-20.
//

#ifndef CPP_EXAM_VLVECTOR_HPP
#define CPP_EXAM_VLVECTOR_HPP

#include <w32api/rpcndr.h>

#define DEFAULT_SIZE 16
#define DEFAULT_AMOUNT 0

template <class T, int statSize = DEFAULT_SIZE>
class VLVector
{

private:
    T _staticArr[statSize];
    size_t _currSize, _currCap;
    T* _dynamicArr;

public:

    /**
     * creates a default empty VLVector with the given generic size.
     */
    explicit VLVector() : _currSize(DEFAULT_AMOUNT), _currCap(statSize) {}


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
        return this->_currSize == 0;

    }

    /**
     * @param idx - index to get.
     * @return
     */
    T at(int const idx) const
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


};

#endif //CPP_EXAM_VLVECTOR_HPP
