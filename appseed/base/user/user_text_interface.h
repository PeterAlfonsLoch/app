#pragma once


class CLASS_DECL_BASE text_interface :
   virtual public string_interface
{
public:

   virtual void _001GetText(string & str);
   virtual void _001GetSelText(string & str);
   virtual void _001SetText(const char * psz, bool bUser);

   // string_interface < char > interface
   virtual strsize get_length();
   virtual void get_string(char * psz, ::primitive::memory_size len);
   virtual void set_string(const char * psz, bool bUser);

};



