#pragma once

#include "Vector.h"

template <typename T> T& Vector<T>::operator[] (Rank r) const {
    return _elem[r]; //assert : 0 <= r < _size
};

template <typename T> T& Vector<T>::remove (Rank r) {
	T e = _elem[r];
	remove(r, r+1);
	return e;
};

template <typename T> T& Vector<T>::insert( Rank r, T const& e) {
    _size++;
    Rank _index = _size;
    while(_index > r){
        _elem[_index] = _elem[_index--];
    }
    _elem[r] = e;
    return _elem[r];
};

template <typename T> int remove (Rank lo, Rank hi) {
   if ( lo == hi ) return 0; //出于效率考虑，单独处理退化情况，比如remove(0, 0)
   while ( hi < _size ) //区间[hi, _size)
      _elem[lo++] = _elem[hi++]; //顺次前移hi - lo个单元
   _size = lo; //更新规模，直接丢弃尾部[lo, _size = hi)区间
   return hi - lo; //返回被删除元素的数目
}