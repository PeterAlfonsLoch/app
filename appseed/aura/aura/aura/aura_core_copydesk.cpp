#include "framework.h"


namespace aura
{


   copydesk::copydesk(sp(::aura::application) papp) :
      element(papp)
   {
   }

   copydesk::~copydesk()
   {
   }

   int32_t copydesk::get_file_count()
   {

      throw interface_only_exception(get_app());

   }


   void copydesk::get_filea(stringa & stra)
   {

      UNREFERENCED_PARAMETER(stra);
      throw interface_only_exception(get_app());

   }


   void copydesk::set_filea(stringa & stra)
   {

      UNREFERENCED_PARAMETER(stra);
      throw interface_only_exception(get_app());

   }



   bool copydesk::initialize()
   {

      return true;

   }

   bool copydesk::finalize()
   {

      return true;

   }

   void copydesk::set_plain_text(const char * psz)
   {

      UNREFERENCED_PARAMETER(psz);
      throw interface_only_exception(get_app());

   }


   string copydesk::get_plain_text()
   {

      throw interface_only_exception(get_app());

   }

   bool copydesk::desk_to_dib(::draw2d::dib * pdib)
   {

      UNREFERENCED_PARAMETER(pdib);
      throw interface_only_exception(get_app());

   }


} // namespace core


