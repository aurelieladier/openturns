//                                               -*- C++ -*-
/**
 *  @brief The test file of class MeixnerDistribution for standard methods
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
#include "openturns/OT.hxx"
#include "openturns/OTtestcode.hxx"

using namespace OT;
using namespace OT::Test;

int main(int argc, char *argv[])
{
  TESTPREAMBLE;
  OStream fullprint(std::cout);
  setRandomGenerator();

  try
  {
    ResourceMap::SetAsUnsignedInteger( "MeixnerDistribution-CDFIntegrationNodesNumber", 8 );
    ResourceMap::SetAsUnsignedInteger( "MeixnerDistribution-CDFDiscretization", 100 );
    ResourceMap::SetAsNumericalScalar( "MeixnerDistribution-MaximumAbsoluteError", 1.0e-6 );
    ResourceMap::SetAsNumericalScalar( "MeixnerDistribution-MaximumRelativeError", 1.0e-6 );
    ResourceMap::SetAsNumericalScalar( "MeixnerDistribution-MaximumConstraintError", 1.0e-6 );
    ResourceMap::SetAsNumericalScalar( "MeixnerDistribution-MaximumObjectiveError", 1.0e-6 );
    MeixnerDistribution distribution(1.5, 0.5, 2.5, -0.5);
    UnsignedInteger size = 1000;
    NumericalSample sample(distribution.getSample(size));
    MeixnerDistributionFactory factory;
    CovarianceMatrix covariance;
    // Distribution estimatedDistribution(factory.build(sample, covariance));
    Distribution estimatedDistribution(factory.build(sample));
    fullprint << "Distribution          =" << distribution << std::endl;
    fullprint << "Estimated distribution=" << estimatedDistribution << std::endl;
    // fullprint << "Covariance=" << covariance << std::endl;
    estimatedDistribution = factory.build();
    fullprint << "Default distribution=" << estimatedDistribution << std::endl;
    estimatedDistribution = factory.build(distribution.getParameter());
    fullprint << "Distribution from parameters=" << estimatedDistribution << std::endl;
    MeixnerDistribution estimatedMeixnerDistribution(factory.buildAsMeixnerDistribution(sample));
    fullprint << "MeixnerDistribution          =" << distribution << std::endl;
    fullprint << "Estimated meixnerDistribution=" << estimatedMeixnerDistribution << std::endl;
    estimatedMeixnerDistribution = factory.buildAsMeixnerDistribution();
    fullprint << "Default meixnerDistribution=" << estimatedMeixnerDistribution << std::endl;
    estimatedMeixnerDistribution = factory.buildAsMeixnerDistribution(distribution.getParameter());
    fullprint << "MeixnerDistribution from parameters=" << estimatedMeixnerDistribution << std::endl;
  }
  catch (TestFailed & ex)
  {
    std::cerr << ex << std::endl;
    return ExitCode::Error;
  }


  return ExitCode::Success;
}
