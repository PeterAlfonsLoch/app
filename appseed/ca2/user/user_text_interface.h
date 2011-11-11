#pragma once


class CLASS_DECL_ca text_interface :
   virtual public string_interface
{
public:
   virtual void _001GetText(string & str) const;
   virtual void _001GetSelText(string & str) const;
   virtual void _001SetText(const char * psz);

   // string_interface < char > interface
   virtual int get_length() const;
   virtual void get_string(char * psz) const;
   virtual void set_string(const char * psz);
};
