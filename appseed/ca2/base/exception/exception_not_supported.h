#pragma once


class CLASS_DECL_ca2 not_supported_exception : 
   virtual public interface_only_exception
{
public:
   
   
   not_supported_exception(const not_supported_exception & e);
   not_supported_exception(sp(::ca::application) papp, const char * pszTip = ::null());
   virtual ~not_supported_exception();


};
