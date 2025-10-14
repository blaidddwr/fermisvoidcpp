#ifndef LATCH_H
#define LATCH_H

template <class T>
class Latch
{
public:
    Latch(const T& value = T()) { _value = value; }
    void operator=(const T& value) { set(value); }
    bool updated() const { return _updated; }
    const T& get()
    {
        _updated = false;
        return _value;
    }
    const T& peek() const { return _value; }
    void set(const T& value)
    {
        if (_value != value)
        {
            _value = value;
            _updated = true;
        }
    }
    T& set()
    {
        _updated = true;
        return _value;
    }
private:
    T _value;
    bool _updated {true};
};

#endif
