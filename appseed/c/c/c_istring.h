#pragma once


class CLASS_DECL_c istring
{
protected:


   sp(::application)  m_papp;
   string               m_str;
   string               m_strTemplate;


public:


   istring(sp(::application) papp);
   ~istring();


   istring & operator = (const char * psz);


   inline operator const char * () { return m_str; }
   inline operator const char * () const { return m_str; }


   void update_string();

};



