#pragma once


///      USE istring
///         USE istring
///            USE istring
///               USE istring
///      USE istring
///         USE istring
///            USE istring
///               USE istring
///      USE istring
///         USE istring
///            USE istring
///               USE istring
///      USE istring
///         USE istring
///            USE istring
///               USE istring

class CLASS_DECL_ca language_string :
   public ::radix::object
{
public:
   language_string();
   virtual ~language_string();
   string   m_str;
   string   m_id;

   string get(::ca::application * papp);
   void set_text(const char * psz);
   void set_text_id(const char * psz);
};