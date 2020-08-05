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

const std::string IDX_ERR = "given index is illegal";



template <class T, int statSize = DEFAULT_SIZE>
class VLVector
{

private:
    T _staticArr[statSize];
    T* _arrPtr = this->_staticArr;
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
            this->_dynamicArr = new(std::nothrow) T [ this->_currCap];
            this->_copyToDynamic();
            std::fill(std::begin(this->_staticArr), std::end(this->_staticArr), 0);//zero static array.
            this->_arrPtr = this->_dynamicArr; // change ptr to point at dynamic memory
        }
        else if(this->_currSize == this->_currCap)
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

    //TODO: insert and implement the 2nd constructor.

    /**
     *
     * @tparam InputIterator
     * @param first
     * @param last
     */
    template<class InputIterator>
    VLVector(InputIterator& first, InputIterator& last)

    {

    }


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
     * @throw - index out of range.
     */
    T at(const int idx) const
    {
        if(idx > this->_currSize || idx < 0)
        {
            throw std::out_of_range(IDX_ERR);
        }
        return this->_arrPtr[idx];
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
        }
        this->_arrPtr;
        (this->_currSize)++;
    }

    /**
     * inserts the given value on the left of the given position.
     * @param pos - an iterator pointing to a position in the vector.
     * @param val - refrence of value to insert.
     * @return - an iterator to pointing to the new added value.
     */
    iterator insert(iterator pos ,const T& val)
    {

    }

    /**
     *
     * @param pos
     * @param beg
     * @param end
     * @return
     */
    template <class InputIterator>
    iterator insert(iterator pos, const InputIterator& beg, const InputIterator& end)
    {

    }

    /**
     * removes the last element of the vector.
     */
    void pop_back()
    {

    }

    /**
     *
     * @param pos
     * @return
     */
    iterator erase(iterator pos)
    {

    }

    /**
     *
     * @param first
     * @param last
     * @return
     */
    iterator erase(iterator first, iterator last)
    {

    }

    /**
     *
     */
    void clear()
    {

    }

    /**
     * @return - a direct pointer to the memory array used internally by the vector to store its owned elements.
     */
    T* data()
    {
        return this->_arrPtr;
    }






};

#endif //CPP_EXAM_VLVECTOR_HPP
