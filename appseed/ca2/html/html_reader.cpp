#include "framework.h"


namespace html
{


   reader::reader()
   {
      m_ptag = NULL;
      m_ptagMain = NULL;
   }

   reader::~reader()
   {

      if(m_ptagMain != NULL)
      {
         delete m_ptagMain;
      }

      m_ptag      = NULL;
      m_ptagMain  = NULL;

   }

   void reader::BeginParse(dword_ptr dwAppData, bool &bAbort)
   {
      UNREFERENCED_PARAMETER(dwAppData);
      m_ptag = NULL;
      m_ptagMain = NULL;
      bAbort = false;
   }

   void reader::StartTag(lite_html_tag *pTag, dword_ptr dwAppData, bool &bAbort)
   {
      UNREFERENCED_PARAMETER(dwAppData);
      if(m_ptag == NULL)
      {
         m_ptag = new ::html::tag(NULL);
         m_ptagMain = m_ptag;
      }
      else
      {
         ::html::tag * ptag = new ::html::tag(m_ptag);
         m_ptag->baseptra().add(ptag);
         m_ptag = ptag;
      }
      m_ptag->set_name(pTag->getTagName());
      if(pTag->getAttributes() != NULL)
      {
         for(int i = 0; i < pTag->getAttributes()->getCount(); i++)
         {
            attribute * pattr = m_ptag->attra().add_new();
            pattr->set_name(pTag->getAttributes()->getAttribute(i).getName().make_lower());
            pattr->set_value(pTag->getAttributes()->getAttribute(i).getValue());
         }
      }
      if(m_ptag->get_parent() != NULL && pTag->getTagName() == "visual")
      {
         m_ptag = m_ptag->get_parent();
      }
      bAbort = false;
   }

   void reader::EndTag(lite_html_tag *pTag, dword_ptr dwAppData, bool &bAbort)
   {
      UNREFERENCED_PARAMETER(pTag);
      UNREFERENCED_PARAMETER(dwAppData);
      if(m_ptag->get_parent() != NULL && pTag->getTagName() != "visual")
      {
         m_ptag = m_ptag->get_parent();
      }

      bAbort = false;
   }

   void reader::Characters(const string &rText, dword_ptr dwAppData, bool &bAbort)
   {
      UNREFERENCED_PARAMETER(dwAppData);
      if(m_ptag != NULL)
      {
         ::html::value * pvalue = new ::html::value(m_ptag);
         m_ptag->baseptra().add(pvalue);
         pvalue->set_value(rText);
      }
      bAbort = false;
   }

   void reader::Comment(const string &rComment, dword_ptr dwAppData, bool &bAbort)
   {
      UNREFERENCED_PARAMETER(rComment);
      UNREFERENCED_PARAMETER(dwAppData);
      bAbort = false;
   }

   void reader::EndParse(dword_ptr dwAppData, bool bIsAborted)
   {
      UNREFERENCED_PARAMETER(dwAppData);
      UNREFERENCED_PARAMETER(bIsAborted);
   }

   tag * reader::detach_main_tag()
   {

      tag * ptagMain    = m_ptagMain;


      m_ptagMain        = NULL;
      m_ptag            = NULL;


      return ptagMain;

   }


} // namespace html



