#include "framework.h"


namespace xml
{

   var_exchange::var_exchange(::ca::application * papp) :
      ca(papp)
   {
      m_pvar = ::null();
   }

   var_exchange::~var_exchange()
   {

   }

   void var_exchange::xml_export(class output_tree & xmlot)
   {
      ASSERT(m_pvar != ::null());
      if(m_pvar == ::null())
         return;
      node * pnode = xmlot.m_pnode;
      pnode->add_attr("type", (int32_t)m_pvar->get_type());
      pnode->set_value(m_pvar->get_string());
   }

   void var_exchange::xml_import(class input_tree & xmlit)
   {
      ASSERT(m_pvar != ::null());
      if(m_pvar == ::null())
         return;
      node * pnode = xmlit.m_pnode;
      if(pnode == ::null())
      {
         // property Node not found;
         //ASSERT(FALSE);
         return;
      }
      int32_t i;
      pnode->get_attr("type", i);
      m_pvar->m_etype = (var::e_type) i;
      m_pvar->set_string(pnode->get_value());
   
   }

} // namespace xml