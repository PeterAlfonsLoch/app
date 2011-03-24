#include "StdAfx.h"
#include "document.h"

namespace i2com
{

   document::document(::ca::application * papp) :
      ca(papp),
   ::ca::data_container(papp),
   ::document(papp),
   ::userbase::document(papp),
      form_document(papp),
      html_document(papp),
      mediaplay::document(papp),
      rtprx::document(papp),
      rtptx::document(papp)
   {
   }

   BOOL document::on_new_document()
   {
      if (!::userbase::document::on_new_document())
         return FALSE;
     update_all_views(NULL, 0);

      return TRUE;
   }

   document::~document()
   {
   }



   bool document::on_open_document(var varFile)
   {
      if(gen::str::begins_ci("rtprx://", varFile))
      {
         return rtprx::document::on_open_document(varFile);
      }
      else if(gen::str::begins_ci("rtptx://", varFile))
      {
         return rtptx::document::on_open_document(varFile);
      }
      else
      {
         return html_document::on_open_document(varFile);
      }
   }

   #ifdef _DEBUG
   void document::assert_valid() const
   {
      ::userbase::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::userbase::document::dump(dumpcontext);
   }
   #endif //_DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // document serialization

   /*
   void document::Serialize(CArchive& ar)
   {
      if (ar.IsStoring())
      {
         // TODO: add storing code here
      }
      else
      {
         // TODO: add loading code here
      }
   }
   */

   void document::data_on_after_change(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   /*
   BOOL document::on_open_document(const char * lpszPathName)
   {
      m_strTopic = lpszPathName;
      update_all_views(NULL, 123);
      return TRUE;
   }
   */

   void document::OnBeforeNavigate2(html::data * pdata, const char * lpszUrl, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel)
   {

      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(lpszTargetFrameName);
      UNREFERENCED_PARAMETER(baPostedData);
      UNREFERENCED_PARAMETER(lpszHeaders);

      string strUrl(lpszUrl);
      if(System.url().get_protocol(strUrl) == "i2com")
      {
         m_ppaneview->i2com_open(lpszUrl);
         *pbCancel = TRUE;
      }

      if(!*pbCancel)
      {
         form_document::OnBeforeNavigate2(pdata, lpszUrl, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
      }

   }

} // namespace i2com