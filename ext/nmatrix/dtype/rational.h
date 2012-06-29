/////////////////////////////////////////////////////////////////////
// = NMatrix
//
// A linear algebra library for scientific computation in Ruby.
// NMatrix is part of SciRuby.
//
// NMatrix was originally inspired by and derived from NArray, by
// Masahiro Tanaka: http://narray.rubyforge.org
//
// == Copyright Information
//
// SciRuby is Copyright (c) 2010 - 2012, Ruby Science Foundation
// NMatrix is Copyright (c) 2012, Ruby Science Foundation
//
// Please see LICENSE.txt for additional copyright notices.
//
// == Contributing
//
// By contributing source code to SciRuby, you agree to be bound by
// our Contributor Agreement:
//
// * https://github.com/SciRuby/sciruby/wiki/Contributor-Agreement
//
// == dtype.h
//
// Functions and classes for dealing with rational numbers.

#ifndef COMPLEX_H
#define COMPLEX_H

/*
 * Standard Includes
 */

/*
 * Project Includes
 */

/*
 * Macros
 */

#define RATIONAL_RATIONAL_OPS(other_type)																											\
	inline Rational<Type> operator+(const Rational<other_type>& other) const {									\
		long simplify;																																						\
		Rational<Type> result;																																		\
																																															\
		result.n = (this->n * other.d) + (other.n * this->d);																			\
		result.d = this->d * other.d;																															\
																																															\
		simplify = gcf<Type>(result.n, result.d);																									\
																																															\
		result.n /= simplify;																																			\
		result.d /= simplify;																																			\
																																															\
		return result;																																						\
	}																																														\
																																															\
	inline Rational<Type> operator-(const Rational<other_type>& other) const {									\
		long simplify;																																						\
		Rational<Type> result;																																		\
																																															\
		result.n = (this->n * other.d) - (other.n * this->d);																			\
		result.d = this->d * other.d;																															\
																																															\
		simplify = gcf<Type>(result.n, result.d);																									\
																																															\
		result.n /= simplify;																																			\
		result.d /= simplify;																																			\
																																															\
		return result;																																						\
	}																																														\
																																															\
	inline Rational<Type> operator*(const Rational<other_type>& other) const {									\
		int g1 = gcf<Type>(this->n, other.d);																											\
		int g2 = gcf<Type>(this->d, other.n);																											\
																																															\
		return Rational<Type>((this->n / g1) * (other.n / g2), (this->d / g2) * (other.d / g1));	\
	}																																														\
																																															\
	inline Rational<Type> operator/(const Rational<other_type>& other) const {									\
		return *this * Rational<other_type>(other.d, other.n);																		\
	}																																														\
																																															\
	inline Rational<Type> operator%(const Rational<other_type>& other) const {									\
		Rational<Type> prod;																																			\
		long floor_div;																																						\
																																															\
		floor_div = (this->n * other.n) / (this->d * other.d);																		\
		prod = other * Rational<long>(floor_div, 1);																							\
		return Rational<long>(this->n, other.n) - prod;																						\
	}																																														\
																																															\
	inline bool operator<(const Rational<other_type>& other) const {														\
		return (this->n * other.d) < (other.n * this->d);																					\
	}																																														\
																																															\
	inline bool operator>(const Rational<other_type>& other) const {														\
		return (this->n * other.d) > (other.n * this->d);																					\
	}																																														\
																																															\
	inline bool operator==(const Rational<other_type>& other) const {														\
		return (this->n == other.n) && (this->d == other.d);																			\
	}																																														\
																																															\
	inline bool operator!=(const Rational<other_type>& other) const {														\
		return !(*this == other);																																	\
	}																																														\
																																															\
	inline bool operator<=(const Rational<other_type>& other) const {														\
		return (*this < other) || (*this == other);																								\
	}																																														\
																																															\
	inline bool operator>=(const Rational<other_type>& other) const {														\
		return (*this > other) || (*this == other);																								\
	}

