//
// Created by user on 04-Aug-20.
//

#ifndef CPP_EXAM_VLVECTOR_HPP
#define CPP_EXAM_VLVECTOR_HPP
// ------------------------------ includes ------------------------------
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

// -------------------------- const definitions -------------------------
/**
 * general copy method between both arrays.
 */
#define COPY_DATA(src, dest)\
for (int i = 0; i < this->_currSize; ++i)\
    {\
        (this->dest)[i] = (this->src)[i];\
    }

#define DEFAULT_CAP 16
#define EMPTY 0
#define INCREASE_FACTOR 3

const static std::string IDX_ERR = "given index is illegal";
// ------------------------------- methods ------------------------------

template <class T, int statSize = DEFAULT_CAP>
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
        else
        {
            /*need to increase dynamic memory*/
            //_dynamicArr = (T*) realloc(_dynamicArr, this->_currCap * sizeof(T*));
            T* tmp = new(std::nothrow) T [_currCap];
            for (int i = 0; i < _currSize ; ++i)
            {
                tmp[i] = _dynamicArr[i];
            }
            delete[] _dynamicArr;
            _dynamicArr = tmp;
        }
    }

    /**
     * contains all actions needed when transferring the data from dynamic memory onto the stack.
     */
    void _toStack()
    {
        COPY_DATA(_dynamicArr, _staticArr);
        delete[] _dynamicArr;
        _dynamicArr = nullptr;
        _arrPtr = _staticArr;
        _currCap = statSize;
    }

    class Iterator
    {
        T* _currElem;

    public:

        /*Iterator traits*/
        typedef T value_type;
        typedef T &reference;
        typedef  T *pointer;
        typedef int difference_type;
        typedef std::random_access_iterator_tag iterator_category;

        /**
         * constructors for the Iterator class.
         */
        Iterator(T* val) : _currElem(val){}

        /**
         * @return - the current elements the iterator is holding.
         */
        reference operator*() const
        {
            return *_currElem;
        }

        /**
         * @return - reference to the value at _currElem+n.
         */
        reference operator[](const difference_type& n)
        {
            return *this->_currElem + n;
        }

        /**
         * @return - the incremented iterator, post-fix advanced.
         */
        Iterator &operator++()
        {
            _currElem++;
            return *this;
        }

        /**
         * @return the incremented iterator/
         */
        Iterator &operator++(int)
        {
            Iterator tmp = *this; //save curr iterator.
            _currElem++;
            return tmp;
        }

        /**
         *
         * @return
         */
        Iterator &operator--()
        {
            _currElem--;
            return *this;
        }

        /**
         *
         * @return
         */
        Iterator &operator__(int)
        {
            Iterator tmp = *this;
            _currElem--;
            return tmp;
        }

        /**
         * @param k - reference to T type.
         * @return - an iterator to the sum of the given input and curr.
         */
        Iterator operator+(const difference_type& k) const
        {
            return Iterator(_currElem + k);
        }

        /**
         * @param other - iterator.
         * @return - sum of pointers.
         */
        difference_type operator+(const Iterator other) const
        {
            return _currElem + other._currElem;
        }

        /**
         * @param k - reference to another T type.
         * @return - an iterator to the difference of the given item and curr.
         */
        Iterator operator-(const difference_type& k) const
        {
            return Iterator(this->_currElem - k);
        }

        /**
         * @param other - another iterator.
         * @return - distance between pointers.
         */
        difference_type operator-(const Iterator other) const
        {
            return _currElem - other._currElem;
        }

        /**
         *
         * @param T2
         * @return
         */
        Iterator &operator+=(const difference_type& k)
        {
            this->_currElem += k;
            return *this;
        }

        /**
         *
         * @param n
         * @return
         */
        Iterator &operator-=(const difference_type& n)
        {
            this->_currElem -= n;
            return *this;
        }


        /**
         * @param other - iterator to compare against.
         * @return - true if both iterators point at the same item, false otherwise.
         */
        bool operator==(const Iterator& other) const
        {
            return this->_currElem == other._currElem;
        }

        /**
         * @param other - iterator to compare against.
         * @return true if the iterators aren't pointing at the same value;
         */
        bool operator!=(const Iterator& other) const
        {
            return this->_currElem != other._currElem;
        }

        /**
         * @param other - iterator to compare against.
         * @return - true if the first pointer is lesser then the other.
         */
        bool operator<(const Iterator& other) const
        {
            return this->_currElem < other._currElem;
        }

        /**
         * @param other - iterator to compare against.
         * @return - true if the first pointer is greater then the other.
         */
        bool operator>(const Iterator& other) const
        {
            return this->_currElem > other._currElem;
        }

        /**
         *
         * @param other - iterator to compare against.
         * @return - true if the first pointer is lesser or equal then the other.
         */
        bool operator<=(const Iterator& other) const
        {
            return this->_currElem <= other._currElem;
        }

        /**
         *
         * @param other - iterator to compare against.
         * @return - true if the first pointer is greater or equal then the other.
         */
        bool operator>=(const Iterator& other) const
        {
            return this->_currElem >= other._currElem;
        }
    };

    class ConstIterator
    {
        T* _curr;

    public:
        typedef T value_type;
        typedef const T& reference;
        typedef const T* pointer;
        typedef int difference_type;
        typedef std::random_access_iterator_tag iterator_category;

        /**
         * constructors for the Iterator class.
         */
        ConstIterator(T* val) : _curr(val){}

        /**
         *
         * @return
         */
        value_type operator*() const
        {
            return *_curr;
        }

        /**
         *
         * @param n
         * @return
         */
        value_type operator[](const difference_type n) const
        {
            return *(this->_curr) + n;
        }

        /**
         *
         * @return
         */
        ConstIterator &operator++()
        {
            _curr++;
            return *this;
        }

        /**
         *
         * @return
         */
        ConstIterator &operator++(int)
        {
            ConstIterator temp = *this;
            _curr++;
            return temp;
        }

        /**
         *
         * @return
         */
        ConstIterator &operator--()
        {
            _curr--;
            return *this;
        }

        /**
         *
         * @return
         */
        ConstIterator &operator--(int)
        {
            ConstIterator temp = *this;
            _curr--;
            return temp;
        }

        /**
         *
         * @param n
         * @return
         */
        ConstIterator operator+(const difference_type& n) const
        {
            return ConstIterator(_curr + n);
        }


        /**
         *
         * @param n
         * @return
         */
        ConstIterator operator-(const difference_type& n) const
        {
            return ConstIterator(_curr - n);
        }

        /**
         *
         * @param n
         * @return
         */
        ConstIterator operator+=(const difference_type& n) const
        {
            _curr += n;
            return *this;
        }

        /**
         *
         * @param n
         * @return
         */
        ConstIterator operator-=(const difference_type& n) const
        {
            _curr -= n;
            return *this;
        }

        /**
         *
         * @param other
         * @return
         */
        bool operator==(const ConstIterator& other) const
        {
            return this->_curr == other._curr;
        }

        /**
         *
         * @param other
         * @return
         */
        bool operator!=(const ConstIterator& other) const
        {
            return this->_curr != other._curr_curr;
        }

        /**
         *
         * @param other
         * @return
         */
        bool operator<(const ConstIterator& other) const
        {
            return _curr < other._curr;
        }

        /**
         *
         * @param other
         * @return
         */
        bool operator>(const ConstIterator& other) const
        {
            return _curr > other._curr;
        }

        /**
         *
         * @param other - iterator to compare against.
         * @return - true if the first pointer is lesser or equal then the other.
         */
        bool operator<=(const ConstIterator& other) const
        {
            return _curr <= _curr;
        }

        /**
         *
         * @param other - iterator to compare against.
         * @return - true if the first pointer is greater or equal then the other.
         */
        bool operator>=(const ConstIterator& other) const
        {
            return _curr >= _curr;
        }

    };

