#pragma once

namespace mplite
{

   class CLASS_DECL_CA2_CUBE MediaLibraryDoc :
      public ::userbase::document
   {
   public:
      
      
      ::sqlite::set *         m_pdsAlbum1;
      critical_section *      m_pcsAlbum1;
      ::sqlite::set *         m_pdsAlbumRecord;


      MediaLibraryDoc(::ca::application * papp);
      virtual ~MediaLibraryDoc();
      

      virtual BOOL on_new_document();
      void OnSetSongDirectory();
      int GetSongCount();
      
      DECL_GEN_VSIGNAL(data_on_after_change)

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   };

} // namespace mplite