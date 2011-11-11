#include "StdAfx.h"


namespace mediaplaylist
{


   central_container::central_container()
   {
      m_pplaylistcentral = NULL;
   }

   central_container::~central_container()
   {
      delete m_pplaylistcentral;
   }

   bool central_container::initialize(::ca::application * papp)
   {
      set_app(papp);
      m_pplaylistcentral = new mediaplaylist::central(papp);
      if(m_pplaylistcentral == NULL)
         return false;
      System.factory().creatable_small < ::mediaplaylist::document >();
      System.factory().creatable_small < ::mediaplaylist::frame >();
      System.factory().creatable_small < ::mediaplaylist::list_view >();
      System.factory().creatable_small < ::mediaplaylist::tree_view >();
      System.factory().creatable_small < ::mediaplaylist::view >();
      return true;
   }


   mediaplaylist::callback_interface * central_container::GetNewPlaylistCallback()
   {
      return NULL;
   }


   mediaplaylist::central & central_container::GetPlaylistCentral()
   {
      return *m_pplaylistcentral;
   }

   central_container & central_container::AppGetPlaylistAppInterface(::ca::application * papp)
   {
      return *(dynamic_cast < central_container * > (papp));
   }

   mediaplaylist::central & central_container::AppGetPlaylistCentral(::ca::application * papp)
   {
      return AppGetPlaylistAppInterface(papp).GetPlaylistCentral();
   }


} // namespace mediaplaylist

