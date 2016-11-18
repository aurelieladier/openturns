// SWIG file SymmetricTensor.i

%{
#include "openturns/SymmetricTensor.hxx"
%}

%include SymmetricTensor_doc.i

%ignore OT::SymmetricTensor::checkSymmetry;

%apply const NumericalScalarCollection & { const OT::SymmetricTensor::NumericalScalarCollection & };

%include openturns/SymmetricTensor.hxx

%pythoncode %{
def SymmetricTensor___getattribute__(self, name):
    """Implement attribute accesses."""
    if name == '__array_interface__':
        # call the ignored method checkSymmetry
        self.__str__()
    return super(SymmetricTensor, self).__getattribute__(name)
SymmetricTensor.__getattribute__ = SymmetricTensor___getattribute__
%}

namespace OT {

%extend SymmetricTensor {

  SymmetricTensor(const SymmetricTensor & other) { return new OT::SymmetricTensor(other); }

  SymmetricTensor(PyObject * pyObj) { return new OT::SymmetricTensor( OT::convert<OT::_PySequence_,OT::SymmetricTensor>(pyObj) ); }

  OTTensorAccessors(SymmetricTensor, NumericalScalar, _PyFloat_)

} // SymmetricTensor
} // OT
