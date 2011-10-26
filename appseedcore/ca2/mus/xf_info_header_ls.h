#pragma once

class CLASS_DECL_ca XFInfoHeaderLS  
{
public:
   void Prepare();
   bool is_empty();
   void Empty();
   void ToData(string &str);
   void FromData(string &wstrData);
   XFInfoHeaderLS();
   XFInfoHeaderLS(const XFInfoHeaderLS & xfihls);
   virtual ~XFInfoHeaderLS();
   XFInfoHeaderLS & operator =(const XFInfoHeaderLS & xfihls);

   string      m_id;
   string      m_strLanguage;
   string      m_strSongName;
   stringa   m_straComposer;
   stringa   m_straLyricist;
   stringa   m_straArranger;
   stringa   m_straPerformer;
   stringa   m_straProgrammer;

   

};


class CLASS_DECL_ca XFInfoHeaderLSArray :
   public base_array < XFInfoHeaderLS, const   XFInfoHeaderLS &>
{
public:
};
