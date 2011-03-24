#pragma once

namespace  mediamanager
{

   class AlbumBuild;

   class AlbumBuildWnd : 
      public ::user::interaction
   {
   public:
      AlbumBuild *         m_palbumbuild;
      ::user::interaction *     m_hwndCallback;
      bool                 m_b1123;

      int                  m_iTransactionTrigger;
      int                  m_iFieldIndexTitle;
      int                  m_iFieldIndexArtist;
      int                  m_iFieldIndexFileName;

      int                  m_iPreBuildStep;

      AlbumBuildWnd(::ca::application * papp);
      virtual ~AlbumBuildWnd();

      void KillBuild();
      void Initialize(AlbumBuild * palbumbuild);
      AlbumBuild * GetAlbumBuild();
      void KickBuild();
      using ::user::interaction::create;
      bool create();

      DECL_GEN_SIGNAL(_001OnTimer)
   };

} // namespace mediamanager
