#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <stdexcept>
#include "stack.hpp"

#define DICTIONARY_ALLOCATED_BLOCK 0x10


template<typename KeyType, typename ValueType>
struct Node
{
    KeyType key;
    ValueType value;

    Node() = default;
};



// this is a dictionary type.
// it is an associative container that contains key-value pairs.
// the AllowsUnique flag is a compile time flag that will set
// weather the dictionary forces unique items based on the KeyType.
// If false, you are allowed to have multiple of the same key in
//  the dictionary and the first key found will return for searches.
// if true, you are NOT allowed to store more than one copy of a 
//  key in a dictionary.  In this case, if a repeat key is introduced,
//  the ValueType will be overridden
template<typename KeyType, typename ValueType>
class Dictionary
{
private:
    Node<KeyType, ValueType> *_dataPtr = nullptr;
    bool _uniqueForced = false;
    unsigned int _count = 0;
    unsigned int _allocated = DICTIONARY_ALLOCATED_BLOCK;

    void reallocate();
    int find(const KeyType & key) const;

public:
    Dictionary();
    ~Dictionary();


    void Insert(const KeyType & key, const ValueType & value);
    ValueType Remove(const KeyType & key);

    // creates a stack that contains all keys in the dictionary.
    // returns this as a copy.
    Stack<KeyType> Keys() const;
    bool IsEmpty() const;
    bool Contains(const KeyType & key) const;

    ValueType At(const KeyType & key) const;
};


template<typename KeyType, typename ValueType>
Dictionary<KeyType, ValueType>::Dictionary()
{
    _dataPtr = new Node<KeyType, ValueType>[_allocated];
}

template<typename KeyType, typename ValueType>
Dictionary<KeyType, ValueType>::~Dictionary()
{
    delete [] _dataPtr;
}

template<typename KeyType, typename ValueType>
void Dictionary<KeyType, ValueType>::Insert(const KeyType & key, const ValueType & value)
{
    if(_uniqueForced)
    {
        if(Contains(key))
        {
            return;
        }
    }
    if(_count == _allocated)
    {
        reallocate();
    }
    _dataPtr[_count].key = key;
    _dataPtr[_count].value = value;
    _count ++;
}

template<typename KeyType, typename ValueType>
ValueType Dictionary<KeyType, ValueType>::Remove(const KeyType & key)
{
    int loc = find(key);
    if(loc < 0)
    {
        throw new std::range_error("out of bounds error");
    }

    ValueType value = _dataPtr[loc].value;
    for(int i = loc; i < _count; i ++)
    {
        _dataPtr[i].key = _dataPtr[i+1].key;
        _dataPtr[i].value = _dataPtr[i+1].value;
    }
    _count --;

    return value;
}

template<typename KeyType, typename ValueType>
Stack<KeyType> Dictionary<KeyType, ValueType>::Keys() const
{
    Stack<KeyType> returnedStack;

    for(int i = 0; i < _count; i ++)
    {
        returnedStack.AddItem(_dataPtr[i].key);
    }
    return returnedStack;
}

template<typename KeyType, typename ValueType>
bool Dictionary<KeyType, ValueType>::IsEmpty() const
{   
    return _count == 0;
}

template<typename KeyType, typename ValueType>
bool Dictionary<KeyType, ValueType>::Contains(const KeyType & key) const
{
    return find(key) > -1;
}

template<typename KeyType, typename ValueType>
ValueType Dictionary<KeyType, ValueType>::At(const KeyType & key) const
{
    int loc = find(key);
    if(loc < 0)
    {
        return ValueType();
    }
    return _dataPtr[loc].value;
}

template<typename KeyType, typename ValueType>
void Dictionary<KeyType, ValueType>::reallocate()
{
    _allocated += DICTIONARY_ALLOCATED_BLOCK;
    Node<KeyType, ValueType> * tmpList = new Node<KeyType, ValueType>[_allocated];
    
    for(int i = 0; i < _count; i++)
    {
        tmpList[i].key = _dataPtr[i].key;
        tmpList[i].value = _dataPtr[i].value;
    }
    delete _dataPtr;
    _dataPtr = tmpList;
}

template<typename KeyType, typename ValueType>
int Dictionary<KeyType, ValueType>::find(const KeyType & key) const
{
    for(int i = 0; i < _count; i++)
    {
        if(_dataPtr[i].key ==  key)
        {
            return i;
        }
    }
    return -1;
}


#endif