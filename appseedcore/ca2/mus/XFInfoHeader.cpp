#include "StdAfx.h"
#include "vmsmusresource.h"

XFInfoHeader::XFInfoHeader()
{

}

XFInfoHeader::~XFInfoHeader()
{

}

void XFInfoHeader::FromData(string &wstrData)
{
   string strToken;

   stringa stra;
   PcreUtil::add_tokens(stra, wstrData, "/(.*)(((\\\\?~1):)|$)/", 1);
   stra.replace("\\:", ":");

   m_id       = stra[0];
   m_strDate     = stra[1];
   m_strCountry  = stra[2];
   m_strCategory = stra[3];
   m_strBeat              = stra[4];
   m_strMelodyInstrument  = stra[5];
   m_strVocalType         = stra[6];
   strToken               = stra[7];
   m_straComposer.remove_all();
   PcreUtil::add_tokens(m_straComposer, strToken, "/(([^/]|(/{2}))+)((/(/?!))|$)/", 1);
   m_straComposer.replace("//", "/");

   //m_straComposer.add_tokens(strToken, L"/", FALSE);

   m_straLyricist.remove_all();
   m_straLyricist.add_tokens(stra[8], "/", FALSE);

   m_straArranger.remove_all();
   m_straArranger.add_tokens(stra[9], "/", FALSE);

   m_straPerformer.remove_all();
   PcreUtil::add_tokens(m_straPerformer, stra[10], "/(([^/]|(/{2}))+)((/(?!/))|$)/", 1);
   m_straPerformer.replace("//", "/");
   //m_straPerformer.add_tokens(strToken, L"/", FALSE);

   m_straProgrammer.remove_all();
   m_straProgrammer.add_tokens(stra[11], "/", FALSE);

   m_straKeyword.remove_all();
   if(stra.get_size() > 12)
   {
      m_straKeyword.add_tokens(stra[12], "/", FALSE);
   }

}

void XFInfoHeader::ToData(string &str)
{
   string l_str;
   str.Empty();
//   str += "XFhd";
//   str += L":";
   str += m_id;
   str += L":";
   str += m_strDate;
   str += L":";
   str += m_strCountry;
   str += L":";
   str += m_strCategory;
   str += L":";
   str += m_strBeat;
   str += L":";
   str += m_strMelodyInstrument;
   str += L":";
   str += m_strVocalType;
   str += L":";
    
   m_straComposer.get_format_string(l_str, "/");
   str += l_str;
   str += L":";

   m_straLyricist.get_format_string(l_str, "/");
   str += l_str;
   str += L":";

   m_straArranger.get_format_string(l_str, "/");
   str += l_str;
   str += L":";

   m_straPerformer.get_format_string(l_str, "/");
   str += l_str;
   str += L":";

   m_straProgrammer.get_format_string(l_str, "/");
   str += l_str;
   str += L":";

   m_straKeyword.get_format_string(l_str, "/");
   str += l_str;
}

void XFInfoHeader::FromKarHeader(SoftKaraokeInfo *pInfo)
{
   m_straComposer.remove_all();
   m_straLyricist.remove_all();
   m_straArranger.remove_all();
   m_straPerformer.remove_all();
   m_straProgrammer.remove_all();

   string str;
   string wstrAuthor;
   string wstrCopyright;
   gen::international::OemToUtf8(wstrAuthor, pInfo->m_strAuthor);
   gen::international::OemToUtf8(wstrCopyright, pInfo->m_strCopyright);
   wstrAuthor.replace("/", "//");
   wstrCopyright.replace("/", "//");
   wstrAuthor.replace(":", "\\:");
   wstrCopyright.replace(":", "\\:");
   str =  wstrAuthor + "/" + wstrCopyright;

   PcreUtil::add_tokens(m_straComposer,   str, "/(([^/]|(/{2}))+)((/(/?!))|$)/", 1);
   PcreUtil::add_tokens(m_straLyricist,   str, "/(([^/]|(/{2}))+)((/(/?!))|$)/", 1);
   PcreUtil::add_tokens(m_straArranger,   str, "/(([^/]|(/{2}))+)((/(/?!))|$)/", 1);
   PcreUtil::add_tokens(m_straPerformer,  str, "/(([^/]|(/{2}))+)((/(/?!))|$)/", 1);
   PcreUtil::add_tokens(m_straProgrammer, str, "/(([^/]|(/{2}))+)((/(/?!))|$)/", 1);

}

void XFInfoHeader::FromTune1000Header(CTune1000Info *pInfo)
{
   m_straComposer.remove_all();
   m_straLyricist.remove_all();
   m_straArranger.remove_all();
   m_straPerformer.remove_all();
   m_straProgrammer.remove_all();

   string str;

   pInfo->m_straOther.get_format_string(str, "/");

   m_straComposer.add_tokens(str, "/", FALSE);
   m_straLyricist.add_tokens("", "/", FALSE);
   m_straArranger.add_tokens("", "/", FALSE);
   m_straPerformer.add_tokens("", "/", FALSE);
   m_straProgrammer.add_tokens("", "/", FALSE);

}

bool XFInfoHeader::get_data(char * lpsz, int nCount)
{
   string str;
   ToData(str);
   return gen::international::utf8_to_multibyte(gen::international::CodePageLatin1, lpsz, nCount, str);
   
}

