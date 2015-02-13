//#include "framework.h" // from "axis/user/user.h"
//#include "base/user/user.h"


namespace user
{


   copydesk::copydesk(::aura::application * papp) :
      object(papp)
   {
   }

   copydesk::~copydesk()
   {
   }

   int32_t copydesk::get_file_count()
   {

      ::exception::throw_interface_only(get_app());

      return 0;

   }


   void copydesk::get_filea(stringa & stra)
   {

      UNREFERENCED_PARAMETER(stra);
      ::exception::throw_interface_only(get_app());

   }


   void copydesk::set_filea(stringa & stra)
   {

      UNREFERENCED_PARAMETER(stra);
      ::exception::throw_interface_only(get_app());

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
      ::exception::throw_interface_only(get_app());

   }


   string copydesk::get_plain_text()
   {

      ::exception::throw_interface_only(get_app());

      return "";

   }

   bool copydesk::desk_to_dib(::draw2d::dib * pdib)
   {

      UNREFERENCED_PARAMETER(pdib);
      ::exception::throw_interface_only(get_app());

      return false;

   }


} // namespace user


