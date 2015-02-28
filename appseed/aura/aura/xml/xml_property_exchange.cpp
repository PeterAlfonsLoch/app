//#include "framework.h"

namespace xml
{

   property_set_exchange::property_set_exchange(::aura::application * papp) :
      object(papp)
   {
      m_ppropertyset = NULL;
   }

   property_set_exchange::~property_set_exchange()
   {

   }


   void property_set_exchange::xml_export(class output_tree & xmlot)
   {
      ASSERT(m_ppropertyset != NULL);
      if(m_ppropertyset == NULL)
         return;
      var_exchange varexchange(get_app());
      for(auto property : *m_ppropertyset)
      {
         varexchange.m_pvar = &property.get_value();
         xmlot.export_node(property.name(), varexchange);
      }
   }

   void property_set_exchange::xml_import(class input_tree & xmlit)
   {
      ASSERT(m_ppropertyset != NULL);
      if(m_ppropertyset == NULL)
         return;
      var_exchange varexchange(get_app());
      for(auto property : *m_ppropertyset)
      {
         varexchange.m_pvar = &property.get_value();
         xmlit.import_node(property.name(), varexchange);
      }
   }

} // namespace xml
