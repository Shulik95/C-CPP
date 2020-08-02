#include <iostream>
class candybag
{
public:
    candybag(size_t num): _num(num), _candy(new std::string[num]) {};

    candybag(candybag &other): _num(other._num), _candy(new std::string[_num])
    {
        for (int i = 0; i < (int)_num; ++i)
        {
            _candy[i] = other._candy[i];
        }
    }

    void fill(size_t index, std::string treat)
    {
        _candy[index] = treat;
    };

    std::string eat(size_t index)
    {
        std::string temp = _candy[index];
        _candy[index]= "";
        return temp;
    };

    candybag& operator=(candybag& other)
    {
        if(this == &other)
        {
            return *this;
        }
        delete[] _candy;
        _num = other._num;
        _candy = new std::string[_num];
        for(size_t i = 0; i< _num; ++i)
        {
            _candy[i] = other._candy[i];
        }
        return *this;
    }

    ~candybag()
    {
        delete[] _candy;
    }

private:
    size_t _num;
    std::string * _candy;
};

class hangers
{
private:
    int _n;
    std::string* _hooks;
    friend std::ostream& operator<<(std::ostream& out, const hangers& h);

public:

    hangers(int n)
    {
        _hooks = new std::string[n];
        _n = n;
    }

    ~hangers()
    {
        delete _hooks;
    }

    hangers(const hangers& other) : _n(other._n), _hooks(new std::string[other._n])
    {
        for (int i = 0; i< _n; ++i)
        {
            _hooks[i] = other._hooks[i];
        }
    }

    hangers& operator=(const hangers& other)
    {
        if(this != &other)
        {
            delete[] _hooks;
            _n = other._n;
            _hooks = new std::string[_n];
            for(int i = 0; i < _n; ++i)
            {
                _hooks[i] = other._hooks[i];
            }
        }
        return *this;
    }

    std::string& operator[](int index)
    {
        return _hooks[index%_n];
    }

    std::string operator[](int index) const
    {
        return _hooks[index % _n];
    }

    operator bool() const
    {
        for(int i =0;i<_n;i++)
        {
            if(_hooks[i] == "")
            {
                return false;
            }
        }
        return true;
    }

};

std::ostream &operator<<(std::ostream &out, const hangers &h) {
    for(int i = 0; i< h._n; i++)
    {
        out << i << ": " <<h[i]<<std::endl;
    }
    return out;
}

int main()
{
    candybag base(2);
    base.fill(0, "Chocolate");
    base.fill(1, "Cream");
    candybag first(5);
    first = base;
    first.eat(0);
    std::cout << base.eat(0);
}
