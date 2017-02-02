//                                               -*- C++ -*-
/**
 *  @brief LinearProfile
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
#ifndef OPENTURNS_OPTIMALLINEARPROFILE_HXX
#define OPENTURNS_OPTIMALLINEARPROFILE_HXX

#include "openturns/TemperatureProfileImplementation.hxx"

namespace OT
{

/**
 * @class LinearProfile
 *
 * LinearProfile is a linear temperature profile for SimulatedAnnealing
 */
class OT_API LinearProfile
  : public TemperatureProfileImplementation
{
  CLASSNAME;

public:
  /** Default constructor */
  LinearProfile(const NumericalScalar T0=10.0, const UnsignedInteger iMax=2000);

  /** Virtual constructor method */
  LinearProfile * clone() const;

  /** Compute temperature T(i) */
  NumericalScalar operator()(UnsignedInteger i) const;

  /** String converter */
  String __repr__() const;

  /** Method save() stores the object through the StorageManager */
  void save(Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(Advocate & adv);

private:
  mutable NumericalScalar iMaxInv_;

  friend class Factory<LinearProfile>;
}; /* class LinearProfile */

} /* namespace OT */

#endif /* OT_OPTIMALLINEARPROFILE_HXX */
