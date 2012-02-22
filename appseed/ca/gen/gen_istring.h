#pragma once


class CLASS_DECL_ca istring
{
protected:


   ::ca::application *  m_papp;
   string               m_str;
   string               m_strTemplate;


public:

      
   istring(::ca::application * papp);
   ~istring();


   inline istring & operator = (const char * psz);


   inline operator const char * () { return m_str; }
   inline operator const char * () const { return m_str; }


   void update_string();

};

