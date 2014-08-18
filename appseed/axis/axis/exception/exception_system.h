// Common/Exception.h
// from 7-zip on 2012-12-23, dawn
#pragma once

class CLASS_DECL_AXIS system_exception :
   virtual public simple_exception
{
public:
   HRESULT ErrorCode;
   system_exception(sp(::axis::application) papp, HRESULT errorCode) :
      element(papp),
      ::call_stack(papp),
      ::exception::axis(papp),
      ::simple_exception(papp),
      ErrorCode(errorCode)
   {
         printf(":system");
   }
};
