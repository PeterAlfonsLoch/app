#include "framework.h"

// 0000 -> 7FFF IDR range
// 0000 -> 6FFF : ::fontopus::user resources
// 7000 -> 7FFF : AFX (and standard windows) resources
// IDR ranges (NOTE: IDR_ values must be <32768)
#define ASSERT_VALID_IDR(nIDR) ASSERT((nIDR) != 0 && (nIDR) < 0x8000)

namespace userbase
{

   document_template::document_template(sp(::ca::application) papp, const char * pszMatter, sp(::ca::type_info) pDocClass, sp(::ca::type_info) pFrameClass, sp(::ca::type_info) pViewClass) :
      ::document_template(papp, pszMatter, pDocClass, pFrameClass, pViewClass)
   {
   }

   document_template::~document_template()
   {
   }

#ifdef DEBUG
   void document_template::dump(dump_context & dumpcontext) const
   {
      ::document_template::dump(dumpcontext);
   }

   void document_template::assert_valid() const
   {
      ::document_template::assert_valid();
   }
#endif //DEBUG

} // namespace userbase