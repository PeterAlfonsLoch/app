#pragma once


namespace user
{


   namespace wndfrm
   {


      class CLASS_DECL_CORE wndfrm :
         virtual public ::aura::departament
      {
      public:


         wndfrm(sp(::aura::application) papp);
         virtual ~wndfrm();


         virtual sp(::user::wndfrm::interaction) get_new_wndfrm(const char * pszUinteractionLibrary);
         virtual sp(::user::wndfrm::interaction) get_wndfrm(const char * pszUinteractionLibrary);
         virtual sp(frame::frame) get_frame_schema(const char * pszUinteractionLibrary, const char * pszFrameSchemaName);

      };


   } // namespace wndfrm


} // namespace user





