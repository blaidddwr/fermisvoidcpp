#ifndef LATCH_H
#define LATCH_H

template <class T>
class Latch
{
public:
    Latch(const T& value = T())
    {
        _value = value;
    }
    bool updated() const
    {
        return _updated;
    }
    const T& get()
    {
        _updated = false;
        return _value;
    }
    const T& peek() const
    {
        return _value;
    }
    void set(const T& value)
    {
        if (_value != value)
        {
            _value = value;
            _updated = true;
        }
    }
private:
    T _value;
    bool _updated {true};
};

#endif
