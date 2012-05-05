#include "StdAfx.h"


namespace ca2
{


   namespace filehandler
   {


      handler::handler(::ca::application * papp) :
         ca(papp)
      {

         m_sptree(new tree_interface(papp));

         m_sptree->initialize();

      }

      handler::~handler()
      {
      }

      void handler::defer_add_library(::ca2::library * plibrary)
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

         for(int i = 0; i < straExtension.get_count(); i++)
         {
            ::ex1::tree_item * pitem = get_extension_tree_item(straExtension[i], true);
            if(pitem == NULL)
               continue;
            dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straHandlerLibrary.add(plibrary->m_strCa2Name);
            plibrary->get_extension_app(dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straApp, straExtension[i]);
         }

         stringa straMimeType;
         
         plibrary->get_mime_type_list(straMimeType);

         for(int i = 0; i < straMimeType.get_count(); i++)
         {
            ::ex1::tree_item * pitem = get_extension_tree_item(straMimeType[i], true);
            if(pitem == NULL)
               continue;
            dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straHandlerLibrary.add(plibrary->m_strCa2Name);
            plibrary->get_mime_type_app(dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straApp, straMimeType[i]);
         }

      }

      void handler::add_menu_library(menu_library * plibrary)
      {

         stringa straExtension;

         plibrary->get_extension_list(straExtension);

         for(int i = 0; i < straExtension.get_count(); i++)
         {
            ::ex1::tree_item * pitem = get_extension_tree_item(straExtension[i], true);
            if(pitem == NULL)
               continue;
            dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straMenuLibrary.add(plibrary->m_strCa2Name);
            plibrary->get_extension_app(dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straApp, straExtension[i]);
         }

         stringa straMimeType;
         
         plibrary->get_mime_type_list(straMimeType);

         for(int i = 0; i < straMimeType.get_count(); i++)
         {
            ::ex1::tree_item * pitem = get_mime_type_tree_item(straMimeType[i], true);
            if(pitem == NULL)
               continue;
            dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straMenuLibrary.add(plibrary->m_strCa2Name);
            plibrary->get_mime_type_app(dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straApp, straMimeType[i]);
         }

      }

      ::ex1::tree_item * handler::get_extension_tree_item(const char * pszExtension, bool bCreate)
      {

         ex1::tree_item * pitem = m_sptree->get_base_item()->get_next();

         if(strcmp(pszExtension, "*") == 0)
         {

            while(pitem != NULL)
            {
               if(dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_etopictype == tree_item::topic_type_root)
                  return pitem;
               pitem = pitem->get_next(false);
            }

            if(!bCreate)
               return NULL;

            pitem = m_sptree->create_item(m_sptree->get_base_item(), ex1::RelativeLastChild);

            dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_etopictype      = tree_item::topic_type_root;

         }
         else
         {

            while(pitem != NULL)
            {
               if(dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_etopictype == tree_item::topic_type_extension
               && dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_strTopic.CompareNoCase(pszExtension) == 0)
                  return pitem;
               pitem = pitem->get_next(false);
            }

            if(!bCreate)
               return NULL;

            pitem = m_sptree->create_item(m_sptree->get_base_item(), ex1::RelativeLastChild);

            dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_etopictype      = tree_item::topic_type_extension;
            dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_strTopic        = pszExtension;

         }

         return pitem;

      }


      ::ex1::tree_item * handler::get_mime_type_tree_item(const char * pszMimeType, bool bCreate)
      {

         ex1::tree_item * pitem = m_sptree->get_base_item()->get_next();

         while(pitem != NULL)
         {
            if(dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_etopictype == tree_item::topic_type_mime_type
            && dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_strTopic.CompareNoCase(pszMimeType) == 0)
               return pitem;
            pitem = pitem->get_next(false);
         }

         if(!bCreate)
            return NULL;

         pitem = m_sptree->create_item(m_sptree->get_base_item(), ex1::RelativeLastChild);

         dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_etopictype      = tree_item::topic_type_mime_type;
         dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_strTopic        = pszMimeType;

         return pitem;

      }


      void handler::get_extension_app(stringa & straAppId, const char * pszExtension)
      {

         ::ex1::tree_item * pitem = get_extension_tree_item(pszExtension, false);
         if(pitem == NULL)
            return;
         straAppId.add(dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straApp);

      }

      void handler::get_mime_type_app(stringa & straAppId, const char * pszMimeType)
      {

         ::ex1::tree_item * pitem = get_mime_type_tree_item(pszMimeType, false);
         if(pitem == NULL)
            return;
         straAppId.add(dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straApp);

      }

      void handler::write(::ex1::byte_output_stream & ostream)
      {
         ::ex1::tree_item * pitem = m_sptree->get_base_item();

         index iLevel = 0;

         while(true)
         {
            pitem = pitem->get_next(true, true, &iLevel);
            if(pitem == NULL)
               break;
            ostream << (int) iLevel;
            ostream << (int) dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_etopictype;
            ostream << dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_strTopic;
            ostream << dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straApp;
         }

         ostream << (int) -1;

      }

      void handler::read(::ex1::byte_input_stream & istream)
      {

         ::ex1::tree_item * pitem = m_sptree->get_base_item();

         int iPreviousLevel = 0;
         int iLevel = 0;

         while(true)
         {
            iPreviousLevel = iLevel;
            istream >> iLevel;
            if(iLevel < 0)
               break;
            if(iLevel == iPreviousLevel)
               pitem = m_sptree->create_item(pitem, ex1::RelativeLastSibling);
            else if(iLevel > iPreviousLevel)
               pitem = m_sptree->create_item(pitem, ex1::RelativeFirstChild);
            else
            {
               while(iLevel < iPreviousLevel)
               {
                  pitem = pitem->m_pparent;
                  iPreviousLevel--;
               }
               pitem = m_sptree->create_item(pitem, ex1::RelativeLastSibling);
            }

            istream >> (int &) dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_etopictype;
            istream >> dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_strTopic;
            istream >> dynamic_cast < tree_item * > (pitem->m_pitemdata)->m_straApp;
         }


      }


   
   } // namespace filehandler


} // namespace ca2


