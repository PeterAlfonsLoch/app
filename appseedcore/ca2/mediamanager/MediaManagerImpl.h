#pragma once

class ::database::id;

namespace mediamanager
{

   class MediaManager;
   class AlbumBuild;
   CLASS_DECL_ca MediaManager * get(::ca::application * papp);

   class CLASS_DECL_ca MediaManager :
      virtual public ::radix::object
   {
   public:
      MediaManager(::ca::application * papp);
      virtual ~MediaManager();

   public:
      void BuildAlbum(stringa & straFolder);
      void KickBuildAlbum();

      
      AlbumBuild & GetAlbumBuild();

      bool Initialize();
      bool Finalize();
      void OnOpenDocumentFile(const char * lpcsz);
      static MediaManager * GetMediaManager(::ca::application * papp);
   protected:
      AlbumBuild * m_palbumbuild;

   };

   class CLASS_DECL_ca mediamanager_container :
      virtual public ::radix::object
   {
   public:
      mediamanager_container();
      virtual ~mediamanager_container();
      virtual MediaManager * get_mediamanager();
      virtual bool initialize_container(::ca::application * papp);
   protected:
      MediaManager * m_pmanager;
   };

} // namespace mediamanager
