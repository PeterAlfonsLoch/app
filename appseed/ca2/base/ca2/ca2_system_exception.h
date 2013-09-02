// Common/Exception.h
// from 7-zip on 2012-12-23, dawn
#pragma once

namespace ca2
{

   class CLASS_DECL_ca2 system_exception :
      virtual public simple_exception
   {
   public:
      HRESULT ErrorCode;
      system_exception(sp(::application) papp, HRESULT errorCode) :
         element(papp),
         ::call_stack(papp),
         ::exception::base(papp),
         ::simple_exception(papp),
         ErrorCode(errorCode) 
      {
      }
   };

} // namespace ca2
