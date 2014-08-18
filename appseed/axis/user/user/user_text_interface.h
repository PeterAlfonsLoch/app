#pragma once


class CLASS_DECL_AXIS text_interface :
   virtual public string_interface
{
public:

   virtual void _001GetText(string & str) const;
   virtual void _001GetSelText(string & str) const;
   virtual void _001SetText(const string & str, ::action::context actioncontext);

   // string_interface < char > interface
   virtual strsize get_length() const;
   using string_interface::get_string;
   virtual void get_string(char * psz, ::primitive::memory_size len) const;
   virtual void set_string(const string & str, ::action::context actioncontext);

};



