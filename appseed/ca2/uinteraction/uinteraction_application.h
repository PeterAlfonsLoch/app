#pragma once


namespace uinteraction
{


   class CLASS_DECL_ca2 application :
      virtual public ::ca2::user::application
   {
   public:


      application();
      virtual ~application();


      virtual ::uinteraction::interaction * get_new_uinteraction(const char * pszUinteraction);
      virtual ::uinteraction::interaction * get_uinteraction(const char * pszUinteraction);
      virtual ::uinteraction::frame::frame * get_frame_schema(const char * pszLibrary, const char * pszFrameSchemaName);

   };


} // namespace uinteraction





