#pragma once


class CLASS_DECL_AURA istring
{
protected:


   sp(::aura::application)  m_pauraapp;
   string               m_str;
   string               m_strTemplate;


public:


   istring(sp(::aura::application) papp);
   ~istring();


   istring & operator = (const char * psz);


   inline operator const char * () { return m_str; }
   inline operator const char * () const { return m_str; }


   void update_string();

};



