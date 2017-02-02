//                                               -*- C++ -*-
/**
 *  @file  HMatrixParameters.cxx
 *  @brief This file supplies support for HMat
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
 */
#include "openturns/PersistentObjectFactory.hxx"
#include "openturns/HMatrixParameters.hxx"


BEGIN_NAMESPACE_OPENTURNS

CLASSNAMEINIT(HMatrixParameters);

static const Factory<HMatrixParameters> Factory_HMatrixParameters;


HMatrixParameters::HMatrixParameters()
  : PersistentObject()
  , assemblyEpsilon_(ResourceMap::GetAsNumericalScalar("HMatrix-AssemblyEpsilon"))
  , recompressionEpsilon_(ResourceMap::GetAsNumericalScalar("HMatrix-RecompressionEpsilon"))
  , admissibilityFactor_(ResourceMap::GetAsNumericalScalar("HMatrix-AdmissibilityFactor"))
  , clusteringAlgorithm_(ResourceMap::Get("HMatrix-ClusteringAlgorithm"))
{
  // Convert numerical value into a string
  const UnsignedInteger resourceCompressionMethod = ResourceMap::GetAsUnsignedInteger("HMatrix-CompressionMethod");
  switch(resourceCompressionMethod)
  {
  case 0:
    compressionMethod_ = "SVD";
    break;
  case 1:
    compressionMethod_ = "ACA full";
    break;
  case 2:
    compressionMethod_ = "ACA partial";
    break;
  case 3:
    compressionMethod_ = "ACA+";
    break;
  default:
    throw InvalidArgumentException(HERE) << "Unknown compression method: " << resourceCompressionMethod << ", valid choices are: 0 (SVD), 1 (ACA full), 2 (ACA partial) or 3 (ACA+)";
    break;
  }
}

/* Virtual constructor */
HMatrixParameters * HMatrixParameters::clone() const
{
  return new HMatrixParameters(*this);
}

/** accessor for assembly epsilon */
void HMatrixParameters::setAssemblyEpsilon(const NumericalScalar assemblyEpsilon)
{
  assemblyEpsilon_ = assemblyEpsilon;
}

NumericalScalar HMatrixParameters::getAssemblyEpsilon() const
{
  return assemblyEpsilon_;
}

/** accessor for recompression epsilon */
void HMatrixParameters::setRecompressionEpsilon(const NumericalScalar recompressionEpsilon)
{
  recompressionEpsilon_ = recompressionEpsilon;
}

NumericalScalar HMatrixParameters::getRecompressionEpsilon() const
{
  return recompressionEpsilon_;
}

/** accessor for admissibility factor */
void HMatrixParameters::setAdmissibilityFactor(const NumericalScalar admissibilityFactor)
{
  admissibilityFactor_ = admissibilityFactor;
}

NumericalScalar HMatrixParameters::getAdmissibilityFactor() const
{
  return admissibilityFactor_;
}

/** accessor for clustering algorithm */
void HMatrixParameters::setClusteringAlgorithm(const String & clusteringAlgorithm)
{
  clusteringAlgorithm_ = clusteringAlgorithm;
}

String HMatrixParameters::getClusteringAlgorithm() const
{
  return clusteringAlgorithm_;
}

/** accessor for compression method */
void HMatrixParameters::setCompressionMethod(const String & compressionMethod)
{
  compressionMethod_ = compressionMethod;
}

String HMatrixParameters::getCompressionMethod() const
{
  return compressionMethod_;
}

UnsignedInteger HMatrixParameters::getCompressionMethodAsUnsignedInteger() const
{
  if (compressionMethod_ == "SVD")
    return 0;
  else if (compressionMethod_ == "ACA full")
    return 1;
  else if (compressionMethod_ == "ACA partial")
    return 2;
  else if (compressionMethod_ == "ACA+")
    return 3;
  else
    throw InvalidArgumentException(HERE) << "Unknown compression method: " << compressionMethod_ << ", valid choices are: SVD, ACA full, ACA partial or ACA+";
}

/* String converter */
String HMatrixParameters::__repr__() const
{
  OSS oss(true);
  oss << "class= " << HMatrixParameters::GetClassName()
      << ", assembly epsilon= " << assemblyEpsilon_
      << ", recompression epsilon=" << recompressionEpsilon_
      << ", admissibility factor=" << admissibilityFactor_
      << ", clustering algorithm=" << clusteringAlgorithm_
      << ", compression method=" << compressionMethod_;
  return oss;
}

String HMatrixParameters::__str__(const String & offset) const
{
  OSS oss(false);
  oss << offset << "class= " << HMatrixParameters::GetClassName();
  return oss;
}

/* Method save() stores the object through the StorageManager */
void HMatrixParameters::save(Advocate & adv) const
{
  PersistentObject::save(adv);

  adv.saveAttribute("assemblyEpsilon_", assemblyEpsilon_);
  adv.saveAttribute("recompressionEpsilon_", recompressionEpsilon_);
  adv.saveAttribute("admissibilityFactor_", admissibilityFactor_);
  adv.saveAttribute("clusteringAlgorithm_", clusteringAlgorithm_);
  adv.saveAttribute("compressionMethod_", compressionMethod_);
}

/* Method load() reloads the object from the StorageManager */
void HMatrixParameters::load(Advocate & adv)
{
  PersistentObject::load(adv);
  adv.loadAttribute("assemblyEpsilon_", assemblyEpsilon_);
  adv.loadAttribute("recompressionEpsilon_", recompressionEpsilon_);
  adv.loadAttribute("admissibilityFactor_", admissibilityFactor_);
  adv.loadAttribute("clusteringAlgorithm_", clusteringAlgorithm_);
  adv.loadAttribute("compressionMethod_", compressionMethod_);
}

END_NAMESPACE_OPENTURNS
