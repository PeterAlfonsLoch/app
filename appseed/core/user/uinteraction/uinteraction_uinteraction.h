#pragma once


namespace user
{


   namespace uinteraction
   {


      class CLASS_DECL_CORE uinteraction :
         virtual public ::aura::departament
      {
      public:


         uinteraction(sp(::aura::application) papp);
         virtual ~uinteraction();


         virtual sp(::user::uinteraction::interaction) get_new_uinteraction(const char * pszUinteractionLibrary);
         virtual sp(::user::uinteraction::interaction) get_uinteraction(const char * pszUinteractionLibrary);
         virtual sp(frame::frame) get_frame_schema(const char * pszUinteractionLibrary, const char * pszFrameSchemaName);

      };


   } // namespace uinteraction


} // namespace user





