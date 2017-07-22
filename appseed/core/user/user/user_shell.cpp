#include "framework.h"
#include "zlib.h"
#include "zutil.h"
#include "aura/compress/zip/zip.h"
#include "aura/compress/compress_gz.h"


namespace user
{


   namespace shell
   {


      image_key::image_key()
      {

         m_iIcon = 0x80000000;
         m_pszPath = "";
         m_pszShellThemePrefix = "";

      }

      image_key_store::image_key_store()
      {

      }

      image_key_store::image_key_store(const image_key & key)
      {

         m_oswindow = key.m_oswindow;
         m_cr = key.m_cr;
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

         m_iaSize.add(16);
         m_iaSize.add(24);
         m_iaSize.add(32);
         m_iaSize.add(48);
         m_iaSize.add(256);


         for (auto iSize : m_iaSize)
         {

            m_pil[iSize] = canew(image_list(papp));
            m_pil[iSize]->create(iSize, iSize, 0, 10, 10);

            m_pilHover[iSize] = canew(image_list(papp));
            m_pilHover[iSize]->create(iSize, iSize, 0, 10, 10);

         }

         m_imagemap.InitHashTable(16384);

      }

      shell::~shell()
      {

      }

      void shell::initialize()
      {

         do_initialize();

      }

      void shell::do_initialize()
      {


         single_lock sl(m_pmutex, true);

         int iImage;
         for (auto iSize : m_iaSize)
         {
            
            iImage = GetImageList(iSize)->add_matter("filemanager\\check_off_16.png");

            add_hover_image(iSize, iImage, 0);


            iImage = GetImageList(iSize)->add_matter("filemanager\\check_on_16.png");

            add_hover_image(iSize, iImage, 0);
            
         }

      }

      image_list * shell::GetImageList(int iSize)
      {
         
         index i = 0;

         for (; i < m_iaSize.get_size(); i++)
         {

            if (iSize <= m_iaSize[i])
            {

               break;

            }

         }

         if (i >= m_iaSize.get_size())
         {

            i = m_iaSize.get_upper_bound();

         }
         
         return m_pil[m_iaSize[i]];

      }

      
      image_list * shell::GetImageListHover(int iSize)
      {
         index i = 0;

         for (; i < m_iaSize.get_size(); i++)
         {

            if (iSize <= m_iaSize[i])
            {

               break;

            }

         }

         if (i >= m_iaSize.get_size())
         {

            i = m_iaSize.get_upper_bound();

         }

         return m_pilHover[m_iaSize[i]];

      }


      //void shell::open_folder(oswindow oswindow, const string & strFolder)
      //{




      //}


      //void shell::close_folder(const string & strFolder)
      //{


      //}



   } // namespace shell


} // namespace user



