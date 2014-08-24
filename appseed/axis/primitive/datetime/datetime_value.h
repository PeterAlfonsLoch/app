#pragma once


namespace datetime
{


   CLASS_DECL_AXIS string to_string(sp(::aura::application) pbaseapp,::user::str_context * pcontext,::datetime::value & value);


   CLASS_DECL_AXIS value span_strtotime(sp(::aura::application) pbaseapp,::user::str_context * pcontext,const char * psz);
   CLASS_DECL_AXIS value strtotime(sp(::aura::application) pbaseapp,::user::str_context * pcontext,const char * psz,int32_t & iPath,int32_t & iPathCount,bool bForceUTC = false);



} // namespace datetime




