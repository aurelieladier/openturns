//                                               -*- C++ -*-
/**
 *  @brief Abstract top-level class for all numerical math hessian implementations
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
#ifndef OPENTURNS_NUMERICALMATHHESSIANIMPLEMENTATION_HXX
#define OPENTURNS_NUMERICALMATHHESSIANIMPLEMENTATION_HXX

#include "openturns/PersistentObject.hxx"
#include "openturns/NumericalPoint.hxx"
#include "openturns/NumericalPointWithDescription.hxx"
#include "openturns/Description.hxx"
#include "openturns/Indices.hxx"
#include "openturns/SymmetricTensor.hxx"
#include "openturns/Pointer.hxx"
#include "openturns/StorageManager.hxx"

BEGIN_NAMESPACE_OPENTURNS

/**
 * @class NumericalMathHessianImplementation
 *
 * This class offers an abstract interface for the implementation
 * of an real numerical mathematical hessian into the platform.
 */
class OT_API NumericalMathHessianImplementation
  : public PersistentObject
{
  CLASSNAME;
public:

  typedef Pointer<NumericalMathHessianImplementation> Implementation;


  /** Default constructor */
  NumericalMathHessianImplementation();

  /** Virtual constructor */
  virtual NumericalMathHessianImplementation * clone() const;

  /** Comparison operator */
  Bool operator ==(const NumericalMathHessianImplementation & other) const;

  /** String converter */
  virtual String __repr__() const;
  virtual String __str__(const String & offset = "") const;


  /** Test for actual implementation */
  virtual Bool isActualImplementation() const;

  /** Get the i-th marginal evaluation */
  virtual Implementation getMarginal(const UnsignedInteger i) const;

  /** Get the evaluation corresponding to indices components */
  virtual Implementation getMarginal(const Indices & indices) const;



  /* Here is the interface that all derived class must implement */

  /** Hessian method */
  virtual SymmetricTensor hessian(const NumericalPoint & inP) const;
  virtual SymmetricTensor hessian(const NumericalPoint & inP,
                                  const NumericalPoint & parameter);

  /** Accessor for input point dimension */
  virtual UnsignedInteger getInputDimension() const;

  /** Accessor for output point dimension */
  virtual UnsignedInteger getOutputDimension() const;

  /** Parameters value accessor */
  virtual NumericalPoint getParameter() const;
  virtual void setParameter(const NumericalPoint & parameter);

  /** Get the number of calls to operator() */
  UnsignedInteger getCallsNumber() const;

  /** Method save() stores the object through the StorageManager */
  void save(Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(Advocate & adv);

protected:

  /** Number of calls since the construction */
  mutable UnsignedInteger callsNumber_;

  /** The value of the parameters */
  NumericalPoint parameter_;

private:


}; /* class NumericalMathHessianImplementation */


END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_NUMERICALMATHHESSIANIMPLEMENTATION_HXX */
