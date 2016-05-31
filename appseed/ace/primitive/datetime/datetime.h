#pragma once


#include "datetime_value.h"


namespace datetime
{



   CLASS_DECL_ACE string to_string(::ace::application * pbaseapp,::ace::str_context * pcontext,const ::datetime::value & value);


   CLASS_DECL_ACE value span_strtotime(::ace::application * pbaseapp,::ace::str_context * pcontext,const char * psz);
   CLASS_DECL_ACE value strtotime(::ace::application * pbaseapp,::ace::str_context * pcontext,const char * psz,int32_t & iPath,int32_t & iPathCount,bool bForceUTC = false);






} // namespace datetime


extern "C" CLASS_DECL_ACE time_t timegm(struct tm *tmp);




#include "datetime_department.h"