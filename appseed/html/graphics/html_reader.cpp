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

   void reader::BeginParse(uint_ptr dwAppData, bool &bAbort)
   {
      UNREFERENCED_PARAMETER(dwAppData);
      m_ptag = NULL;
      m_ptagMain = NULL;
      bAbort = false;
   }

   void reader::StartTag(lite_html_tag *pTag, uint_ptr dwAppData, bool &bAbort)
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
      
      string strTagName = pTag->getTagName();
      
      m_ptag->set_name(strTagName);

      if(pTag->getAttributes() != NULL)
      {
         for(int32_t i = 0; i < pTag->getAttributes()->getCount(); i++)
         {
             m_ptag->attra().add(canew(attribute()));
            attribute * pattr = m_ptag->attra().last_sp();
            pattr->set_name(pTag->getAttributes()->getAttribute(i).getName().make_lower());
            pattr->set_value(pTag->getAttributes()->getAttribute(i).getValue());
         }
      }
      if(m_ptag->GetParent() != NULL && pTag->getTagName() == "visual")
      {
         m_ptag = m_ptag->GetParent();
      }
      bAbort = false;
   }

   void reader::EndTag(lite_html_tag *pTag, uint_ptr dwAppData, bool &bAbort)
   {
      UNREFERENCED_PARAMETER(pTag);
      UNREFERENCED_PARAMETER(dwAppData);
      if(m_ptag->GetParent() != NULL && pTag->getTagName() != "visual")
      {
         m_ptag = m_ptag->GetParent();
      }

      bAbort = false;
   }

   void reader::Characters(const string &rText, uint_ptr dwAppData, bool &bAbort)
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

   void reader::Comment(const string &rComment, uint_ptr dwAppData, bool &bAbort)
   {
      UNREFERENCED_PARAMETER(rComment);
      UNREFERENCED_PARAMETER(dwAppData);
      bAbort = false;
   }

   void reader::EndParse(uint_ptr dwAppData, bool bIsAborted)
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



