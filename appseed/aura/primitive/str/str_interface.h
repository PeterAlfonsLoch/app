#pragma once


//#ifdef LINUX
//#undef __USE_MISC
//#include <strings.h>
//#endif


class string;
class istring;


class CLASS_DECL_AURA string_interface :
   virtual public root
{
public:


   // the string returned by get_string should be valid
   // during all lifetime of an derived object of
   // string_interface
   virtual strsize get_length() const;

   virtual void get_string(char * psz) const;

   virtual void set_string(const string & str, ::action::context actioncontext);

   string_interface & operator = (const string_interface & str);

   string_interface & operator = (const char * psz);

};
