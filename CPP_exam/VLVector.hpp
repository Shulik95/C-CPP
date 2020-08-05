//
// Created by user on 04-Aug-20.
//

#ifndef CPP_EXAM_VLVECTOR_HPP
#define CPP_EXAM_VLVECTOR_HPP
// ------------------------------ includes ------------------------------
#include <fstream>
#include <cmath>
#include <cstdlib>

// -------------------------- const definitions -------------------------
/**
 * general copy method between both arrays.
 */
#define COPY_DATA(src, dest)\
for (int i = 0; i < this->_currSize; ++i)\
    {\
        (this->dest)[i] = (this->src)[i];\
    }

#define DEFAULT_SIZE 16
#define EMPTY 0
#define INCREASE_FACTOR 3

const std::string IDX_ERR = "given index is illegal";
// ------------------------------- methods ------------------------------

template <class T, int statSize = DEFAULT_SIZE>
class VLVector
{

private:
    T _staticArr[statSize];
    T* _arrPtr = this->_staticArr;
    size_t _currSize, _currCap;
    T* _dynamicArr = nullptr;


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
        COPY_DATA(_staticArr, _dynamicArr)
    }

    /**
     * copies the elements from the dynamic array into the static array.
     */
    void _copyToStatic()
    {
        COPY_DATA(_dynamicArr, _staticArr)
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

    /**
     * copies the val
     */
    void _decrementCapacity()
    {
        this->_currCap = statSize;
    }

    class Iterator
    {
        T* _currElem;

    public:

        /**
         * @return - the current elements the iterator is holding.
         */
        T& operator*() const
        {
            return *(this->_currElem);
        }

        /**
         * @return - the iterator, post-fix advanced.
         */
        Iterator &operator++()
        {
            _currElem++;
            return *this;
        }

        Iterator &operator++(int)
        {
            Iterator tmp = *this; //save curr iterator.
            _currElem++;
            return tmp;
        }

        /**
         * @param other - iterator to compare against.
         * @return - true if both iterators point at the same item, false otherwise.
         */
        bool operator==(const Iterator& other) const
        {
            return this->_currElem == other._currElem;
        }



    };

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
    explicit VLVector(InputIterator& first, InputIterator& last)

    {

    }

    /**
     * a copy constructor for VLVector, creates a deep copy of the given vector.
     * @param vec - the vecotor to copy.
     */
    explicit VLVector(const VLVector<T>& vec) : VLVector()
    {
        _currSize = vec._currSize;
        _currCap = this->_currCap;
        for (int i = 0; i < vec.size(); ++i)
        {
            _arrPtr[i] = vec[i];
        }
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
        this->_arrPtr[this->_currSize] = val;
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
        this->_currSize--;
        if(this->_currSize <= statSize) //free allocated array and go back to static array.
        {
            this->_copyToStatic(); //copy data to static.
            delete[] this->_dynamicArr; //free allocated memory.
            this->_arrPtr = _staticArr;
        }
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
     * Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
     */
    void clear()
    {
        this->_currSize = EMPTY;
        this->_currCap = statSize;
        if(_dynamicArr != nullptr)
        {
            delete[] (this->_dynamicArr);
        }
    }

    /**
     * @return - a direct pointer to the memory array used internally by the vector to store its owned elements.
     */
    T* data()
    {
        return this->_arrPtr;
    }

    /**
     * @param idx - index in the array to check
     * @return - the value at the given index.
     */
    T& operator[](const int idx)
    {
        return this->_arrPtr[idx];
    }

    /**
     * @param idx - idx to get.
     * @return - the value at the given index in the vector.
     */
    const T& operator[](const int idx) const
    {
        return this->_arrPtr[idx];
    }

    /**
     * checks if two given VLVectors, vectors are equal only if each "cell" holds the same value.
     * @param rhs - VLVector to compare with.
     * @return - true if equal, false otherwise.
     */
    bool operator==(const VLVector<T>& rhs) const
    {
        if(this->_currSize != rhs.size()) //sizes are not the same, no need to check further.
        {
            return false;
        }
        for (int i = 0; i < rhs.size(); ++i)
        {
            if((this->_arrPtr)[i] != rhs[i])
            {
                return false;
            }
        }
        return true;
    }

    /**
     * uses the == operator and answers the opposite.
     * @param rhs - VLVector to compare with.
     * @return - true if arent equal, false otherwise.
     */
    bool operator!=(const VLVector<T>& rhs) const
    {
        return !(*this == rhs);
    }
};

#endif //CPP_EXAM_VLVECTOR_HPP
