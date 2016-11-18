//                                               -*- C++ -*-
/**
 *  @brief Meshing algorithm for levelSets
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
 *  Id:      $Id$
 */
#include "openturns/PersistentObjectFactory.hxx"
#include "openturns/LevelSetMesher.hxx"
#include "openturns/IntervalMesher.hxx"
#include "openturns/PersistentObjectFactory.hxx"
#include "openturns/Exception.hxx"
#include "openturns/OptimizationProblem.hxx"
#include "openturns/LinearNumericalMathFunction.hxx"
#include "openturns/AbdoRackwitz.hxx"
#include "openturns/CenteredFiniteDifferenceGradient.hxx"
#include "openturns/NLopt.hxx"

BEGIN_NAMESPACE_OPENTURNS

CLASSNAMEINIT(LevelSetMesher);
static const Factory<LevelSetMesher> RegisteredFactory;


/* Default constructor */
LevelSetMesher::LevelSetMesher()
  : PersistentObject()
  , discretization_(0)
  , solver_(AbdoRackwitz())
{
  // Nothing to do
}

/* Parameter constructor */
LevelSetMesher::LevelSetMesher(const Indices & discretization,
                               const OptimizationSolver & solver)
  : PersistentObject()
  , discretization_(discretization)
  , solver_(solver)
{
  // Check if the discretization is valid
  for (UnsignedInteger i = 0; i < discretization.getSize(); ++i)
    if (discretization[i] == 0) throw InvalidArgumentException(HERE) << "Error: expected a positive discretization, got " << discretization;
}

/* Virtual constructor */
LevelSetMesher * LevelSetMesher::clone() const
{
  return new LevelSetMesher(*this);
}

/* String converter */
String LevelSetMesher::__repr__() const
{
  OSS oss(true);
  oss << "class=" << LevelSetMesher::GetClassName()
      << " discretization=" << discretization_;
  return oss;
}

/* String converter */
String LevelSetMesher::__str__(const String & offset) const
{
  return __repr__();
}

/* Optimization solver accessor */
void LevelSetMesher::setOptimizationSolver(const OptimizationSolver & solver)
{
  solver_ = solver;
}

OptimizationSolver LevelSetMesher::getOptimizationSolver() const
{
  return solver_;
}

/* Discretization accessors */
void LevelSetMesher::setDiscretization(const Indices & discretization)
{
  // At least one slice per dimension
  for (UnsignedInteger i = 0; i < discretization.getSize(); ++i)
    if (discretization_[i] == 0) throw InvalidArgumentException(HERE) << "Error: expected positive values for the discretization, here discretization[" << i << "]=" << discretization[i];
  discretization_ = discretization;
}

Indices LevelSetMesher::getDiscretization() const
{
  return discretization_;
}

/* Here is the interface that all derived class must implement */

Mesh LevelSetMesher::build(const LevelSet & levelSet,
                           const Bool project) const
{
  const UnsignedInteger dimension(levelSet.getDimension());
  if (discretization_.getSize() != dimension) throw InvalidArgumentException(HERE) << "Error: the mesh factory is for levelSets of dimension=" << discretization_.getSize() << ", here dimension=" << dimension;
  if (dimension > 3) throw NotYetImplementedException(HERE) << "In LevelSetMesher::build(const LevelSet & levelSet, const Bool project) const";
  return build(levelSet, Interval(levelSet.getLowerBound(), levelSet.getUpperBound()), project);
}

