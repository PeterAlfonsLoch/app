#pragma once

namespace html
{

   class reader : public ::ILiteHTMLReaderEvents
   {
   public:
      reader();

      tag * m_ptagMain;
      tag * m_ptag;

      virtual void BeginParse(DWORD dwAppData, bool &bAbort);
      virtual void StartTag(lite_html_tag *pTag, DWORD dwAppData, bool &bAbort);
      virtual void EndTag(lite_html_tag *pTag, DWORD dwAppData, bool &bAbort);
      virtual void Characters(const string &rText, DWORD dwAppData, bool &bAbort);
      virtual void Comment(const string &rComment, DWORD dwAppData, bool &bAbort);
      virtual void EndParse(DWORD dwAppData, bool bIsAborted);
   };


} // namespace html