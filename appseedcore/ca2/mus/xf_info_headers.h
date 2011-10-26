#pragma once

class CLASS_DECL_ca CXFInfoHeaders  
{
public:
   void Prepare();
   void Empty();
   CXFInfoHeaders();
   virtual ~CXFInfoHeaders();

   string                  m_strSongName;
   XFInfoHeader            m_xfInfoHeader;
   XFInfoHeaderLSArray      m_xfaInfoHeaderLS;
   
};
