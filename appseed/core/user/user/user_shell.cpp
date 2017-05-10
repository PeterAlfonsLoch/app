#include "framework.h"
#include "zlib.h"
#include "zutil.h"
#include "aura/compress/zip/zip.h"
#include "aura/compress/compress_gz.h"


#ifdef MACOS

bool macos_get_file_image(::draw2d::dib * pdib, const char * psz);
#elif defined(LINUX)

const char * basecore_get_file_icon_path(const char * pszPath, int iSize);
string linux_get_file_icon_path(string strPath, int iSize)
{

   const char* psz = basecore_get_file_icon_path(strPath, iSize);

   if (psz == NULL)
   {
      return "";
   }

   string str = psz;

   free((void*)psz);

   return str;

}

const char * basecore_get_file_content_type(const char * pszFile);
string linux_get_file_content_type(string strPath)
{

   const char* psz = basecore_get_file_content_type(strPath);

   if (psz == NULL)
   {
      return "";
   }

   string str = psz;

   free((void*)psz);

   return str;

}
#endif


namespace user
{


   namespace shell
   {


      image_key::image_key()
      {

         m_iIcon = 0x80000000;

      }

      image_key_store::image_key_store()
      {

      }

      image_key_store::image_key_store(const image_key & key)
      {

         m_pszPath = strdup(key.m_pszPath);
         m_iIcon = key.m_iIcon;
         m_eattribute = key.m_eattribute;
         m_eicon = key.m_eicon;
         m_pszExtension = strdup(key.m_pszExtension);
         m_pszShellThemePrefix = strdup(key.m_pszShellThemePrefix);

      }


      image_key_store::~image_key_store()
      {

         if (m_pszPath != NULL)
         {

            free(m_pszPath);

         }

         if (m_pszPath != NULL)
         {

            free(m_pszExtension);

         }

         if (m_pszPath != NULL)
         {

            free(m_pszShellThemePrefix);

         }

      }

      void image_key::set_path(const string & strPath, bool bSetExtension)
      {

         m_pszPath = (char *)strPath.c_str();

         set_extension(strPath);

      }


      void image_key::set_extension(const string & strPath)
      {

         index iFind1 = strPath.rfind('/');
         index iFind2 = strPath.rfind('\\');
         index iFind = MAX(iFind1, iFind2) + 1;

         m_pszExtension = (char *)&strPath[strPath.find('.', iFind) + 1];

      }


      shell::shell(::aura::application * papp) :
         object(papp)
      {

         m_pil16 = canew(image_list(papp));
         m_pil16->create(16, 16, 0, 10, 10);
         m_pil48 = canew(image_list(papp));
         m_pil48->create(48, 48, 0, 10, 10);
         m_pil48Hover = canew(image_list(papp));
         m_pil48Hover->create(48, 48, 0, 10, 10);
         m_imagemap.InitHashTable(16384);

      }

      shell::~shell()
      {

      }

      void shell::initialize()
      {

         single_lock sl(m_pmutex, true);

         m_pil16->add_matter("filemanager\\check_off_16.png");
         m_pil16->add_matter("filemanager\\check_on_16.png");
         m_pil48->add_matter("filemanager\\check_off_16.png");
         m_pil48->add_matter("filemanager\\check_on_16.png");
         m_pil48Hover->add_matter("filemanager\\check_off_16.png");
         m_pil48Hover->add_matter("filemanager\\check_on_16.png");

      }


      void shell::open_folder(oswindow oswindow, const string & strFolder)
      {




      }


      void shell::close_folder(const string & strFolder)
      {


      }



   } // namespace shell


} // namespace user



#ifdef WINDOWSEX

#include "user_shell_windows.cpp"

#endif
