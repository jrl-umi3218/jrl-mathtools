/*
 *  Copyright 2007 Florent Lamiraux
 */

#ifndef JRLMATHTOOLS_ANGLE_H
#define JRLMATHTOOLS_ANGLE_H

#include <iostream>
#include <math.h>

namespace jrlMathTools {

  /**
     \brief This class implements angles.
  */

  class Cangle {
  public:
    /**
       \brief Constructor
    */
    Cangle():attAngle(0) {
    };

    /**
       \brief Constructor by value.
    */
    Cangle(const double& inAngle):attAngle(inAngle) {
      setBetweenMinusAndPlusPI();
    };

    /**
       \brief Copy Constructor.
    */
    Cangle(const Cangle& inAngle):attAngle(inAngle.attAngle) {
    };

    /**
       \brief Cast into a double.
    */
    operator const double& () const {
      return attAngle;
    };

    /**
       \brief Operator = with a double
    */
    const double& operator=(const double& inDouble) {
      attAngle = inDouble;
      setBetweenMinusAndPlusPI();
      return inDouble;
    };

    /**
       \brief Difference between two angles
    */
    Cangle operator-(Cangle inAngle) const {
      return Cangle(attAngle-inAngle.attAngle);
    };

    /**
       \brief Sum of two angles.
    */
    Cangle operator+(Cangle inAngle) const {
      Cangle outAngle(attAngle + inAngle.attAngle);
      return outAngle;
    };

    /**
       \brief Multiplication of an angle by a real number.
    */
    friend Cangle operator*(const double& coef, const Cangle& inAngle) 
    {
      return Cangle(coef*inAngle.attAngle);
    };

    /**
       \brief Interpolation between two angles
       \param alpha interpolation parameter between 0 and 1.
       \param inAngle second angle of interpolation.
       \return an angle between this one and inAngle along the shortest arc.
       \li if alpha = 0, return this angle,
       \li if alpha = 1, return inAngle. 
    */
    Cangle interpolate(const double& alpha, const Cangle& inAngle) const
    {
      Cangle diffAngle = inAngle.attAngle - attAngle;
      return Cangle(attAngle+alpha*diffAngle.attAngle);
    };

    /**
       \brief output to a stream.
    */
    friend std::ostream& operator<<(std::ostream &os, const Cangle& inAngle) {
      os << inAngle.attAngle;
      return os;
    };

    /**
       \brief Distance on unit circle.
    */
    double distance(const Cangle& inAngle) const {
      Cangle diffAngle = *this - inAngle;
      return fabs(diffAngle.attAngle);
    };

    friend double cos(const Cangle& inAngle) {
      return cos(inAngle.attAngle);
    }

    friend double sin(const Cangle& inAngle) {
      return sin(inAngle.attAngle);
    }

    friend double tan(const Cangle& inAngle) {
      return tan(inAngle.attAngle);
    }

    /**
       @}
    */

  protected:

    /**
       \brief Set angle between -PI and PI.
    */
    void setBetweenMinusAndPlusPI()
    {
      while (attAngle < -M_PI){
	attAngle += 2*M_PI;
      }
      while (attAngle > M_PI){
	attAngle -= 2*M_PI;
      }
    };

    /**
       \brief angular value.
    */
    double attAngle;
  };
};

#endif
