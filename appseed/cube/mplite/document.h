#pragma once

class PlaylistDoc;

namespace mplite
{
   class pane_view;

   class CLASS_DECL_CA2_CUBE document :
      virtual public ::userbase::document,
      virtual public mediaplay::document 
   {
   public:

      bool           m_bPlay;

      document(::ca::application * papp);
      virtual ~document();
      
      //virtual thread * HelperGetMidiPlayerCallbackThread();
      virtual BOOL on_new_document();
      virtual bool on_open_document(var varFile);
      virtual void delete_contents();

      pane_view * GetPaneView();
      mplite::EPaneView GetViewId();
      void AttachPlaylist(PlaylistDoc * pdoc);
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


      afx_msg BOOL OpenFile(const char * bstrFilePath, BOOL bMakeVisible);
   };

} // namespace mplite