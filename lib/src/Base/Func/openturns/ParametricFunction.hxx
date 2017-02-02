//                                               -*- C++ -*-
/**
 *  @brief The class that implements parametric functions.
 *
 *  Copyright 2005-2017 Airbus-EDF-IMACS-Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef OPENTURNS_PARAMETRICFUNCTION_HXX
#define OPENTURNS_PARAMETRICFUNCTION_HXX

#include "openturns/NumericalMathFunction.hxx"
#include "openturns/NumericalPoint.hxx"
#include "openturns/Matrix.hxx"
#include "openturns/SymmetricTensor.hxx"

BEGIN_NAMESPACE_OPENTURNS


/**
 * @class ParametricFunction
 *
 */
class OT_API ParametricFunction
  : public NumericalMathFunction
{
  CLASSNAME;
public:

  /* Default constructor */
  ParametricFunction();

  /** Parameter constructor */
  ParametricFunction (const NumericalMathFunction & function,
                      const Indices & set,
                      const NumericalPoint & referencePoint,
                      const Bool parametersSet = true);

  /** Comparison operator */
  Bool operator ==(const ParametricFunction & other) const;

  /** String converter */
  virtual String __repr__() const;
  virtual String __str__(const String & offset = "") const;

}; /* class QuadraticNumericalMathFunction */


END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_PARAMETRICFUNCTION_HXX */
