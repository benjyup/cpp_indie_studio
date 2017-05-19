//
// Created by vincent on 05/05/17.
//

#ifndef CPP_INDIE_STUDIO_VECTOR3_HPP
#define CPP_INDIE_STUDIO_VECTOR3_HPP
#include <string>
#include <ostream>

template <typename T = int>
class Vector3
{
 public:
  Vector3(const T &x, const T &y, const T &z);
  ~Vector3(void);

  std::string 		toString(void) const;

  Vector3            	&operator+(const Vector3 &);
  Vector3               &operator-(const Vector3 &);
  bool 			operator==(const Vector3 &rhs) const;
  bool			operator!=(const Vector3 &rhs) const;

 private:
  T 			_x;
  T 			_y;
  T 			_z;
};

template <typename T>
Vector3<T>::Vector3(T const &x, T const &y, T const &z)
	: _x(x),
	  _y(y),
	  _z(z)
{ }

template <typename T>
Vector3<T>::~Vector3(void)
{ }

template <typename T>
std::string Vector3<T>::toString(void) const
{
  return ("x = " + std::to_string(this->_x) + " y = " + std::to_string(this->_y) + " z = " + std::to_string(this->_z));
}

template <typename T>
Vector3<T> &Vector3<T>::operator+(const Vector3 &o)
{
  this->_x += o._x;
  this->_y += o._y;
  this->_z += o._z;
  return (*this);
}

template <typename T>
Vector3<T> &Vector3<T>::operator-(const Vector3 &o)
{
  this->_x -= o._x;
  this->_y -= o._y;
  this->_z -= o._z;
  return (*this);
}

template <typename T>
bool Vector3<T>::operator==(const Vector3 &o) const
{
  return this->_x == o._x &&
	 this->_y == o._y &&
	 this->_z == o._z;
}

template <typename T>
bool Vector3<T>::operator!=(const Vector3 &o) const
{
  return (!(o == *this));
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vector3<T> &vector3)
{
  os << vector3.toString();
  return os;
}


/*template <typename T>
std::ostream &operator<<(std::ostream &os, const Vector3<T> &vector3);*/

#endif //CPP_INDIE_STUDIO_VECTOR3_HPP
