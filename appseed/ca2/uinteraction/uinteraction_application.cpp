#include "framework.h"


namespace uinteraction
{

   application::application()
   {
   }

   application::~application()
   {
   }

   bool application::find_uinteractions_from_cache(::string_to_string_map & map)
   {

      if(directrix().m_varTopicQuery.has_property("install"))
         return true;

      ex1::filesp file;
      
      try
      {

         file = get_file(System.dir().appdata("uinteractionlib.bin"), ex1::file::type_binary | ex1::file::mode_read);

      }
      catch(...)
      {

         return false;

      }

      ex1::byte_input_stream is(file);

      is >> map;

      return true;

   }

   bool application::find_uinteractions_to_cache(::string_to_string_map & map)
   {

/*      m_spfilehandler(new ::ca2::filehandler::handler(this));*/

      map.remove_all();

      string strLibraryId;
      stringa straTitle;

      Application.dir().ls_pattern(System.dir().ca2module(), "app_core_uinteraction_*", NULL,& straTitle);

      for(int i = 0; i < straTitle.get_count(); i++)
      {
         strLibraryId = straTitle[i];
         gen::str::ends_eat_ci(strLibraryId, ".dll");
         gen::str::ends_eat_ci(strLibraryId, ".so");
         map_uinteraction_library(map, strLibraryId);
      }

      map_uinteraction_library(map, "app_core_uinteraction");

      ex1::filesp file;

      file = get_file(System.dir().appdata("uinteractionlib.bin"), ex1::file::defer_create_directory | ::ex1::file::type_binary | ex1::file::mode_create  | ::ex1::file::mode_write);

      ex1::byte_output_stream os(file);

      os << map;

      return true;

   }

   bool application::map_uinteraction_library(::string_to_string_map & map, const char * pszLibrary)
   {

      ::ca2::library library;

      if(!library.open(this, pszLibrary))
         return false;


      stringa stra;
      string strUinteraction;

      library.get_uinteraction_list(stra);

      for(int i = 0; i < stra.get_count(); i++)
      {
         strUinteraction = stra[i];
         map.set_at(strUinteraction, pszLibrary);
      }

      if(stra.get_count() <= 0)
         return false;

      return true;

   }

   ::uinteraction::interaction * application::get_new_uinteraction(const char * pszUinteraction)
   {


      if(pszUinteraction == NULL || pszUinteraction == '\0')
         pszUinteraction = "core";


      if(!System.directrix().m_varTopicQuery.has_property("install")
      && !System.directrix().m_varTopicQuery.has_property("uninstall")
      && !System.install().is("uinteraction", pszUinteraction))
      {

         if(::IsDebuggerPresent())
         {

            MessageBox(NULL, "Starting installation of uinteraction \"" + string(pszUinteraction) + "\"", "Starting Installation - ca2", MB_OK);

         }

         hotplugin::host::starter_start(": app=session session_start=" + string(pszUinteraction) + " app_type=uinteraction install", NULL);

         return NULL;

      }

      ca2::library library;

      string strLibrary = Bergedge.m_mapUInteractionToLibrary[pszUinteraction];

      if(strLibrary.is_empty())
         return NULL;

      ::uinteraction::interaction * pinteraction = NULL;
      if(!library.open(get_app(), strLibrary, false))
         return NULL;

      stringa stra;

      library.get_app_list(stra);

      if(stra.get_size() != 1) // a uinteraction OSLibrary should have one application
         return NULL;

      string strAppId(stra[0]);

      if(strAppId.is_empty()) // trivial validity check
         return NULL;



      pinteraction = library.get_new_uinteraction(pszUinteraction);
      if(pinteraction == NULL)
         return NULL;

      return pinteraction;

   }

   ::uinteraction::interaction * application::get_uinteraction(const char * pszUinteraction)
   {
      
      ::uinteraction::interaction * pinteraction = Bergedge.m_mapUInteraction[pszUinteraction];
      
      if(Bergedge.m_mapUInteraction[pszUinteraction] == NULL)
      {
         
         Bergedge.m_mapUInteraction[pszUinteraction] = Bergedge.get_new_uinteraction(pszUinteraction);

         pinteraction = Bergedge.m_mapUInteraction[pszUinteraction];

      }

      return pinteraction;


   }


   ::uinteraction::frame::frame * application::get_frame_schema(const char * pszLibrary, const char * pszFrameSchemaName)
   {

      ::uinteraction::interaction * pinteraction = get_uinteraction(pszLibrary);

      if(pinteraction == NULL)
         return NULL;


      return pinteraction->get_frame_schema(pszFrameSchemaName);

   }

} // namespace uinteraction