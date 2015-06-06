


struct PROCESS_INFO_t
{
    string csProcess;
    uint32_t dwImageListIndex;
};


namespace linux
{


   file_system::file_system(::aura::application *  papp) :
      ::object(papp),
      ::file::system(papp)
   {
   }


   file_system::~file_system()
   {
   }

   bool file_system::update_module_path()
   {

      {

         if(!br_init_lib(NULL))
            return false;

         char * lpszModule = br_find_exe(NULL);

         if(lpszModule == NULL)
            return false;

         m_pathModule = lpszModule;

         free(lpszModule);

      }

      {

         void * handle = dlopen("libaura.so", RTLD_NOW);

         if(handle == NULL)
         {

            m_pathCa2Module = m_pathModule;

         }
         else
         {

            link_map * plm;

            dlinfo(handle, RTLD_DI_LINKMAP, &plm);

            m_pathCa2Module = plm->l_name;

            if(m_pathCa2Module.is_empty() || m_pathCa2Module[0] != '/')
            {

                m_pathCa2Module = m_pathModule;

            }

            dlclose(handle);

         }

      }

		return true;

   }


} // namespace linux






