#pragma once


class CLASS_DECL_ca not_supported_exception : 
   virtual public interface_only_exception
{
public:
   
   
   not_supported_exception(const not_supported_exception & e);
   not_supported_exception(::ca::applicationsp papp, const char * pszTip = ::null());
   virtual ~not_supported_exception();


};
