// Common/Exception.h
// from 7-zip on 2012-12-23, dawn
#pragma once

namespace ca
{

   class CLASS_DECL_ca2 system_exception :
      virtual public simple_exception
   {
   public:
      HRESULT ErrorCode;
      system_exception(sp(::ca::application) papp, HRESULT errorCode) :
         ca(papp),
         ::call_stack(papp),
         ::base_exception(papp),
         ::simple_exception(papp),
         ErrorCode(errorCode) 
      {
      }
   };

} // namespace ca
