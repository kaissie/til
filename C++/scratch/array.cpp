#include <iostream>
#include <array>
template <typename Array>
struct array_iterator
{
  Array& a;
  std::size_t i;
  array_iterator(Array& a, std::size_t i)
    : a(a), i(i) {}

  array_iterator& operator ++ ()
  {
    ++i;
    return *this;
  }
  array_iterator operator ++ (int)
  {
    array_iterator copy = *this;
    ++*this;
    return copy;
  }

  array_iterator& operator -- ()
  {
    --i;
    return *this;
  }
  array_iterator operator -- (int)
  {
    array_iterator copy = *this;
    --*this;
    return copy;
  }

  bool operator == (array_iterator const & right)
  { return i == right.i; }
  bool operator != (array_iterator const & right)
  { return i != right.i; }

  array_iterator & operator += ( std::size_t n )
  {
      i += n ;
      return *this ;
  }
  array_iterator & operator -= ( std::size_t n )
  {
      i -= n ;
      return *this ;
  }

  array_iterator operator + ( std::size_t n ) const
  {
      auto copy = *this ;
      copy += n ;
      return copy ;
  }
  array_iterator operator - ( std::size_t n ) const
  {
      auto copy = *this ;
      copy -= n ;
      return copy ;
  }

  typename Array::reference operator * ()
  { return a[i]; }

  typename Array::reference operator [] ( std::size_t n ) const
  { return *( *this + n ); }
};


template <typename Array>
struct array_const_iterator
{
  Array const & a;
  std::size_t i;
  array_const_iterator(Array const & a, std::size_t i)
    : a(a), i(i) {}

  array_const_iterator& operator ++ ()
  {
    ++i;
    return *this;
  }
  array_const_iterator operator ++ (int)
  {
    auto copy = *this;
    ++*this;
    return copy;
  }

  array_const_iterator& operator -- ()
  {
    --i;
    return *this;
  }
  array_const_iterator operator -- (int)
  {
    auto copy = *this;
    --*this;
    return copy;
  }

  bool operator == (array_const_iterator const & right) const
  { return i == right.i; }
  bool operator != (array_const_iterator const & right) const
  { return i != right.i; }

  array_const_iterator & operator += ( std::size_t n )
  {
      i += n ;
      return *this ;
  }
  array_const_iterator & operator -= ( std::size_t n )
  {
      i -= n ;
      return *this ;
  }

  array_const_iterator operator + ( std::size_t n ) const
  {
      auto copy = *this ;
      copy += n ;
      return copy ;
  }
  array_const_iterator operator - ( std::size_t n ) const
  {
      auto copy = *this ;
      copy -= n ;
      return copy ;
  }

  typename Array::const_reference operator * ()
  { return a[i]; }
  typename Array::const_reference operator [] ( std::size_t i ) const
  { return *(*this + i);}

};

template <typename T, std::size_t N>
struct array {
  using reference = T &;
  using const_reference = const T &;
  using iterator = array_iterator<array>;
  using const_iterator = array_const_iterator<array>;

  T storage[N];
  std::size_t size() const { return N; };

  reference operator [] (std::size_t i)
  { return storage[i]; }
  const_reference operator [] (std::size_t i) const
  { return storage[i]; }

  reference front()
  { return storage[0]; }
  const_reference front() const
  { return storage[0]; }

  reference back()
  { return storage[N-1]; }
  const_reference back() const
  { return storage[N-1]; }

  iterator begin()
  { return iterator(*this, 0); }
  iterator end()
  { return iterator(*this, N); }

  const_iterator begin() const
  { return const_iterator(*this, 0); }
  const_iterator end() const
  { return const_iterator(*this, N); }

  const_iterator cbegin() const
  { return const_iterator(*this, 0) ; }
  const_iterator cend() const
  { return const_iterator(*this, N) ; }

};

int main(int argc, char const *argv[]) {
  const array<int,5> a = {1,2,3,4,5};

  const std::array<int,3> b = {7,8,9};
  for(auto e: a){
    std::cout << e << '\n';
  }

}
