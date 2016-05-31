#pragma once


#include "datetime_value.h"


namespace datetime
{



   CLASS_DECL_AURA string to_string(::aura::application * pbaseapp,::aura::str_context * pcontext,const ::datetime::value & value);


   CLASS_DECL_AURA value span_strtotime(::aura::application * pbaseapp,::aura::str_context * pcontext,const char * psz);
   CLASS_DECL_AURA value strtotime(::aura::application * pbaseapp,::aura::str_context * pcontext,const char * psz,int32_t & iPath,int32_t & iPathCount,bool bForceUTC = false);






} // namespace datetime


extern "C" CLASS_DECL_AURA time_t timegm(struct tm *tmp);




#include "datetime_department.h"