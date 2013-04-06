#include "framework.h"

namespace userbase
{

   multiple_document_template::multiple_document_template(sp(::ca::application) papp, const char * pszMatter, ::ca::type_info pDocClass,
      ::ca::type_info pFrameClass, ::ca::type_info pViewClass) : 
      ca(papp),
      ::document_template(papp, pszMatter, pDocClass, pFrameClass, pViewClass),
      ::userbase::document_template(papp, pszMatter, pDocClass,   pFrameClass, pViewClass),
      ::multiple_document_template(papp, pszMatter, pDocClass,   pFrameClass, pViewClass)
   {

   }

   multiple_document_template::~multiple_document_template()
   {

   }

   void multiple_document_template::reload_template()
   {
      m_strDocStrings = System.matter_as_string(get_app(),m_strMatter, "full_string.txt");
      if(m_strDocStrings.is_empty())
      {
         TRACE1("Warning: no document names in string for template #%s.\n",
            m_strMatter);
      }

   }

#ifdef DEBUG
   void multiple_document_template::dump(dump_context & dumpcontext) const
   {
      ::document_template::dump(dumpcontext);
   }

   void multiple_document_template::assert_valid() const
   {
      ::document_template::assert_valid();
   }
#endif //DEBUG

} // namespace userbase