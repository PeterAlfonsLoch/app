#include "framework.h"


namespace xml
{


   input_tree::input_tree(sp(::aura::application) papp) :
      element(papp),
      tree_base(papp)
   {
      m_pdocument = NULL;
      m_pnode = NULL;
   }

   input_tree::input_tree(sp(::aura::application) papp, tree_schema * pschema) :
      element(papp),
      tree_base(papp, pschema)
   {
      m_pdocument = NULL;
      m_pnode = NULL;
   }

   input_tree::~input_tree()
   {

   }

   node * input_tree::import_node(const char * lpcszName, importable & importable)
   {
      node * pnodePrev = m_pnode;
      if(m_pnode == NULL)
      {
         m_pnode = m_pdocument->get_root();
         string strName;
         strName = m_pnode->get_name();
         if(strName != lpcszName)
         {
            m_pnode = NULL;
            throw "Node not found";
         }
         importable.xml_import(*this);
         return m_pdocument->get_root();
      }
      else
      {
         node * pnode = m_pnode->get_child(lpcszName);
         m_pnode = pnode;
         importable.xml_import(*this);
         m_pnode = pnodePrev;
         return pnode;
      }
   }


   node * input_tree::import_node(const char * lpcszName, attr_array & attributea, importable & importable)
   {
      node * pnodePrev = m_pnode;
      if(m_pnode == NULL)
      {
         m_pnode = m_pdocument->get_root();
         if(m_pnode->get_name() != lpcszName)
         {
            ASSERT(FALSE);
            m_pnode = NULL;
            throw "Node not found";
         }
         if(!m_pnode->contains(attributea))
            return ((node *) NULL);
         importable.xml_import(*this);
         return m_pdocument->get_root();
      }
      else
      {
         node * pnode = m_pnode->child_at(m_pnode->find(lpcszName, attributea));
         m_pnode = pnode;
         importable.xml_import(*this);
         m_pnode = pnodePrev;
         return pnode;
      }
   }



   bool input_tree::get_attr(const char * lpcszName, string & strValue)
   {
      return m_pnode->get_attr(lpcszName, strValue);
   }


   bool input_tree::get_attr(const char * lpcszName, int32_t & iValue)
   {
      return m_pnode->get_attr(lpcszName, iValue);
   }


   void input_tree::get_value(string & strValue)
   {
      strValue = m_pnode->get_value();
   }


   node * input_tree::import_node(const char * lpcszName, var & var)
   {
      m_varexchange.m_pvar = &var;
      return import_node(lpcszName, m_varexchange);
   }


} // namespace xml


