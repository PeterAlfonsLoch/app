#pragma once

class playlist_document;

namespace musctrl
{

   class CLASS_DECL_ca single_document_template :
      virtual public userbase::single_document_template
   {
   public:
      single_document_template(::ca::application * papp, const char * pszMatter, ::ca::type_info pDocClass, ::ca::type_info pFrameClass, ::ca::type_info pViewClass );
      virtual ~single_document_template();

      playlist_document * m_pActivePlaylistDoc;

      // varFile, bMakeVisible = true, ui * puiParent = NULL, ui * puiAlloc)
      void request(var & varFile, var & varQuery);
      document * OpenDocumentFileNoReserve(var varPathName, bool bMakeVisible = true, ::user::interaction * puiParent = NULL);
      VMSRESULT ReserveSong(stringa & stra, bool bDoPlay, bool bMakeVisible);
      VMSRESULT ReserveSong(int iSongCode, bool bDoPlay, bool bMakeVisible);
      VMSRESULT ReserveSong(var varPath, bool bDoPlay, bool bMakeVisible);
      VMSRESULT ReserveSong(LPINT lpiaSongs, int iSongCount, bool bDoPlay, bool bMakeVisible);


   #ifdef _DEBUG
      virtual void dump(dump_context&) const;
      virtual void assert_valid() const;
   #endif //_DEBUG

   };

} // namespace musctrl
