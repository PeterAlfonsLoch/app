#pragma once


class CLASS_DECL_ca2 istring
{
protected:


   sp(::ca::application)  m_papp;
   string               m_str;
   string               m_strTemplate;


public:


   istring(sp(::ca::application) papp);
   ~istring();


   istring & operator = (const char * psz);


   inline operator const char * () { return m_str; }
   inline operator const char * () const { return m_str; }


   void update_string();

};

