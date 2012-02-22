#pragma once


namespace html
{


   class reader : 
      virtual public ::ILiteHTMLReaderEvents
   {
   protected:


      tag *       m_ptagMain;
      tag *       m_ptag;


   public:


      reader();
      virtual ~reader();

      virtual void BeginParse(DWORD_PTR dwAppData, bool &bAbort);
      virtual void StartTag(lite_html_tag *pTag, DWORD_PTR dwAppData, bool &bAbort);
      virtual void EndTag(lite_html_tag *pTag, DWORD_PTR dwAppData, bool &bAbort);
      virtual void Characters(const string &rText, DWORD_PTR dwAppData, bool &bAbort);
      virtual void Comment(const string &rComment, DWORD_PTR dwAppData, bool &bAbort);
      virtual void EndParse(DWORD_PTR dwAppData, bool bIsAborted);

      tag * detach_main_tag();

   };


} // namespace html


