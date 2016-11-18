//                                               -*- C++ -*-
/**
 *  @brief Classification algorithm base type
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

#include "openturns/PersistentObjectFactory.hxx"
#include "openturns/ClassifierImplementation.hxx"
#include "openturns/TBB.hxx"

BEGIN_NAMESPACE_OPENTURNS

CLASSNAMEINIT(ClassifierImplementation);

static const Factory<ClassifierImplementation> Factory_ClassifierImplementation;

/* Default constructor */
ClassifierImplementation::ClassifierImplementation()
  : PersistentObject()
  , inputSample_(0, 0)
  , classes_(0)
  , verbose_(false)
  , isParallel_(ResourceMap::GetAsBool("Classifier-Parallel"))
{
  // Nothing to do
}

/* Default constructor */
ClassifierImplementation::ClassifierImplementation(const NumericalSample & inputSample,
    const Indices & classes)
  : PersistentObject()
  , inputSample_(inputSample)
  , classes_(classes)
  , verbose_(false)
  , isParallel_(ResourceMap::GetAsBool("Classifier-Parallel"))
{
  // Nothing to do
}

ClassifierImplementation * ClassifierImplementation::clone() const
{
  return new ClassifierImplementation(*this);
}


/* Classify a sample */
UnsignedInteger ClassifierImplementation::classify(const NumericalPoint & inP) const
{
  throw NotYetImplementedException(HERE) << "In ClassifierImplementation::classify(const NumericalPoint & inP) const";
}

/* Classify a sample */
struct ClassifyPolicy
{
  const NumericalSample & input_;
  Indices & output_;
  const ClassifierImplementation * p_classifier_;

  ClassifyPolicy( const NumericalSample & input,
                  Indices & output,
                  const ClassifierImplementation * p_classifier)
    : input_(input)
    , output_(output)
    , p_classifier_(p_classifier)
  {}

  inline void operator()( const TBB::BlockedRange<UnsignedInteger> & r ) const
  {
    for (UnsignedInteger i = r.begin(); i != r.end(); ++ i) output_[i] = p_classifier_->classify(input_[i]);
  }

}; /* end struct ClassifyPolicy */


Indices ClassifierImplementation::classifyParallel(const NumericalSample & inS) const
{
  const UnsignedInteger size = inS.getSize();
  Indices result(size);
  const ClassifyPolicy policy(inS, result, this);
  TBB::ParallelFor(0, size, policy);
  return result;
}

Indices ClassifierImplementation::classifySequential(const NumericalSample & inS) const
{
  const UnsignedInteger size = inS.getSize();
  Indices prediction(size);
  for (UnsignedInteger i = 0; i < size; ++ i)
    prediction[i] = classify(inS[i]);
  return prediction;
}

Indices ClassifierImplementation::classify(const NumericalSample & inS) const
{
  if (isParallel_)
    return classifyParallel(inS);
  return classifySequential(inS);
}

/* Grade a point */
NumericalScalar ClassifierImplementation::grade(const NumericalPoint & inP, const UnsignedInteger hClass) const
{
  throw NotYetImplementedException(HERE) << "In ClassifierImplementation::grade(const NumericalPoint & inP, const UnsignedInteger hClass) const";
}

/* Grade a sample */
struct GradePolicy
{
  const NumericalSample & input_;
  const Indices & classes_;
  NumericalPoint & output_;
  const ClassifierImplementation * p_classifier_;

  GradePolicy( const NumericalSample & input,
               const Indices & classes,
               NumericalPoint & output,
               const ClassifierImplementation * p_classifier)
    : input_(input)
    , classes_(classes)
    , output_(output)
    , p_classifier_(p_classifier)
  {}

  inline void operator()( const TBB::BlockedRange<UnsignedInteger> & r ) const
  {
    for (UnsignedInteger i = r.begin(); i != r.end(); ++ i) output_[i] = p_classifier_->grade(input_[i], classes_[i]);
  }

}; /* end struct GradePolicy */


/* Grade a sample */
NumericalPoint ClassifierImplementation::gradeParallel(const NumericalSample & inS,
    const Indices & hClass) const
{
  const UnsignedInteger size = inS.getSize();
  NumericalPoint result(size);
  const GradePolicy policy(inS, hClass, result, this);
  TBB::ParallelFor(0, size, policy);
  return result;
}

NumericalPoint ClassifierImplementation::gradeSequential(const NumericalSample & inS,
    const Indices & hClass) const
{
  const UnsignedInteger size = inS.getSize();
  NumericalPoint grades(size);
  for ( UnsignedInteger i = 0; i < size; ++ i )
    grades[i] = grade(inS[i], hClass[i]);
  return grades;
}

NumericalPoint ClassifierImplementation::grade(const NumericalSample & inS, const Indices & hClass) const
{
  const UnsignedInteger size = inS.getSize();
  if ( size != hClass.getSize() )
    throw InvalidDimensionException(HERE) << "Input sample dimension (=" << size << ") and classes dimension (=" << hClass.getSize() << ") do not match.";
  if (isParallel_)
    return gradeParallel(inS, hClass);
  return gradeSequential(inS, hClass);
}

/** Parallelization flag accessor */
void ClassifierImplementation::setParallel(const Bool flag)
{
  isParallel_ = flag;
}

Bool ClassifierImplementation::isParallel() const
{
  return isParallel_;
}

/* String converter */
String ClassifierImplementation::__repr__() const
{
  return OSS(true) << "class=" << getClassName()
         << " x=" << inputSample_
         << " y=" << classes_
         << " verbose=" << verbose_ ;
}


String ClassifierImplementation::__str__(const String & offset) const
{
  return __repr__();
}

/* Verbosity accessor */
void ClassifierImplementation::setVerbose(const Bool verbose)
{
  verbose_ = verbose;
}

Bool ClassifierImplementation::getVerbose() const
{
  return verbose_;
}

/* Input space dimension accessor */
UnsignedInteger ClassifierImplementation::getDimension() const
{
  return inputSample_.getDimension();
}

/* Method save() stores the object through the StorageManager */
void ClassifierImplementation::save(Advocate & adv) const
{
  PersistentObject::save(adv);
  adv.saveAttribute( "inputSample_", inputSample_ );
  adv.saveAttribute( "classes_", classes_ );
  adv.saveAttribute( "verbose_", verbose_ );
}


/* Method load() reloads the object from the StorageManager */
void ClassifierImplementation::load(Advocate & adv)
{
  PersistentObject::load(adv);
  adv.loadAttribute( "inputSample_", inputSample_ );
  adv.loadAttribute( "classes_", classes_ );
  adv.loadAttribute( "verbose_", verbose_ );
}


END_NAMESPACE_OPENTURNS

