


namespace android
{


   copydesk::copydesk(::aura::application * papp) :
      ::object(papp),
      ::user::copydesk(papp)
   {
   }

   copydesk::~copydesk()
   {
   }

   int32_t copydesk::get_file_count()
   {
      return 0;
   }


   void copydesk::get_filea(stringa & stra)
   {

      stra.add("this_file_does_not_exist_please_implement_android_copydesk_get_filea.txt");

   }

   void copydesk::set_filea(stringa & stra)
   {

      throw todo(get_app());

   }



   bool copydesk::initialize()
   {


      if(!::user::copydesk::initialize())
         return false;

      return true;

   }


   bool copydesk::finalize()
   {

      bool bOk;

      bOk = ::user::copydesk::finalize();

//      if(::window_sp::is_set() && ::window_sp::m_p->IsWindow())
      {
  //       bOk = ::window_sp::m_p->DestroyWindow() != FALSE;
      }
    //  else
      {
         bOk = false;
      }

      return bOk;

   }

   void copydesk::set_plain_text(const char * psz)
   {

      throw todo(get_app());


   }


   string copydesk::get_plain_text()
   {

      return "this text was not actually copied please_implement_android_copydesk_get_plain_text";

   }

   bool copydesk::desk_to_dib(::draw2d::dib * pdib)
   {

      throw todo(get_app());

   }


} // namespace linux


