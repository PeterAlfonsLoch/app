#include "StdAfx.h"

namespace musctrl
{

   PlayerDocContainer::PlayerDocContainer()
   {

   }

   PlayerDocContainer::~PlayerDocContainer()
   {

   }

   ::userbase::document * PlayerDocContainer::GetXfplayerDoc()
   {
      return dynamic_cast < ::userbase::document * > (MusicalPlayerCentralContainer::AppGetMusicalPlayerCentral(m_papp).get_document_template()->get_document(0));
   }

} //namespace musctrl
