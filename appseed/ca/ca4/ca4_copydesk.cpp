#include "StdAfx.h"


namespace ca4
{


   copydesk::copydesk(::ca::application * papp) :
      ca(papp)
   {
   }

   copydesk::~copydesk()
   {
   }

   int copydesk::get_file_count()
   {

      throw interface_only_exception();

   }


   void copydesk::get_filea(stringa & stra)
   {

      UNREFERENCED_PARAMETER(stra);
      throw interface_only_exception();

   }


   void copydesk::set_filea(stringa & stra)
   {

      UNREFERENCED_PARAMETER(stra);
      throw interface_only_exception();

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
      throw interface_only_exception();

   }


   string copydesk::get_plain_text()
   {

      throw interface_only_exception();

   }

   bool copydesk::desk_to_dib(::ca::dib * pdib)
   {

      UNREFERENCED_PARAMETER(pdib);
      throw interface_only_exception();

   }


} // namespace ca4


