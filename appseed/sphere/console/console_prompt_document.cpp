#include "framework.h"


namespace console
{


   prompt_document::prompt_document(::aura::application * papp) :
      ::object(papp),
      ::data::data_container_base(papp),
      ::aura::document(papp)
   {

   }


   bool prompt_document::on_new_document()
   {

      if(!::aura::document::on_new_document())
		   return FALSE;

      update_all_views(NULL, 0);

	   return TRUE;

   }


   prompt_document::~prompt_document()
   {

   }


 
   #ifdef DEBUG
   void prompt_document::assert_valid() const
   {
      ::aura::document::assert_valid();
   }

   void prompt_document::dump(dump_context & dumpcontext) const
   {
      ::aura::document::dump(dumpcontext);
   }
   #endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // prompt_document serialization

   /*
   void prompt_document::Serialize(CArchive& ar)
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

   void prompt_document::data_on_after_change(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   bool prompt_document::on_open_document(var varFile)
   {
      string str = Application.file().as_string(varFile);
   //  m_prompt_document.load(str);
      
      update_all_views(NULL, 123);

      return TRUE;

   }


} // namespace command



