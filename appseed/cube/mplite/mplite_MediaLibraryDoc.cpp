#include "StdAfx.h"
#include "MediaLibraryDoc.h"
#include "mediamanager/AlbumBuild.h"

namespace mplite
{

   MediaLibraryDoc::MediaLibraryDoc(::ca::application * papp) :
      ca(papp),
      data_container(papp),
      ::document(papp),
      ::userbase::document(papp)
   {
   //   m_pdb = NULL;
      m_pdsAlbum1       = NULL;
      m_pcsAlbum1       = NULL;
      m_pdsAlbumRecord  = NULL;
   //   m_bBuilt = false;
   }

   BOOL MediaLibraryDoc::on_new_document()
   {
      if (!::userbase::document::on_new_document())
         return FALSE;

      stringa stra;
      data_get("SongDirectorySet", ::ca::system::idEmpty, stra);

      mediamanager::get(get_app())->BuildAlbum(stra);

      m_pcsAlbum1        = &mediamanager::get(get_app())->GetAlbumBuild().m_csRead1;
      m_pdsAlbum1        = (::sqlite::set *) mediamanager::get(get_app())->GetAlbumBuild().m_pdsRead1;


      update_all_views(NULL, 0);

      return TRUE;
   }

   MediaLibraryDoc::~MediaLibraryDoc()
   {
   }


    // BEGIN_MESSAGE_MAP(MediaLibraryDoc, ::userbase::document)
      //{{AFX_MSG_MAP(MediaLibraryDoc)
         // NOTE - the ClassWizard will add and remove mapping macros here.
      //}}AFX_MSG_MAP
    // END_MESSAGE_MAP()

   /////////////////////////////////////////////////////////////////////////////
   // MediaLibraryDoc diagnostics

   #ifdef _DEBUG
   void MediaLibraryDoc::assert_valid() const
   {
      ::userbase::document::assert_valid();
   }

   void MediaLibraryDoc::dump(dump_context & dumpcontext) const
   {
      ::userbase::document::dump(dumpcontext);
   }
   #endif //_DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // MediaLibraryDoc serialization

   /*
   void MediaLibraryDoc::Serialize(CArchive& ar)
   {
      if (ar.IsStoring())
      {
         // TODO: add storing code here
      }
      else
      {
         // TODO: add loading code here
      }
   }
   */

   /////////////////////////////////////////////////////////////////////////////
   // MediaLibraryDoc commands

   int MediaLibraryDoc::GetSongCount()
   {
      //m_pds->query("select * from album;");
      //return m_pds->num_rows();
      //return m_fileinfo.m_wstraNew.get_size();
      if(m_pcsAlbum1 == NULL)
         return 0;

      CSingleLock sl(m_pcsAlbum1, TRUE);
      if(m_pdsAlbum1 == NULL)
         return 0;
      else
         return m_pdsAlbum1->num_rows();
   }

   void MediaLibraryDoc::data_on_after_change(gen::signal_object * pobj)
   {
      SCAST_PTR(::database::change_event, pchange, pobj);
      if(pchange->m_key.m_idKey == "SongDirectorySet")
      {
         OnSetSongDirectory();
      }
   }

   void MediaLibraryDoc::OnSetSongDirectory()
   {

      stringa stra;
      data_get("SongDirectorySet", ::ca::system::idEmpty, stra);

      mediamanager::get(get_app())->BuildAlbum(stra);

      update_all_views(NULL, 0);

   }

} // namespace mplite