//#include "framework.h"


namespace xml
{


   input_tree::input_tree(::aura::application * papp) :
      object(papp),
      tree_base(papp)
   {
      //m_pdocument = NULL;
      //m_node = NULL;
   }

   input_tree::input_tree(::aura::application * papp, tree_schema * pschema) :
      object(papp),
      tree_base(papp, pschema)
   {
      //m_pdocument = NULL;
      //m_node = NULL;
   }

   input_tree::~input_tree()
   {

   }

   node input_tree::import_node(const char * lpcszName, importable & importable)
   {
      node pnodePrev = m_node;
      if(m_node.empty())
      {
         m_node = m_document.root();
         string strName;
         strName = m_node.get_name();
         if(strName != lpcszName)
         {
            m_node = node();
            throw "Node not found";
         }
         importable.xml_import(*this);
         return m_document.root();
      }
      else
      {
         node pnode = m_node.get_child(lpcszName);
         m_node = pnode;
         importable.xml_import(*this);
         m_node = pnodePrev;
         return pnode;
      }
   }


   node input_tree::import_node(const char * lpcszName, ::array < attribute > & attributea, importable & importable)
   {
      node pnodePrev = m_node;
      if(m_node.empty())
      {
         m_node = m_document.root();
         if(m_node.get_name() != lpcszName)
         {
            ASSERT(FALSE);
            m_node = node();
            throw "Node not found";
         }
         if(!m_node.contains(attributea))
            return ((node) NULL);
         importable.xml_import(*this);
         return m_document.root();
      }
      else
      {
         node pnode = m_node.child_at(m_node.find(lpcszName, attributea));
         m_node = pnode;
         importable.xml_import(*this);
         m_node = pnodePrev;
         return pnode;
      }
   }



   bool input_tree::get_attr(const char * lpcszName, string & strValue)
   {
      return m_node.get_attr(lpcszName, strValue);
   }


   bool input_tree::get_attr(const char * lpcszName, int32_t & iValue)
   {
      return m_node.get_attr(lpcszName, iValue);
   }


   void input_tree::get_value(string & strValue)
   {
      strValue = m_node.get_value();
   }


   node input_tree::import_node(const char * lpcszName, var & var)
   {
      m_varexchange.m_pvar = &var;
      return import_node(lpcszName, m_varexchange);
   }


} // namespace xml