Mesh LevelSetMesher::build(const LevelSet & levelSet,
                           const Interval & boundingBox,
                           const Bool project) const
{
  const UnsignedInteger dimension(levelSet.getDimension());
  if (discretization_.getSize() != dimension) throw InvalidArgumentException(HERE) << "Error: the mesh factory is for levelSets of dimension=" << discretization_.getSize() << ", here dimension=" << dimension;
  if (dimension > 3) throw NotYetImplementedException(HERE) << "In LevelSetMesher::build(const LevelSet & levelSet, const Interval & boundingBox, const Bool project) const";

  // First, mesh the bounding box
  const Mesh boundingMesh(IntervalMesher(discretization_).build(boundingBox));
  NumericalSample boundingVertices(boundingMesh.getVertices());
  const UnsignedInteger numVertices = boundingVertices.getSize();
  const Mesh::IndicesCollection boundingSimplices(boundingMesh.getSimplices());
  const UnsignedInteger numSimplices = boundingSimplices.getSize();
  // Second, keep only the simplices with a majority of vertices in the level set
  const NumericalMathFunction function(levelSet.getFunction());
  NumericalSample values(function(boundingVertices));
  const NumericalScalar level = levelSet.getLevel();
  Mesh::IndicesCollection goodSimplices(0);
  NumericalSample goodVertices(0, dimension);
  // Flags for the vertices to keep
  Indices flagGoodVertices(numVertices, 0);
  // Vertices that have moved
  NumericalSample movedVertices(0, dimension);
  // Flag for the vertices that have moved
  Indices flagMovedVertices(0);
  // Prepare the optimization problem for the projection
  NumericalMathFunction shiftFunction;
  OptimizationProblem problem;
  if (project)
  {
    Matrix linear(dimension, 2 * dimension);
    for (UnsignedInteger i = 0; i < dimension; ++i)
    {
      linear(i, i) = 1.0;
      linear(i, dimension + i) = 1.0;
    }
    LinearNumericalMathFunction shiftFunctionBase(NumericalPoint(2 * dimension), NumericalPoint(dimension), linear);
    Indices parameters(dimension);
    parameters.fill();
    shiftFunction = NumericalMathFunction(shiftFunctionBase, parameters, NumericalPoint(dimension));
    problem.setLevelValue(level);
  } // project
  for (UnsignedInteger i = 0; i < numSimplices; ++i)
  {
    const Indices currentSimplex(boundingSimplices[i]);
    UnsignedInteger numGood = 0;
    // Count the vertices in the level set
    for (UnsignedInteger j = 0; j <= dimension; ++j)
    {
      const UnsignedInteger globalVertexIndex(currentSimplex[j]);
      if (values[globalVertexIndex][0] <= level)
      {
        ++numGood;
        ++flagGoodVertices[globalVertexIndex];
      }
    }
    // If enough vertices, keep the simplex and flag all the vertices
    if (numGood > 0)
    {
      goodSimplices.add(currentSimplex);
      // Check if we have to move some vertices
      if (numGood <= dimension)
      {
        NumericalSample localVertices(dimension + 1, dimension);
        NumericalPoint localValues(dimension + 1, dimension);
        for (UnsignedInteger j = 0; j <= dimension; ++j)
        {
          const UnsignedInteger index(currentSimplex[j]);
          localVertices[j] = boundingVertices[index];
          localValues[j] = values[index][0];
        }
        NumericalPoint center(dimension);
        NumericalScalar centerValue = 0.0;
        // First pass: compute the center of the good points
        for (UnsignedInteger j = 0; j <= dimension; ++j)
          if (localValues[j] <= level)
          {
            center += localVertices[j];
            centerValue += localValues[j];
          }
        center /= numGood;
        centerValue /= numGood;
        // Second pass, move the vertices that are outside of the level set
        // using a linear interpolation between the center and the vertex
        for (UnsignedInteger j = 0; j <= dimension; ++j)
        {
          const UnsignedInteger globalVertexIndex(currentSimplex[j]);
          // If the vertex has to be moved
          if ((flagGoodVertices[globalVertexIndex] == 0) && (localValues[j] > level))
          {
            // C(v*) [inside], M(level) [on], B(v) [outside]
            // (M-C)/(B-C) = (level-v*)/(v-v*) = a
            // M-B=(v-level)/(v-v*)(C-B)
            const NumericalPoint currentVertex(boundingVertices[globalVertexIndex]);
            const NumericalPoint delta((center - currentVertex) * (localValues[j] - centerValue) / (localValues[j] - centerValue));
            // If no projection, just add the linear correction
            flagMovedVertices.add(globalVertexIndex);
            if (!project) movedVertices.add(currentVertex + delta);
            else
            {
              // Project the vertices not in the level set on the boundary of the level set
              // Build the optimization problem argmin ||x - x_0||^2 such that level - f(x) >= 0, where x_0 is the current vertex
              shiftFunction.setParameter(currentVertex);
              NumericalMathFunction levelFunction(function, shiftFunction);
              problem.setLevelFunction(levelFunction);
              solver_.setStartingPoint(delta);
              // Here we have to catch exceptions raised by the gradient
              try
              {
                solver_.run();
              }
              catch(...)
              {
                // Here we may have to fix the gradient eg in the case of analytical functions, when Ev3 does not handle the expression.
                const NumericalScalar epsilon(ResourceMap::GetAsNumericalScalar("CenteredFiniteDifferenceGradient-DefaultEpsilon"));
                levelFunction.setGradient(CenteredFiniteDifferenceGradient((localVertices.getMin() - localVertices.getMax()) * epsilon + NumericalPoint(dimension, epsilon), levelFunction.getEvaluation()).clone());
                problem.setLevelFunction(levelFunction);
                solver_.setProblem(problem);
                solver_.run();
              }
              movedVertices.add(currentVertex + solver_.getResult().getOptimalPoint());
            } // project
            ++flagGoodVertices[globalVertexIndex];
          } // localValue[j] > level
        } // j = 0; j <= dimension; ++j
      } // numGood <= dimension
    } // numGood > 0
  } // i < numSimplices
  // Insert the vertices that have moved
  for (UnsignedInteger i = 0; i < flagMovedVertices.getSize(); ++i)
    boundingVertices[flagMovedVertices[i]] = movedVertices[i];
  // Extract the vertices to keep and reuse the flag to store vertices
  // indices shifts
  for (UnsignedInteger i = 0; i < numVertices; ++i)
  {
    if (flagGoodVertices[i] > 0) goodVertices.add(boundingVertices[i]);
    flagGoodVertices[i] = i + 1 - goodVertices.getSize();
  }
  // Shift the vertices indices into the good simplices
  for (UnsignedInteger i = 0; i < goodSimplices.getSize(); ++i)
    for (UnsignedInteger j = 0; j <= dimension; ++j)
      goodSimplices[i][j] -= flagGoodVertices[goodSimplices[i][j]];
  return Mesh(goodVertices, goodSimplices);
}

END_NAMESPACE_OPENTURNS

