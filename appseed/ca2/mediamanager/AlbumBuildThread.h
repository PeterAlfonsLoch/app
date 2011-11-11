#pragma once

namespace  mediamanager
{

   class AlbumBuild;
   class AlbumBuildWnd;

   class CLASS_DECL_ca AlbumBuildThread : 
      public ::radix::thread
   {
   public:

      AlbumBuildWnd  *  m_pwnd;
      AlbumBuild *      m_palbumbuild;
      HANDLE            m_heventSynch;

      AlbumBuildThread(::ca::application * papp);

      void Initialize(AlbumBuild * palbumbuild);

      virtual bool initialize_instance();
      virtual int exit_instance();

      virtual ~AlbumBuildThread();

   };

} // namespace mediamanager
