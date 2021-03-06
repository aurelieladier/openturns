//                                               -*- C++ -*-
/**
 *  @brief SpaceFillingMinDist
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
#ifndef OPENTURNS_SPACEFILLINGMINDIST_HXX
#define OPENTURNS_SPACEFILLINGMINDIST_HXX

#include "openturns/PersistentObject.hxx"
#include "openturns/SpaceFillingImplementation.hxx"

namespace OT
{

/**
 * @class SpaceFillingMinDist
 *
 * This class computes minimal distance between sample points.
 */
class OT_API SpaceFillingMinDist
  : public SpaceFillingImplementation
{
  CLASSNAME;

public:
  /** Default constructor */
  SpaceFillingMinDist();

  /** Virtual constructor method */
  SpaceFillingMinDist * clone() const;

  /** String converter */
  String __repr__() const;

  /** Evaluate criterion on a sample */
  NumericalScalar evaluate(const NumericalSample& sample) const;

}; /* class SpaceFillingMinDist */

} /* namespace OT */

#endif /* OT_SPACEFILLINGMINDIST_HXX */
