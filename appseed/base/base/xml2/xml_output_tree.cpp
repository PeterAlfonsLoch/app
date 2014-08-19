#include "framework.h"

namespace xml
{

   output_tree::output_tree(sp(::axis::application) papp) :
      element(papp),
      tree_base(papp)
   {
      m_pdocument = NULL;
      m_pnode = NULL;
   }

   output_tree::output_tree(sp(::axis::application) papp, tree_schema * pschema) :
      element(papp),
      tree_base(papp, pschema)
   {
      m_pdocument = NULL;
      m_pnode = NULL;
   }

   output_tree::~output_tree()
   {
   }

   node * output_tree::export_node(const char * lpcszName, exportable & exportable)
   {
      if(m_pnode == NULL)
      {
         if(m_pdocument == NULL)
         {
            throw "Cannot output to a NULL document";
         }
         m_pnode = m_pdocument->get_root();
         m_pnode->set_name(lpcszName);
         exportable.xml_export(*this);
         return m_pdocument->get_root();
      }
      else
      {
         node * pnodePrev = m_pnode;
         node * pnode = m_pnode->add_child(lpcszName);
         m_pnode = pnode;
         exportable.xml_export(*this);
         m_pnode = pnodePrev;
         return pnode;
      }
   }

   node * output_tree::export_node(exportable & exportable)
   {
      return export_node("", exportable);
   }


   node * output_tree::export_node(const char * lpcszName, var var)
   {
      m_varexchange.m_pvar = &var;
      return export_node(lpcszName, m_varexchange);
   }

   void output_tree::set_attr(const char * lpcszName, const char * lpcszValue)
   {
      m_pnode->set_attr(lpcszName, lpcszValue);
   }

   void output_tree::set_attr(const char * lpcszName, int64_t iValue)
   {
      m_pnode->set_attr(lpcszName, iValue);
   }

   void output_tree::set_value(const char * lpcszValue)
   {
      m_pnode->set_value(lpcszValue);
   }

   void output_tree::SetNodeName(const char * lpcszName)
   {
      m_pnode->set_name(lpcszName);
   }

} // namespace xml