int XFInfoHeader::GetDataCount()
{
   string str;
   ToData(str);
   string strDst;
   return gen::international::utf8_to_multibyte(gen::international::CodePageLatin1, strDst, str);
}

void XFInfoHeader::FromData(LPBYTE *lpData, DWORD cbData)
{
   string str;
   gen::international::utf8_to_multibyte(gen::international::CodePageLatin1, str, (const char *) lpData, cbData);
   FromData(str);
}

bool XFInfoHeader::is_empty()
{
   return m_id.is_empty() &&
      m_strDate.is_empty() &&
      m_strCountry.is_empty() &&
      m_strCategory.is_empty() &&
      m_strBeat.is_empty() &&
      m_strMelodyInstrument.is_empty() &&
      m_strVocalType.is_empty() &&
      m_straComposer.get_size() == 0 &&
      m_straLyricist.get_size() == 0 &&
      m_straArranger.get_size() == 0 &&
      m_straPerformer.get_size() == 0 &&
      m_straProgrammer.get_size() == 0 &&
      m_straKeyword.get_size() == 0;

}

void XFInfoHeader::Empty()
{
   m_id.Empty();
   m_strDate.Empty();
   m_strCountry.Empty();
   m_strCategory.Empty();
   m_strBeat.Empty();
   m_strMelodyInstrument.Empty();
   m_strVocalType.Empty();
   m_straComposer.remove_all();
   m_straLyricist.remove_all();
   m_straArranger.remove_all();
   m_straPerformer.remove_all();
   m_straProgrammer.remove_all();
   m_straKeyword.remove_all();
}

XFInfoHeader & XFInfoHeader::operator =(XFInfoHeader &xfih)
{
   m_id                     = xfih.m_id ;
   m_strDate               = xfih.m_strDate;
   m_strCountry            = xfih.m_strCountry;
   m_strCategory            = xfih.m_strCategory;
   m_strBeat               = xfih.m_strBeat;
   m_strMelodyInstrument   = xfih.m_strMelodyInstrument;
   m_strVocalType            = xfih.m_strVocalType;
   m_straComposer          = xfih.m_straComposer;
   m_straLyricist          = xfih.m_straLyricist;
   m_straArranger          = xfih.m_straArranger;
   m_straPerformer         = xfih.m_straPerformer;
   m_straProgrammer        = xfih.m_straProgrammer;
   m_straKeyword           = xfih.m_straKeyword;
   return *this;
}

void XFInfoHeader::SetID(const wchar_t * lpszID)
{
   m_id = lpszID;
}

void XFInfoHeader::Prepare()
{
   m_strDate.trim_left();
   m_strDate.trim_right();
   m_strCountry.trim_left();
   m_strCountry.trim_right();
   m_strCategory.trim_left();
   m_strCategory.trim_right();
   m_strBeat.trim_left();
   m_strBeat.trim_right();
   m_strMelodyInstrument.trim_left();
   m_strMelodyInstrument.trim_right();
   m_strVocalType.trim_left();
   m_strVocalType.trim_right();
   m_straComposer.trim_left();
   m_straComposer.trim_right();
   m_straLyricist.trim_left();
   m_straLyricist.trim_right();
   m_straArranger.trim_left();
   m_straArranger.trim_right();
   m_straPerformer.trim_left();
   m_straPerformer.trim_right();
   m_straProgrammer.trim_left();
   m_straProgrammer.trim_right();
   m_straKeyword.trim_left();
   m_straKeyword.trim_right();


}

bool XFInfoHeader::GetFormatV001(const wchar_t * lpcszName, string & rwstr)
{
   UNREFERENCED_PARAMETER(lpcszName);
   UNREFERENCED_PARAMETER(rwstr);
   throw not_implemented_exception();
/*    string str;
    string wstrLoad;
    string wstrFormat;

    str = lpcszName;
    m_straComposer.get_format_string(wstrFormat, "/");
    if(!wstrFormat.is_empty())
    {
        str += L"   ";
        wstrLoad.Format(IDS_FORMAT001_COMPOSER, wstrFormat);
        str += wstrLoad;
    }
    m_straLyricist.get_format_string(wstrFormat, "/");
    if(!wstrFormat.is_empty())
    {
        str += L"   ";
        wstrLoad.Format(IDS_FORMAT001_LYRICIST, wstrFormat);
        str += wstrLoad;
    }
    m_straArranger.get_format_string(wstrFormat, "/");
    if(!wstrFormat.is_empty())
    {
        str += L"   ";
        wstrLoad.Format(IDS_FORMAT001_ARRANGER, wstrFormat);
        str += wstrLoad;
    }
    m_straPerformer.get_format_string(wstrFormat, "/");
    if(!wstrFormat.is_empty())
    {
        str += L"   ";
        wstrLoad.Format(IDS_FORMAT001_PERFORMER, wstrFormat);
        str += wstrLoad;
    }
    m_straProgrammer.get_format_string(wstrFormat, "/");
    if(!wstrFormat.is_empty())
    {
        str += L"   ";
        wstrLoad.Format(IDS_FORMAT001_PROGRAMMER, wstrFormat);
        str += wstrLoad;
    }
    rwstr = str;*/
    return true;   
}
