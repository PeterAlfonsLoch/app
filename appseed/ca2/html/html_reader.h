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

      virtual void BeginParse(dword_ptr dwAppData, bool &bAbort);
      virtual void StartTag(lite_html_tag *pTag, dword_ptr dwAppData, bool &bAbort);
      virtual void EndTag(lite_html_tag *pTag, dword_ptr dwAppData, bool &bAbort);
      virtual void Characters(const string &rText, dword_ptr dwAppData, bool &bAbort);
      virtual void Comment(const string &rComment, dword_ptr dwAppData, bool &bAbort);
      virtual void EndParse(dword_ptr dwAppData, bool bIsAborted);

      tag * detach_main_tag();

   };


} // namespace html


