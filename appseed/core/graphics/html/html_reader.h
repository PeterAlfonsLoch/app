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

      virtual void BeginParse(uint_ptr dwAppData, bool &bAbort);
      virtual void StartTag(lite_html_tag *pTag, uint_ptr dwAppData, bool &bAbort);
      virtual void EndTag(lite_html_tag *pTag, uint_ptr dwAppData, bool &bAbort);
      virtual void Characters(const string &rText, uint_ptr dwAppData, bool &bAbort);
      virtual void Comment(const string &rComment, uint_ptr dwAppData, bool &bAbort);
      virtual void EndParse(uint_ptr dwAppData, bool bIsAborted);

      tag * detach_main_tag();

   };


} // namespace html


