#include "framework.h"


namespace filehandler
{


   handler::handler(sp(base_application) papp) :
      element(papp)
   {

      m_sptree = new tree_interface(papp);

   }

   handler::~handler()
   {
   }

   void handler::defer_add_library(::core::library * plibrary)
   {

      menu_library * pmenulibrary = dynamic_cast < menu_library * > (plibrary);
      if(pmenulibrary != NULL)
      {
         add_menu_library(pmenulibrary);
      }
      else
      {
         library * phandlerlibrary = dynamic_cast < library * > (plibrary);
         if(phandlerlibrary != NULL)
         {
            add_library(phandlerlibrary);
         }
      }

   }

   void handler::add_library(library * plibrary)
   {

      stringa straExtension;

      plibrary->get_extension_list(straExtension);

      for(int32_t i = 0; i < straExtension.get_count(); i++)
      {
         sp(::data::tree_item) pitem = get_extension_tree_item(straExtension[i], true);
         if(pitem == NULL)
            continue;
         pitem->m_pitemdata.cast < tree_item_data > ()->m_straHandlerLibrary.add(plibrary->m_strCa2Name);
         plibrary->get_extension_app(pitem->m_pitemdata.cast < tree_item_data > ()->m_straApp, straExtension[i]);
      }

      stringa straMimeType;
         
      plibrary->get_mime_type_list(straMimeType);

      for(int32_t i = 0; i < straMimeType.get_count(); i++)
      {
         sp(::data::tree_item) pitem = get_extension_tree_item(straMimeType[i], true);
         if(pitem == NULL)
            continue;
         pitem->m_pitemdata.cast < tree_item_data > ()->m_straHandlerLibrary.add(plibrary->m_strCa2Name);
         plibrary->get_mime_type_app(pitem->m_pitemdata.cast < tree_item_data > ()->m_straApp, straMimeType[i]);
      }

   }

   void handler::add_menu_library(menu_library * plibrary)
   {

      stringa straExtension;

      plibrary->get_extension_list(straExtension);

      for(int32_t i = 0; i < straExtension.get_count(); i++)
      {
         sp(::data::tree_item) pitem = get_extension_tree_item(straExtension[i], true);
         if(pitem == NULL)
            continue;
         pitem->m_pitemdata.cast < tree_item_data > ()->m_straMenuLibrary.add(plibrary->m_strCa2Name);
         plibrary->get_extension_app(pitem->m_pitemdata.cast < tree_item_data > ()->m_straApp, straExtension[i]);
      }

      stringa straMimeType;
         
      plibrary->get_mime_type_list(straMimeType);

      for(int32_t i = 0; i < straMimeType.get_count(); i++)
      {
         sp(::data::tree_item) pitem = get_mime_type_tree_item(straMimeType[i], true);
         if(pitem == NULL)
            continue;
         pitem->m_pitemdata.cast < tree_item_data > ()->m_straMenuLibrary.add(plibrary->m_strCa2Name);
         plibrary->get_mime_type_app(pitem->m_pitemdata.cast < tree_item_data > ()->m_straApp, straMimeType[i]);
      }

   }

   sp(::data::tree_item) handler::get_extension_tree_item(const char * pszExtension, bool bCreate)
   {

      sp(::data::tree_item) pitem = m_sptree->get_base_item()->get_next();

      if(strcmp(pszExtension, "*") == 0)
      {

         while(pitem != NULL)
         {
            if(pitem->m_pitemdata.cast < tree_item_data > ()->m_etopictype == tree_item_data::topic_type_root)
               return pitem;
            pitem = pitem->get_next(false);
         }

         if(!bCreate)
            return NULL;

         pitem = m_sptree->create_item(m_sptree->get_filehandler_tree_data(), m_sptree->get_base_item(), ::data::RelativeLastChild);

         pitem->m_pitemdata.cast < tree_item_data > ()->m_etopictype      = tree_item_data::topic_type_root;

      }
      else
      {

         while(pitem != NULL)
         {
            if(dynamic_cast < tree_item_data * > (pitem->m_pitemdata.m_p)->m_etopictype == tree_item_data::topic_type_extension
            && dynamic_cast < tree_item_data * > (pitem->m_pitemdata.m_p)->m_strTopic.CompareNoCase(pszExtension) == 0)
               return pitem;
            pitem = pitem->get_next(false);
         }

         if(!bCreate)
            return NULL;

         pitem = m_sptree->create_item(m_sptree->get_filehandler_tree_data(), m_sptree->get_base_item(), ::data::RelativeLastChild);

         dynamic_cast < tree_item_data * > (pitem->m_pitemdata.m_p)->m_etopictype      = tree_item_data::topic_type_extension;
         dynamic_cast < tree_item_data * > (pitem->m_pitemdata.m_p)->m_strTopic        = pszExtension;

      }

      return pitem;

   }


