// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size should be less than max");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz];
      copy(v.pMem, v.pMem+ sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      pMem = nullptr;
      swap(*this, v);
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v)
          return *this;
      TDynamicVector temp(v);
      swap(*this, temp);
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      swap(*this, v);
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind < 0 || ind >= sz)
          throw("wrong index");
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (ind < 0 || ind >= sz)
          throw("wrong index");
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < 0 || ind >= sz)
          throw("wrong index");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0 || ind >= sz)
          throw("wrong index");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (this == &v)
          return true;
      if (sz != v.sz)
          return false;
      for (int i = 0; i < sz; i++)
      {
          if (pMem[i] != v.pMem[i])
              return false;
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (this == &v)
          return false;
      if (sz != v.sz)
          return true;
      for (int i = 0; i < sz; i++)
      {
          if (pMem[i] != v.pMem[i])
              return true;
      }
      return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector temp(sz);
      for (int i = 0; i < sz; i++)
      {
          temp.pMem[i] = pMem[i] + val;
      }
      return temp;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector temp(sz);
      for (int i = 0; i < sz; i++)
      {
          temp.pMem[i] = pMem[i] - val;
      }
      return temp;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector temp(sz);
      for (int i = 0; i < sz; i++)
      {
          temp.pMem[i] = pMem[i] * val;
      }
      return temp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw out_of_range("Vectors are different size");
      TDynamicVector temp(v.sz);
      for (int i = 0; i < sz && i < v.sz; i++)
          temp.pMem[i] = pMem[i] + v.pMem[i];
      return temp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw out_of_range("Vectors are different size");
      TDynamicVector temp(v.sz);
      for (int i = 0; i < sz && i < v.sz; i++)
          temp.pMem[i] = pMem[i] - v.pMem[i];
      return temp;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz)
          throw out_of_range("Vectors are different size");
      int res = 0;
      for (size_t i = 0; i < sz; i++)
          res += pMem[i] * v.pMem[i];
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix transpose(const TDynamicMatrix& m) 
    {
        TDynamicMatrix tmp(m.sz);
        for (int i = 0; i < m.sz; i++)
            for (int j = 0; j < m.sz; j++)
                tmp[i][j] = m[j][i];
        return tmp;
    }

  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      return TDynamicVector<TDynamicVector<T>>::operator==(m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      return TDynamicVector<TDynamicVector<T>>::operator*(val);
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      TDynamicVector<T> temp(sz);
      for (int i = 0; i < sz; i++)
          temp[i] = pMem[i] * v;
      return temp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw out_of_range("Matrix are different size");
      TDynamicMatrix temp(sz);
      for (int i = 0; i < sz; i++)
          temp.pMem[i] = pMem[i] + m.pMem[i];
      return temp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw out_of_range("Matrix are different size");
      TDynamicMatrix temp(sz);
      for (int i = 0; i < sz; i++)
          temp.pMem[i] = pMem[i] - m.pMem[i];
      return temp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw out_of_range("Matrix are different size");
      TDynamicMatrix res(sz);
      TDynamicMatrix temp = transpose(m);
      for (int i = 0; i < sz; i++)
          for (int j = 0; j < sz; j++)
              res[i][j] = pMem[i] * temp[j];
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v.pMem[i]; // требуется оператор>> для типа T
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          ostr << v.pMem[i] << endl; // требуется оператор<< для типа T
      return ostr;
  }
};

#endif
