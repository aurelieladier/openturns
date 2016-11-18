// SWIG file UserDefinedFactory.i

OTAutodoc(UserDefinedFactory)

%{
#include "openturns/UserDefinedFactory.hxx"
%}

%include UserDefinedFactory_doc.i

%include openturns/UserDefinedFactory.hxx
namespace OT { %extend UserDefinedFactory { UserDefinedFactory(const UserDefinedFactory & other) { return new OT::UserDefinedFactory(other); } } }