public:

    /**
     * iterator typedef.
     */
    typedef Iterator iterator;
    typedef ConstIterator const_iterator;

    /**
     * creates a default empty VLVector with the given generic size.
     */
    explicit VLVector() : _currSize(EMPTY), _currCap(statSize) {}

    /**
     *
     * @tparam InputIterator
     * @param first
     * @param last
     */
    template<class InputIterator>
    VLVector(InputIterator first, InputIterator last) : _currSize(EMPTY), _currCap(statSize)
    {
        for (auto it = first; it != last; it++)
        {
            this->push_back(*it);
        }
    }

    /**
     * a copy constructor for VLVector, creates a deep copy of the given vector.
     * @param vec - the vector to copy.
     */
    VLVector(const VLVector<T>& vec) : _currSize(EMPTY), _currCap(statSize)
    {
        *this = vec;
    }

    /**
     * destructor for each object.
     */
    ~VLVector()
    {
        delete[] this->_dynamicArr;
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
            delete[] this->_dynamicArr;
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
        if(_currSize + 1 > _currCap) // need to increase the array.
        {
            int idx = pos - this->begin();
            _incrementCapacity();
            pos = Iterator(&(_arrPtr[idx]));
        }
        for (auto it = this->end(); it != (pos - 1); --it) //shift all elements to the right
        {
            *(it + 1) = *it;
        }
        *pos = val;
        _currSize++;
        return pos;
    }

    /**
     *
     * @param first -
     * @param last -
     * @param pos -
     * @return -
     */
    template <class InputIterator>
    iterator insert(iterator pos, const InputIterator& first, const InputIterator& last)
    {
        int sizeChange = last - first;
        auto tmpEnd = this->end();
        //_currSize += sizeChange;
        int idx = pos - this->begin();
        int endIdx = this->end() - this->begin();
        while(_currSize + sizeChange > _currCap) //increase capacity
        {
            _incrementCapacity();
            pos = Iterator(&(this->_arrPtr[idx]));
            tmpEnd = Iterator(&(_arrPtr[endIdx]));
        }
        _currSize += sizeChange;
        std::copy_backward(pos, tmpEnd, this->end());
        std::copy(first, last, pos);
        return pos;
    }

    /**
     * removes the last element of the vector.
     */
    void pop_back()
    {
        this->_currSize--;
        if(this->_currSize == statSize) //free allocated array and go back to static array.
        {
            this->_copyToStatic(); //copy data to static.
            delete[] this->_dynamicArr; //free allocated memory.
            this->_dynamicArr = nullptr;
            this->_arrPtr = _staticArr;
            this->_currCap = statSize;
        }
    }

    /**
     * @param pos - iterator for the array
     * @return - an iterator to the element on the right of the removed element.
     */
    iterator erase(iterator pos)
    {
        for(auto item = pos; item != this->end(); item++)
        {
            *item = *(item +1);
        }
        if(_currSize - 1 == statSize) //change back to static memory from dynamic
        {
            int idx = pos - this->begin();
            this->_toStack();
            pos = Iterator(&(_arrPtr[idx]));
        }
        _currSize--;
        return pos;
    }

    /**
     *
     * @param first - iterator pointing to the first element to delete
     * @param last - first element which is not deleted
     * @return - iterator to the first element which is not deleted.
     */
    iterator erase(iterator first, iterator last)
    {
        int sizeChange = last - first;
        int idx = first - this->begin();
        for(auto it = last; it != this->end(); it++)
        {
            *(it - sizeChange) = *it;
        }
        _currSize -= sizeChange;
        if(_currSize <= statSize && _dynamicArr != nullptr) //move from dynamic to static
        {
            this->_toStack();
            first = Iterator(&(_arrPtr[idx]));
        }
        return first;
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
            this->_dynamicArr = nullptr;
            _arrPtr = _staticArr;
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
     *
     * @return
     */
    iterator begin()
    {
        return iterator((this->_arrPtr));
    }

    /**
     *
     * @return
     */
    const_iterator begin() const
    {
        return const_iterator(this->_arrPtr);
    }

    /**
     *
     * @return
     */
    const_iterator cbegin() const
    {
        return const_iterator(this->_arrPtr);
    }

    /**
     *
     */
    iterator end()
    {
        return _arrPtr + _currSize;
    }

    /**
     *
     * @return
     */
    const_iterator end() const
    {
        return const_iterator(this->_arrPtr[_currSize]);
    }

    /**
     *
     * @return
     */
    const_iterator cend() const
    {
        return const_iterator(this->_arrPtr[_currSize]);
    }


    //----------------Operators----------------
    /**
     *
     * @param rhs
     * @return
     */
    VLVector& operator=(const VLVector& rhs)
    {
        if(this == &rhs)
        {
            return *this;
        }
        this->_currSize = rhs.size();
        this->_currCap = rhs.capacity();
        delete[] this->_dynamicArr;
        this->_dynamicArr = nullptr;
        if (this->capacity() > statSize) //data is in the dynamically allocated array
        {
            this->_dynamicArr = new T[this->capacity()];
            for (int i = 0; i < rhs.size(); ++i)
            {
                this->_dynamicArr[i] = rhs._dynamicArr[i];
            }
            this->_arrPtr = this->_dynamicArr;
        }
        else //data is on the stack.
        {
            for (int i = 0; i < this->size(); ++i)
            {
                this->_staticArr[i] = rhs._staticArr[i];
            }
            this->_arrPtr = this->_staticArr;
        }
        return *this;
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