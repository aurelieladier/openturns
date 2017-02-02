//                                               -*- C++ -*-
/**
 *  @brief The class that implements linear combination of functions.
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
#include "openturns/LinearCombinationFunction.hxx"
#include "openturns/LinearCombinationEvaluationImplementation.hxx"
#include "openturns/LinearCombinationGradientImplementation.hxx"
#include "openturns/LinearCombinationHessianImplementation.hxx"

BEGIN_NAMESPACE_OPENTURNS

CLASSNAMEINIT(LinearCombinationFunction);

/* Default constructor */
LinearCombinationFunction::LinearCombinationFunction ()
  : NumericalMathFunction()
{
}


/* Parameter constructor */
LinearCombinationFunction::LinearCombinationFunction (const NumericalMathFunctionCollection & functionCollection,
                                                      const NumericalPoint & coefficients)
  : NumericalMathFunction()
{
  const LinearCombinationEvaluationImplementation evaluation(functionCollection, coefficients);
  setEvaluation(evaluation.clone());
  setGradient(new LinearCombinationGradientImplementation(evaluation));
  setHessian(new LinearCombinationHessianImplementation(evaluation));
}


/* Comparison operator */
Bool LinearCombinationFunction::operator ==(const LinearCombinationFunction & other) const
{
  return true;
}

/* String converter */
String LinearCombinationFunction::__repr__() const
{
  return getImplementation()->__repr__();
}

String LinearCombinationFunction::__str__(const String & offset) const
{
  return getImplementation()->__str__(offset);
}

END_NAMESPACE_OPENTURNS
