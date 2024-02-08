#pragma once

#include <assert.h>

namespace SP_STD
{
    template <typename _K, typename _T>
    class Unordered_Map
    {
    public:
        Unordered_Map() {}
        ~Unordered_Map();

        // Getters

        const int Size() const { return _Size; }
        const int Capacity() const { return _Capacity; }

        void Flush();

        // Operators
        _T &operator[](const _K &K);

    private:
        // The Key array
        _K *_Keys = nullptr;

        // The main array which holds the data
        _T *_Map = nullptr;

        // Stores the Size Used of the Maps
        int _Size = 0;
        // Stores the Capacity of the Maps
        int _Capacity = 0;

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
        return _Map[Find(K)];
    }

    template <typename _K, typename _T>
    inline void Unordered_Map<_K, _T>::_Alloc(int _NC)
    {
        // for No memory allocated
        if (_Map == nullptr || _Keys == nullptr)
        {
            _Map = new _T[_NC];
            _Keys = new _K[_NC];
            _Capacity = _NC;

            return;
        }
    }

    template <typename _K, typename _T>
    inline int Unordered_Map<_K, _T>::_Find(const _K &K)
    {
        _AuthSize();

        for (int i = 0; i < _Size; i++)
            if (_Keys[i] == K)
                return i;

        return -1;
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

        if(_Map != nullptr)
            delete[] _Map;
        if(_Keys != nullptr)
            delete[] _Keys;

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
} // namespace SP_STD
