#pragma once


namespace uinteraction
{


   class CLASS_DECL_ca2 application :
      virtual public ::ca2::user::application
   {
   public:


      application();
      virtual ~application();


      // map user interations to library
      virtual bool find_uinteractions_from_cache(::string_to_string_map & map);
      virtual bool find_uinteractions_to_cache(::string_to_string_map & map);
      virtual bool map_uinteraction_library(::string_to_string_map & map, const char * pszLibrary);


      virtual ::uinteraction::interaction * get_new_uinteraction(const char * pszUinteraction);
      virtual ::uinteraction::interaction * get_uinteraction(const char * pszUinteraction);
      virtual ::uinteraction::frame * get_frame_schema(const char * pszLibrary, const char * pszFrameSchemaName);

   };


} // namespace uinteraction





