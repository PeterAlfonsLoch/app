#include "framework.h"

namespace xml
{

   property_set_exchange::property_set_exchange(sp(::aura::application) papp) :
      element(papp)
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
      for(int32_t i = 0; i < m_ppropertyset->m_propertya.get_size(); i++)
      {
         property & property = m_ppropertyset->m_propertya[i];
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
      for(int32_t i = 0; i < m_ppropertyset->m_propertya.get_size(); i++)
      {
         property & property = m_ppropertyset->m_propertya[i];
         varexchange.m_pvar = &property.get_value();
         xmlit.import_node(property.name(), varexchange);
      }
   }

} // namespace xml
