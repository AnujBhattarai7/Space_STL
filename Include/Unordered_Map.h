#pragma once

#include <assert.h>
#include "Iterator.h"
#include <hashtable.h>

namespace SP_STL
{
    template <typename _K, typename _T>
    class Unordered_Map
    {
    public:
        using Iterator = _Iterator_Base<_T>;

    public:
        Unordered_Map() {}
        ~Unordered_Map();

        // Getters
        const int Size() const { return _Size; }
        const int Capacity() const { return _Capacity; }

        const _T &Get(const _K &K)
        {
            _AuthSize();
            return _Map[_Find(K)];
        }

        // Checks if K exists in _Key or not
        bool _KeyExist(const _K &K) { return (_Find(K) != -1) ? true : false; }
        // Flushes both the arrays
        void Flush();
        // Reserves the given _NC in both Arrays
        void Reserve(int _NC);

        // Operators
        _T &operator[](const _K &K);
        _T &operator[](_K &&K);
        const _T &operator[](const _K &K) const;

        // Range based loops
        Iterator begin() { return _Iterator_Base(_Map); }
        Iterator end() { return _Iterator_Base(_Map + _Size); }

    private:
        // The Key array
        _K *_Keys = nullptr;

        // The main array which holds the data
        _T *_Map = nullptr;

        // Stores the Size Used of the Maps
        int _Size = 0;
        // Stores the Capacity of the Maps
        int _Capacity = 0;
        // Caches teh latest _Find result
        int _FindCache = 0;

        // Allocates memory into _Map and _Keys
        void _Alloc(int _NC);

        // Finds and Gets the index of _K if exists in _Keys else -1
        int _Find(const _K &K);

        // Checks if _Size exists
        void _AuthSize();
    };

    template <typename _K, typename _T>
    inline _T &Unordered_Map<_K, _T>::operator[](const _K &K)
    {
        if (_Size + 1 > _Capacity)
            _Alloc((_Size + 1) * 1.5);

        int _CN = _Find(K);
        if (_CN != -1)
            return _Map[_CN];

        _Keys[_Size] = K;
        _Size++;
        return _Map[_Size - 1];
    }

    template <typename _K, typename _T>
    inline _T &Unordered_Map<_K, _T>::operator[](_K &&K)
    {
        if (_Size + 1 > _Capacity)
            _Alloc((_Size + 1) * 1.5);

        int _CN = _Find(K);
        if (_CN != -1)
            return _Map[_CN];

        _Keys[_Size] = std::move(K);
        _Size++;
        return _Map[_Size - 1];
    }

    template <typename _K, typename _T>
    inline const _T &Unordered_Map<_K, _T>::operator[](const _K &K) const
    {
        return _Map[_Find(K)];
    }

    template <typename _K, typename _T>
    inline void Unordered_Map<_K, _T>::_Alloc(int _NC)
    {
        // for No memory allocated
        if (_Map == nullptr || _Keys == nullptr)
        {
            _Map = (_T *)::operator new(_NC * sizeof(_T));
            _Keys = (_K *)::operator new(_NC * sizeof(_K));
            _Capacity = _NC;

            return;
        }

        int _OC = _Capacity;
        _Capacity = _NC;

        _T *_NewMap = (_T *)::operator new(_Capacity * sizeof(_T));
        _K *_NewKey = (_K *)::operator new(_Capacity * sizeof(_K));

        // Copies the data into _A
        for (int i = 0; i < _Size; i++)
        {
            _NewKey[i] = std::move(_Keys[i]);
            _NewMap[i] = std::move(_Map[i]);
        }

        for (int i = 0; i < _Size; i++)
        {
            _Keys[i].~_K();
            _Map[i].~_T();
        }

        ::operator delete(_Map, _OC * sizeof(_T));
        ::operator delete(_Keys, _OC * sizeof(_K));

        _Keys = _NewKey;
        _Map = _NewMap;

        return;
    }

    template <typename _K, typename _T>
    inline int Unordered_Map<_K, _T>::_Find(const _K &K)
    {
        for (int i = 0; i < _Size; i++)
            if (std::hash<_K>{}(_Keys[i]) == std::hash<_K>{}(K))
            {
                _FindCache = i;
                return _FindCache;
            }

        _FindCache = -1;
        return _FindCache;
    }

    template <typename _K, typename _T>
    inline void Unordered_Map<_K, _T>::_AuthSize()
    {
        if (_Size == 0)
            assert("_Size is 0!!" && false);
    }

    template <typename _K, typename _T>
    inline Unordered_Map<_K, _T>::~Unordered_Map()
    {
        Flush();

        if (_Map != nullptr)
            ::operator delete(_Map, _Capacity * sizeof(_T));
        if (_Keys != nullptr)
            ::operator delete(_Keys, _Capacity * sizeof(_K));

        _Map = nullptr;
        _Keys = nullptr;
    }

    template <typename _K, typename _T>
    inline void Unordered_Map<_K, _T>::Flush()
    {
        // Delete all elements
        for (int i = 0; i < _Size; i++)
        {
            _Keys[i].~_K();
            _Map[i].~_T();
        }

        _Size = 0;
    }

    template <typename _K, typename _T>
    inline void Unordered_Map<_K, _T>::Reserve(int _NC)
    {
        if (_Capacity < _NC)
            _Alloc(_NC);
    }
} // namespace SP_STD
