#pragma once


namespace uinteraction
{


   class CLASS_DECL_ca2 uinteraction :
      virtual public ::ca::section
   {
   public:


      uinteraction();
      virtual ~uinteraction();


      virtual ::uinteraction::interaction * get_new_uinteraction(const char * pszUinteractionLibrary);
      virtual ::uinteraction::interaction * get_uinteraction(const char * pszUinteractionLibrary);
      virtual ::uinteraction::frame::frame * get_frame_schema(const char * pszUinteractionLibrary, const char * pszFrameSchemaName);

   };


} // namespace uinteraction





