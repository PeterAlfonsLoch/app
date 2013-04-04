#include "framework.h"


namespace filehandler
{


   handler::handler(::ca::application * papp) :
      ca(papp)
   {

      m_sptree = new tree_interface(papp);

      m_sptree->initialize();

   }

   handler::~handler()
   {
   }

   void handler::defer_add_library(::ca::library * plibrary)
   {

      menu_library * pmenulibrary = dynamic_cast < menu_library * > (plibrary);
      if(pmenulibrary != ::null())
      {
         add_menu_library(pmenulibrary);
      }
      else
      {
         library * phandlerlibrary = dynamic_cast < library * > (plibrary);
         if(phandlerlibrary != ::null())
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
         ::ca::tree_item * pitem = get_extension_tree_item(straExtension[i], true);
         if(pitem == ::null())
            continue;
         dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straHandlerLibrary.add(plibrary->m_strCa2Name);
         plibrary->get_extension_app(dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straApp, straExtension[i]);
      }

      stringa straMimeType;
         
      plibrary->get_mime_type_list(straMimeType);

      for(int32_t i = 0; i < straMimeType.get_count(); i++)
      {
         ::ca::tree_item * pitem = get_extension_tree_item(straMimeType[i], true);
         if(pitem == ::null())
            continue;
         dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straHandlerLibrary.add(plibrary->m_strCa2Name);
         plibrary->get_mime_type_app(dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straApp, straMimeType[i]);
      }

   }

   void handler::add_menu_library(menu_library * plibrary)
   {

      stringa straExtension;

      plibrary->get_extension_list(straExtension);

      for(int32_t i = 0; i < straExtension.get_count(); i++)
      {
         ::ca::tree_item * pitem = get_extension_tree_item(straExtension[i], true);
         if(pitem == ::null())
            continue;
         dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straMenuLibrary.add(plibrary->m_strCa2Name);
         plibrary->get_extension_app(dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straApp, straExtension[i]);
      }

      stringa straMimeType;
         
      plibrary->get_mime_type_list(straMimeType);

      for(int32_t i = 0; i < straMimeType.get_count(); i++)
      {
         ::ca::tree_item * pitem = get_mime_type_tree_item(straMimeType[i], true);
         if(pitem == ::null())
            continue;
         dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straMenuLibrary.add(plibrary->m_strCa2Name);
         plibrary->get_mime_type_app(dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straApp, straMimeType[i]);
      }

   }

   ::ca::tree_item * handler::get_extension_tree_item(const char * pszExtension, bool bCreate)
   {

      ::ca::tree_item * pitem = m_sptree->get_base_item()->get_next();

      if(strcmp(pszExtension, "*") == 0)
      {

         while(pitem != ::null())
         {
            if(dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_etopictype == tree_item::topic_type_root)
               return pitem;
            pitem = pitem->get_next(false);
         }

         if(!bCreate)
            return ::null();

         pitem = m_sptree->create_item(m_sptree->get_base_item(), ::ca::RelativeLastChild);

         dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_etopictype      = tree_item::topic_type_root;

      }
      else
      {

         while(pitem != ::null())
         {
            if(dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_etopictype == tree_item::topic_type_extension
            && dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_strTopic.CompareNoCase(pszExtension) == 0)
               return pitem;
            pitem = pitem->get_next(false);
         }

         if(!bCreate)
            return ::null();

         pitem = m_sptree->create_item(m_sptree->get_base_item(), ::ca::RelativeLastChild);

         dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_etopictype      = tree_item::topic_type_extension;
         dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_strTopic        = pszExtension;

      }

      return pitem;

   }


   ::ca::tree_item * handler::get_mime_type_tree_item(const char * pszMimeType, bool bCreate)
   {

      ::ca::tree_item * pitem = m_sptree->get_base_item()->get_next();

      while(pitem != ::null())
      {
         if(dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_etopictype == tree_item::topic_type_mime_type
         && dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_strTopic.CompareNoCase(pszMimeType) == 0)
            return pitem;
         pitem = pitem->get_next(false);
      }

      if(!bCreate)
         return ::null();

      pitem = m_sptree->create_item(m_sptree->get_base_item(), ::ca::RelativeLastChild);

      dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_etopictype      = tree_item::topic_type_mime_type;
      dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_strTopic        = pszMimeType;

      return pitem;

   }


   void handler::get_extension_app(stringa & straAppId, const char * pszExtension)
   {

      ::ca::tree_item * pitem = get_extension_tree_item(pszExtension, false);
      if(pitem == ::null())
         return;
      straAppId.add(dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straApp);

   }

   void handler::get_mime_type_app(stringa & straAppId, const char * pszMimeType)
   {

      ::ca::tree_item * pitem = get_mime_type_tree_item(pszMimeType, false);
      if(pitem == ::null())
         return;
      straAppId.add(dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straApp);

   }

   void handler::write(::ca::byte_output_stream & ostream)
   {
      ::ca::tree_item * pitem = m_sptree->get_base_item();

      index iLevel = 0;

      while(true)
      {
         pitem = pitem->get_next(true, true, &iLevel);
         if(pitem == ::null())
            break;
         ostream << (int32_t) iLevel;
         ostream << (int32_t) dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_etopictype;
         ostream << dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_strTopic;
         ostream << dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straApp;
      }

      ostream << (int32_t) -1;

   }

   void handler::read(::ca::byte_input_stream & istream)
   {

      ::ca::tree_item * pitem = m_sptree->get_base_item();

      int32_t iPreviousLevel = 0;
      int32_t iLevel = 0;

      while(true)
      {
         iPreviousLevel = iLevel;
         istream >> iLevel;
         if(iLevel < 0)
            break;
         if(iLevel == iPreviousLevel)
            pitem = m_sptree->create_item(pitem, ::ca::RelativeLastSibling);
         else if(iLevel > iPreviousLevel)
            pitem = m_sptree->create_item(pitem, ::ca::RelativeFirstChild);
         else
         {
            while(iLevel < iPreviousLevel)
            {
               pitem = pitem->m_pparent;
               iPreviousLevel--;
            }
            pitem = m_sptree->create_item(pitem, ::ca::RelativeLastSibling);
         }

         istream >> (int32_t &) dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_etopictype;
         istream >> dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_strTopic;
         istream >> dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straApp;
      }


   }


} // namespace filehandler