   sp(::data::tree_item) handler::get_mime_type_tree_item(const char * pszMimeType, bool bCreate)
   {

      sp(::data::tree_item) pitem = m_sptree->get_base_item()->get_next();

      while(pitem != NULL)
      {
         if(dynamic_cast < tree_item_data * > (pitem->m_pitemdata.m_p)->m_etopictype == tree_item_data::topic_type_mime_type
         && dynamic_cast < tree_item_data * > (pitem->m_pitemdata.m_p)->m_strTopic.CompareNoCase(pszMimeType) == 0)
            return pitem;
         pitem = pitem->get_next(false);
      }

      if(!bCreate)
         return NULL;

      pitem = m_sptree->create_item(m_sptree->get_filehandler_tree_data(), m_sptree->get_base_item(), ::data::RelativeLastChild);

      dynamic_cast < tree_item_data * > (pitem->m_pitemdata.m_p)->m_etopictype      = tree_item_data::topic_type_mime_type;
      dynamic_cast < tree_item_data * > (pitem->m_pitemdata.m_p)->m_strTopic        = pszMimeType;

      return pitem;

   }


   void handler::get_extension_app(stringa & straAppId, const char * pszExtension)
   {

      sp(::data::tree_item) pitem = get_extension_tree_item(pszExtension, false);
      if(pitem == NULL)
         return;
      straAppId.add(dynamic_cast < tree_item_data * > (pitem->m_pitemdata.m_p)->m_straApp);

   }

   void handler::get_mime_type_app(stringa & straAppId, const char * pszMimeType)
   {

      sp(::data::tree_item) pitem = get_mime_type_tree_item(pszMimeType, false);
      if(pitem == NULL)
         return;
      straAppId.add(dynamic_cast < tree_item_data * > (pitem->m_pitemdata.m_p)->m_straApp);

   }

   void handler::write(::file::output_stream & ostream)
   {
      sp(::data::tree_item) pitem = m_sptree->get_base_item();

      index iLevel = 0;

      while(true)
      {
         pitem = pitem->get_next(true, true, &iLevel);
         if(pitem == NULL)
            break;
         ostream << (int32_t) iLevel;
         ostream << (int32_t) dynamic_cast < tree_item_data * > (pitem->m_pitemdata.m_p)->m_etopictype;
         ostream << dynamic_cast < tree_item_data * > (pitem->m_pitemdata.m_p)->m_strTopic;
         ostream << dynamic_cast < tree_item_data * > (pitem->m_pitemdata.m_p)->m_straApp;
      }

      ostream << (int32_t) -1;

   }

   void handler::read(::file::input_stream & istream)
   {

      sp(::data::tree_item) pitem = m_sptree->get_base_item();

      int32_t iPreviousLevel = 0;
      int32_t iLevel = 0;

      while(true)
      {
         iPreviousLevel = iLevel;
         istream >> iLevel;
         if(iLevel < 0)
            break;
         if(iLevel == iPreviousLevel)
            pitem = m_sptree->create_item(m_sptree->get_filehandler_tree_data(), pitem, ::data::RelativeLastSibling);
         else if(iLevel > iPreviousLevel)
            pitem = m_sptree->create_item(m_sptree->get_filehandler_tree_data(), pitem, ::data::RelativeFirstChild);
         else
         {
            while(iLevel < iPreviousLevel)
            {
               pitem = pitem->m_pparent;
               iPreviousLevel--;
            }
            pitem = m_sptree->create_item(m_sptree->get_filehandler_tree_data(), pitem, ::data::RelativeLastSibling);
         }

         istream >> (int32_t &) dynamic_cast < tree_item_data * > (pitem->m_pitemdata.m_p)->m_etopictype;
         istream >> dynamic_cast < tree_item_data * > (pitem->m_pitemdata.m_p)->m_strTopic;
         istream >> dynamic_cast < tree_item_data * > (pitem->m_pitemdata.m_p)->m_straApp;
      }


   }


} // namespace filehandler




