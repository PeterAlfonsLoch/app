#include "StdAfx.h"
#include "AlbumBuild.h"


namespace mediamanager
{

   MediaManager::MediaManager(::ca::application * papp) :
      ca(papp)
   {
      TRACE("MediaManager::MediaManager(%d)", this);
      m_palbumbuild = new AlbumBuild(papp);
   }

   MediaManager::~MediaManager()
   {
      if(m_palbumbuild != NULL)
      {
         delete m_palbumbuild;
         m_palbumbuild = NULL;
      }
   }

   MediaManager * MediaManager::GetMediaManager(::ca::application * papp)
   {
      return mediamanager::get(papp);
   }

   mediamanager_container::mediamanager_container()
   {
      m_pmanager = NULL;
   }

   mediamanager_container::~mediamanager_container()
   {
   }

   MediaManager * mediamanager_container::get_mediamanager()
   {
      return m_pmanager;
   }

   bool mediamanager_container::initialize_container(::ca::application * papp)
   {
      m_pmanager = new MediaManager(papp);
      if(m_pmanager == NULL)
         AfxThrowMemoryException();
      return true;
   }

   MediaManager * get(::ca::application * papp)
   {
      return dynamic_cast < mediamanager_container * > (papp)->get_mediamanager();
   }

   bool MediaManager::Initialize()
   {
      GetAlbumBuild().Initialize(NULL);

      TRACE("MediaManager::MediaManager(%d)", this);
      return true;
   }


   bool MediaManager::Finalize()
   {
      return true;
   }

   void MediaManager::OnOpenDocumentFile(const char * lpcsz)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      if(&GetAlbumBuild() == NULL)
         return;
      //if(!GetAlbumBuild().HasFile(lpcsz))
      {
   #ifdef _DEBUG
         string str;
         //      str.Format("File %S is not in the album", lpcsz);
         //System.simple_message_box(str);
   #endif
      }
   }

   void MediaManager::BuildAlbum(stringa & wstraFolder)
   {
      AlbumBuild & albumbuild = GetAlbumBuild();
      albumbuild.m_bBuilt = false;

      albumbuild.KillBuild();

      Initialize();

      albumbuild.m_wstraFolder = wstraFolder;

      albumbuild.KickBuild();
   }

   void MediaManager::KickBuildAlbum()
   {
      GetAlbumBuild().KickBuild();
   }

   AlbumBuild & MediaManager::GetAlbumBuild()
   {
      return *m_palbumbuild;
   }


} // namespace mediamanager


