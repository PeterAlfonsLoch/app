#include "StdAfx.h"

XFInfoHeaderLS::XFInfoHeaderLS()
{

}

XFInfoHeaderLS::~XFInfoHeaderLS()
{

}

void XFInfoHeaderLS::FromData(string &wstrData)
{
   string_tokenizer str(wstrData);
   string strToken;
   if(!str.GetNextToken(m_id, ":"))
      goto End;
   if(!str.GetNextToken(m_strLanguage, ":"))
      goto End;
   m_straComposer.remove_all();
   m_straComposer.add_tokens(strToken, "/", FALSE);

   if(!str.GetNextToken(strToken, ":"))
      goto End;
   m_straLyricist.remove_all();
   m_straLyricist.add_tokens(strToken, "/", FALSE);

   if(!str.GetNextToken(strToken, ":"))
      goto End;
   m_straArranger.remove_all();
   m_straArranger.add_tokens(strToken, "/", FALSE);

   if(!str.GetNextToken(strToken, ":"))
      goto End;
   m_straPerformer.remove_all();
   m_straPerformer.add_tokens(strToken, "/", FALSE);

   if(!str.GetNextToken(strToken, ":"))
      goto End;
   m_straProgrammer.remove_all();
   m_straProgrammer.add_tokens(strToken, "/", FALSE);


End:;

}

void XFInfoHeaderLS::ToData(string &str)
{
   string wstrB;
   str.Empty();
   str += "XFln";
   str += ":";
   str += m_id;
   str += ":";
   str += m_strLanguage;
   str += ":";
   str += m_strSongName;
   str += ":";

   m_straComposer.get_format_string(wstrB, "/");
   str += wstrB;
   str += ":";

   m_straLyricist.get_format_string(wstrB, "/");
   str += wstrB;
   str += ":";

   m_straArranger.get_format_string(wstrB, "/");
   str += wstrB;
   str += ":";

   m_straPerformer.get_format_string(wstrB, "/");
   str += wstrB;
   str += ":";

   m_straProgrammer.get_format_string(wstrB, "/");
   str += wstrB;

}

XFInfoHeaderLS & XFInfoHeaderLS::operator = (const XFInfoHeaderLS & xfihls)
{
   m_id                     = xfihls.m_id ;
   m_strLanguage           = xfihls.m_strLanguage;
   m_strSongName           = xfihls.m_strSongName;
   m_straComposer          = xfihls.m_straComposer;
   m_straLyricist          = xfihls.m_straLyricist;
   m_straArranger          = xfihls.m_straArranger;
   m_straPerformer         = xfihls.m_straPerformer;
   m_straProgrammer        = xfihls.m_straProgrammer;

   return *this;
}

void XFInfoHeaderLS::Empty()
{
   m_id.Empty();
   m_strLanguage.Empty();
   m_strSongName.Empty();
   m_straComposer.remove_all();
   m_straLyricist.remove_all();
   m_straArranger.remove_all();
   m_straPerformer.remove_all();
   m_straProgrammer.remove_all();
}

bool XFInfoHeaderLS::is_empty()
{
   return m_id.is_empty() &&
      m_strLanguage.is_empty() &&
      m_strSongName.is_empty() &&
      m_straComposer.get_size() == 0 &&
      m_straLyricist.get_size() == 0 &&
      m_straArranger.get_size() == 0 &&
      m_straPerformer.get_size() == 0 &&
      m_straProgrammer.get_size() == 0;

}

void XFInfoHeaderLS::Prepare()
{
   m_straComposer.trim();
   m_straLyricist.trim();
   m_straArranger.trim();
   m_straPerformer.trim();
   m_straProgrammer.trim();
}

XFInfoHeaderLS::XFInfoHeaderLS(const XFInfoHeaderLS & xfihls)
{
   operator = (xfihls);
}
