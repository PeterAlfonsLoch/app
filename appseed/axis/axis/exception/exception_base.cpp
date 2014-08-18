#include "framework.h"


namespace exception
{


   axis::axis(sp(::axis::application) papp, uint32_t uiSkip) :
      element(papp),
      ::call_stack(papp, uiSkip)
   {
      // most exceptions are deleted when not needed
      m_ulFlags |= flag_auto_clean;
      m_ulFlags &= ~flag_ready_for_delete;
   }

   axis::axis(sp(::axis::application) papp, bool bAutoDelete, uint32_t uiSkip) :
      element(papp),
      ::call_stack(papp, uiSkip)
   {
      // for exceptions which are not auto-delete (usually)
      if(bAutoDelete)
      {
         m_ulFlags |= flag_auto_clean;
      }
      else
      {
         m_ulFlags &= ~flag_auto_clean;
      }
      m_ulFlags &= ~flag_ready_for_delete;
   }

   axis::~axis()
   {
   }

   void axis::Delete()
   {
      // delete exception if it is auto-deleting
      if(is_set_ca_flag(flag_auto_clean))
      {
         m_ulFlags |= flag_ready_for_delete;
         delete this;
      }
   }


   bool axis::get_error_message(string & str, PUINT pnHelpContext)
   {

      if (pnHelpContext != NULL)
         *pnHelpContext = 0;

      str.Empty();

      return false;

   }

   string axis::get_message(PUINT pnHelpContext)
   {

      string str;

      if(!get_error_message(str, pnHelpContext))
         return "";

      return str;

   }





   int32_t axis::ReportError(UINT nType /* = MB_OK */, const char * pszMessageId /* = NULL */)
   {
      string   strErrorMessage;
      int32_t     nDisposition;
      UINT    nHelpContext;

      // nHelpContext should come with the message "<helpcontext id=\"123\" />"

      if (get_error_message(strErrorMessage, &nHelpContext))
         nDisposition = Application.simple_message_box(NULL, strErrorMessage, nType);
      else
      {
         if (pszMessageId == 0)
            //pszMessageId = __IDP_NO_ERROR_AVAILABLE;
               pszMessageId = "Error message not available";
         nDisposition = Application.simple_message_box(NULL, pszMessageId, nType);
      }
      return nDisposition;
   }


   const char * axis::getMessage() const throw()
   {

      return what();

   }



   void axis::operator delete(void * pbData)
   {
      object::operator delete(pbData);
   }

   void axis::operator delete(void * pbData,   const char * /* lpszFileName */, int32_t /* nLine */)
   {
      operator delete(pbData);
   }




} // namespace exception



