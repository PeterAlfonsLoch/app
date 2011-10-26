#pragma once


class CLASS_DECL_ca not_supported_exception : 
   public interface_only_exception
{
public:
   
   
   not_supported_exception(const not_supported_exception & e);
   not_supported_exception(const char * pszTip = NULL);
   virtual ~not_supported_exception();


};
