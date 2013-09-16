// Copyright (C) 2008-2013 LAAS-CNRS, JRL AIST-CNRS.
//
// This file is part of jrl-mathtools.
// jrl-mathtools is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// jrl-mathtools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// You should have received a copy of the GNU Lesser General Public License
// along with jrl-mathtools.  If not, see <http://www.gnu.org/licenses/>.

#ifndef JRL_MATHTOOLS_COMMON_HH
# define JRL_MATHTOOLS_COMMON_HH

// This is a custom numeric type used to check
// that the container can handle non-native types.
struct MyNumericType
{
public:
  MyNumericType (int i = 0)
    : i (i)
  {}

  bool operator== (const MyNumericType& mnt) const
  {
    return i == mnt.i;
  }

  int i;
};

std::ostream& operator<< (std::ostream& os, const MyNumericType& mnt)
{
  os << mnt.i;
  return os;
}

#endif //! JRL_MATHTOOLS_COMMON_HH
