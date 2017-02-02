//                                               -*- C++ -*-
/**
 *  @brief MultiStart optimization algorithm
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
#include "openturns/MultiStart.hxx"
#include "openturns/PersistentObjectFactory.hxx"
#include "openturns/Cobyla.hxx"
#include "openturns/SpecFunc.hxx"
#include "openturns/Box.hxx"

BEGIN_NAMESPACE_OPENTURNS

CLASSNAMEINIT(MultiStart);

static const Factory<MultiStart> Factory_MultiStart;

/* Constructor with parameters */
MultiStart::MultiStart()
  : OptimizationSolverImplementation()
  , solver_(new Cobyla)
{
  // Nothing to do here
}


/* Constructor with parameters */
MultiStart::MultiStart(const OptimizationSolver & solver,
                       const NumericalSample & startingPoints)
  : OptimizationSolverImplementation(solver.getProblem())
  , solver_(solver)
  , startingPoints_(startingPoints)
{
}


void MultiStart::setProblem(const OptimizationProblem & problem)
{
  OptimizationSolverImplementation::setProblem(problem);
  solver_.setProblem(problem);
}


/* Check whether this problem can be solved by this solver.  Must be overloaded by the actual optimisation algorithm */
void MultiStart::checkProblem(const OptimizationProblem & problem) const
{
  // Nothing to do
}


void MultiStart::run()
{
  if (startingPoints_.getDimension() != getProblem().getDimension())
    throw InvalidArgumentException(HERE) << "The starting points dimension must match the problem dimension";

  // run the solver with each starting point
  OptimizationSolver solver(solver_);
  resultCollection_.clear();
  NumericalScalar bestValue = getProblem().isMinimization() ? SpecFunc::MaxNumericalScalar : -SpecFunc::MaxNumericalScalar;
  const UnsignedInteger size = startingPoints_.getSize();
  for (UnsignedInteger i = 0; i < size; ++ i)
  {
    solver.setStartingPoint(startingPoints_[i]);
    try
    {
      solver.run();
    }
    catch (Exception &)
    {
      continue;
    }
    OptimizationResult result(solver.getResult());
    resultCollection_.add(result);
    NumericalScalar currentValue = result.getOptimalValue()[0];
    if ((getProblem().isMinimization() && (currentValue < bestValue))
        || (!getProblem().isMinimization() && (currentValue > bestValue)))
    {
      bestValue = currentValue;
      setResult(result);
      LOGINFO(OSS() << "Best initial point so far=" << result.getOptimalPoint() << " value=" << result.getOptimalValue());
    }
  }
  LOGINFO(OSS() << resultCollection_.getSize() << " out of " << size << " local searches succeeded");

  if (resultCollection_.getSize() == 0)
  {
    throw InternalException(HERE) << "None of the local searches succeeded.";
  }
}


/* Virtual constructor */
MultiStart * MultiStart::clone() const
{
  return new MultiStart(*this);
}

/* String converter */
String MultiStart::__repr__() const
{
  OSS oss;
  oss << "class=" << getClassName()
      << " " << OptimizationSolverImplementation::__repr__()
      << " solver=" << solver_
      << " startingPoints=" << startingPoints_;
  return oss;
}

void MultiStart::setOptimizationSolver(const OptimizationSolver & solver)
{
  solver_ = solver;
}

OptimizationSolver MultiStart::getOptimizationSolver() const
{
  return solver_;
}

void MultiStart::setStartingPoints(const NumericalSample & startingPoints)
{
  startingPoints_ = startingPoints;
}


NumericalSample MultiStart::getStartingPoints() const
{
  return startingPoints_;
}


MultiStart::OptimizationResultCollection MultiStart::getResultCollection() const
{
  return resultCollection_;
}


/* Method save() stores the object through the StorageManager */
void MultiStart::save(Advocate & adv) const
{
  OptimizationSolverImplementation::save(adv);
  adv.saveAttribute("solver_", solver_);
  adv.saveAttribute("startingPoints_", startingPoints_);
}

/* Method load() reloads the object from the StorageManager */
void MultiStart::load(Advocate & adv)
{
  OptimizationSolverImplementation::load(adv);
  adv.loadAttribute("solver_", solver_);
  adv.loadAttribute("startingPoints_", startingPoints_);
}

END_NAMESPACE_OPENTURNS
