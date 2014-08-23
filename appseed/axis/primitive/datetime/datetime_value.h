#pragma once


namespace datetime
{


   string to_string(sp(::aura::application) pbaseapp,::user::str_context * pcontext,datetime & value);


   CLASS_DECL_AURA value span_strtotime(sp(::aura::application) pbaseapp,::user::str_context * pcontext,const char * psz);
   CLASS_DECL_AURA value strtotime(sp(::aura::application) pbaseapp,::user::str_context * pcontext,const char * psz,int32_t & iPath,int32_t & iPathCount,bool bForceUTC = false);



} // namespace datetime




