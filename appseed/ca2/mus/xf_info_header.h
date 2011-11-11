#pragma once

class CLASS_DECL_ca XFInfoHeader  
{
public:
   bool GetFormatV001(const wchar_t * lpcszName, string & rwstr);
   void Prepare();
   void SetID(const wchar_t * lpszID = L"XFhd");
   XFInfoHeader();
   virtual ~XFInfoHeader();

   
   void Empty();
   bool is_empty();
   void FromData(LPBYTE * lpData, DWORD cbData);
   bool get_data(char * lpsz, int nCount);
   int GetDataCount();
   void FromKarHeader(SoftKaraokeInfo *pInfo);
    void FromTune1000Header(CTune1000Info *pInfo);
   void ToData(string &str);
   void FromData(string &wstrData);
   XFInfoHeader & operator =(XFInfoHeader &xfih);

   string         m_id;
   string         m_strDate;
   string         m_strCountry;
   string         m_strCategory;
   string         m_strBeat;
   string         m_strMelodyInstrument;
   string         m_strVocalType;
   stringa      m_straComposer;
   stringa      m_straLyricist;
   stringa      m_straArranger;
   stringa      m_straPerformer;
   stringa      m_straProgrammer;
   stringa      m_straKeyword;

};
