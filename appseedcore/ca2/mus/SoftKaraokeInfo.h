#pragma once

class CLASS_DECL_ca SoftKaraokeInfo  
{
public:
   SoftKaraokeInfo();
   virtual ~SoftKaraokeInfo();
   bool is_empty();
   void Empty();
   void Prepare();
   string m_strSongName;
   string m_strAuthor;
    string m_strCopyright;
};