#define RATIONAL_NATIVE_OPS(other_type) 														\
	inline Rational<Type> operator+(const other_type& other) const {	\
		long simplify;																									\
		Rational<Type> result;																					\
																																		\
		result.n = this->n + (other.n * this->d);												\
		result.d = this->d;																							\
																																		\
		simplify = gcf<Type>(result.n, result.d);												\
																																		\
		result.n /= simplify;																						\
		result.d /= simplify;																						\
																																		\
		return result;																									\
	}																																	\
																																		\
	inline Rational<Type> operator-(const other_type& other) const {	\
		int simplify;																										\
		Rational<Type> result;																					\
																																		\
		result.n = this->n - (other.n * this->d);												\
		result.d = this->d;																							\
																																		\
		simplify = gcf<Type>(result.n, result.d);												\
																																		\
		result.n /= simplify;																						\
		result.d /= simplify;																						\
																																		\
		return result;																									\
	}																																	\
																																		\
	inline Rational<Type> operator*(const other_type& other) const {	\
		long simplify;																									\
		Rational<Type> result;																					\
																																		\
		result.n = other * this->n;																			\
																																		\
		simplify = gcf<Type>(result.n, this->d);												\
																																		\
		result.n /= simplify;																						\
		result.d  = this->d / simplify;																	\
																																		\
		return result;																									\
	}																																	\
																																		\
	inline Rational<Type> operator/(const other_type& other) const {	\
		return *this * other;																						\
	}																																	\
																																		\
	inline Rational<Type> operator%(const other_type& other) const {	\
		return *this % Rational<Type>(other, 1);												\
	}																																	\
																																		\
	inline bool operator<(const other_type& other) const {						\
		return this->n < (other.n * this->d);														\
	}																																	\
																																		\
	inline bool operator>(const other_type& other) const {						\
		return this->n > (other.n * this->d);														\
	}																																	\
																																		\
	inline bool operator==(const other_type& other) const {						\
		return (this->d == 1) && (this->n == other);										\
	}																																	\
																																		\
	inline bool operator!=(const other_type& other) const {						\
		return !(*this == other);																				\
	}																																	\
																																		\
	inline bool operator<=(const other_type& other) const {						\
		return (*this < other) || (*this == other);											\
	}																																	\
																																		\
	inline bool operator>=(const other_type& other) const {						\
		return (*this > other) || (*this == other);											\
	}

/*
 * Types
 */
template <typename Type> class Rational;

typedef Rational<short>	Rational32;
typedef Rational<int>		Rational64;
typedef Rational<long>	Rational128;

/*
 * Classes and Functions
 */

template <typename Type>
inline Type gcf(Type x, Type y) {
  Type t;

  if (x < 0) x = -x;
  if (y < 0) y = -y;

  if (x == 0) return y;
  if (y == 0) return x;

  while (x > 0) {
    t = x;
    x = y % x;
    y = t;
  }

  return y;
}

template <typename Type>
class Rational {
	public:
		// The numerator and denominator of the rational number.
		Type n;
		Type d;
	
		/*
		 * Default constructor.
		 */
		inline Rational(Type n = 0, Type d = 1) {
			this->n = n;
			this->d = d;
		}
		
		/*
		 * Copy constructors.
		 */
		inline Rational(const Rational<Type>& other) {
			this->n = other.n;
			this->d = other.d;
		}
		
		/*
		 * Binary operator definitions for varous types.
		 */
		 
		 RATIONAL_RATIONAL_OPS(short)
		 RATIONAL_RATIONAL_OPS(int)
		 RATIONAL_RATIONAL_OPS(long)
		 
		 RATIONAL_NATIVE_OPS(char)
		 RATIONAL_NATIVE_OPS(unsigned char)
		 RATIONAL_NATIVE_OPS(short)
		 RATIONAL_NATIVE_OPS(int)
		 RATIONAL_NATIVE_OPS(long)
};

#endif
