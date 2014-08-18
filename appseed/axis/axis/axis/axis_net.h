#pragma once


CLASS_DECL_AXIS string url_encode_dup(const char * psz);


CLASS_DECL_AXIS string url_decode_dup(const char * psz);
CLASS_DECL_AXIS string url_decode_dup(const char * lpszUrl,strsize iLen);


CLASS_DECL_AXIS bool url_query_get_param_dup(string & strParam,const char * pszKey,const char * pszUrl);










