#pragma once


class CLASS_DECL_AXIS istring
{
protected:


   sp(::base::application)  m_pbaseapp;
   string               m_str;
   string               m_strTemplate;


public:


   istring(sp(::base::application) papp);
   ~istring();


   istring & operator = (const char * psz);


   inline operator const char * () { return m_str; }
   inline operator const char * () const { return m_str; }


   void update_string();

};



