#pragma once


class CLASS_DECL_ca not_supported_exception : public interface_only_exception
{
public:
   not_supported_exception(const interface_only_exception & e) : interface_only_exception(e) {}
   not_supported_exception(const char * pszTip = NULL) : interface_only_exception(pszTip) {}
   virtual ~not_supported_exception() {};
};
