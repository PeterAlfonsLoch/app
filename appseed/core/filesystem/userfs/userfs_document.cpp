//#include "framework.h"


namespace userfs
{


   document::document(::aura::application * papp) :
      object(papp),
      ::data::data_container_base(papp),
      ::aura::document(papp)
   {

      m_fsset = canew(::fs::set(papp));

      //m_fsset.m_p->m_pcontainerbase = this;

   }

   document::~document()
   {
   }

   void document::assert_valid() const
   {
      ::aura::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::aura::document::dump(dumpcontext);
   }

   bool document::browse(const char * pszFolder, ::action::context actioncontext)
   {

      {
         synch_lock sl(get_fs_data()->data_mutex());
         m_strFolder = pszFolder;
      }

      if(m_straRootPath.is_empty())
      {

         ::file::listing listing;

         get_fs_data()->root_ones(listing);

         {

            synch_lock sl(get_fs_data()->data_mutex());

            m_straRootPath = listing;

         }

      }

      if(strlen(pszFolder) == 0)
      {

         synch_lock sl(get_fs_data()->data_mutex());

         m_straPath = m_straRootPath;

      }
      else
      {

         ::file::listing listing(get_fs_data());
         
         listing.ls(pszFolder);

         {

            synch_lock sl(get_fs_data()->data_mutex());

            m_straPath = listing;

         }

      }

      update_hint uh;

      uh.set_type(update_hint::type_synchronize_path);

      uh.m_strPath = pszFolder;

      uh.m_actioncontext = ::action::source::sync(actioncontext);

      update_all_views(NULL, 0, &uh);

      return true;

   }



} // namespace userfs



