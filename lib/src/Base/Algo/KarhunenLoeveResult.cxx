//                                               -*- C++ -*-
/**
 *  @brief Karhunen-Loeve decomposition and projection
 *
 *  Copyright 2005-2016 Airbus-EDF-IMACS-Phimeca
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

#include "openturns/KarhunenLoeveResult.hxx"

BEGIN_NAMESPACE_OPENTURNS



CLASSNAMEINIT(KarhunenLoeveResult);


/* Default constructor */
KarhunenLoeveResult::KarhunenLoeveResult()
  : TypedInterfaceObject<KarhunenLoeveResultImplementation>( new KarhunenLoeveResultImplementation() )
{
  // Nothing to do
}

/* Constructor from implementation */
KarhunenLoeveResult::KarhunenLoeveResult(const KarhunenLoeveResultImplementation & implementation)
  : TypedInterfaceObject<KarhunenLoeveResultImplementation>( implementation.clone() )
{
  // Nothing to do
}

/* Constructor from implementation */
KarhunenLoeveResult::KarhunenLoeveResult(const Implementation & p_implementation)
  : TypedInterfaceObject<KarhunenLoeveResultImplementation>( p_implementation )
{
  // Nothing to do
}

/* Threshold accessors */
NumericalScalar KarhunenLoeveResult::getThreshold() const
{
  return getImplementation()->getThreshold();
}

/* Covariance model accessor */
CovarianceModel KarhunenLoeveResult::getCovarianceModel() const
{
  return getImplementation()->getCovarianceModel();
}

/* Eigenvalues accessor */
NumericalPoint KarhunenLoeveResult::getEigenValues() const
{
  return getImplementation()->getEigenValues();
}

/* Modes accessors */
Basis KarhunenLoeveResult::getModes() const
{
  return getImplementation()->getModes();
}

ProcessSample KarhunenLoeveResult::getModesAsProcessSample() const
{
  return getImplementation()->getModesAsProcessSample();
}

/* Scaled modes accessors */
Basis KarhunenLoeveResult::getScaledModes() const
{
  return getImplementation()->getScaledModes();
}

ProcessSample KarhunenLoeveResult::getScaledModesAsProcessSample() const
{
  return getImplementation()->getScaledModesAsProcessSample();
}

/* Projection matrix accessor */
Matrix KarhunenLoeveResult::getProjectionMatrix() const
{
  return getImplementation()->getProjectionMatrix();
}

/* Projection method */
NumericalPoint KarhunenLoeveResult::project(const NumericalMathFunction & function) const
{
  return getImplementation()->project(function);
}

NumericalPoint KarhunenLoeveResult::project(const Field & field) const
{
  return getImplementation()->project(field);
}

NumericalSample KarhunenLoeveResult::project(const Basis & basis) const
{
  return getImplementation()->project(basis);
}

NumericalSample KarhunenLoeveResult::project(const ProcessSample & sample) const
{
  return getImplementation()->project(sample);
}

/* Lift method */
NumericalMathFunction KarhunenLoeveResult::lift(const NumericalPoint & coefficients) const
{
  return getImplementation()->lift(coefficients);
}

Field KarhunenLoeveResult::liftAsField(const NumericalPoint & coefficients) const
{
  return getImplementation()->liftAsField(coefficients);
}

/* String converter */
String KarhunenLoeveResult::__repr__() const
{
  return getImplementation()->__repr__();
}

String KarhunenLoeveResult::__str__(const String & offset) const
{
  return getImplementation()->__str__( offset );
}

END_NAMESPACE_OPENTURNS
