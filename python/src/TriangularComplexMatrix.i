// SWIG file TriangularComplexMatrix.i

%{
#include "openturns/TriangularComplexMatrix.hxx"
%}

%include TriangularComplexMatrix_doc.i

%include openturns/TriangularComplexMatrix.hxx

namespace OT { 

%extend TriangularComplexMatrix {

  TriangularComplexMatrix(const TriangularComplexMatrix & other) { return new OT::TriangularComplexMatrix(other); }

  TriangularComplexMatrix(PyObject * pyObj) { return new OT::TriangularComplexMatrix( OT::convert<OT::_PySequence_,OT::TriangularComplexMatrix>(pyObj) ); }

  OTComplexMatrixGetAccessors()

  TriangularComplexMatrix __rmul__(NumericalComplex s) { return s * (*self); }
  ComplexMatrix __rmul__(const ComplexMatrix & m) { return m * (*self); }

#if SWIG_VERSION < 0x030011
  TriangularComplexMatrix __truediv__(NumericalComplex s) { return (*self) / s; }
#endif

  } // TriangularComplexMatrix
} // OT
