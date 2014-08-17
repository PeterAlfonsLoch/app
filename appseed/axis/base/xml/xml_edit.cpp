#include "framework.h"


namespace xml
{


   edit_item::edit_item(sp(::base::application) papp) :
      element(papp)
   {
   }


   void edit_item::set_name(const sp(::xml::node) pnode)
   {

      m_eaction      = ::xml::set_name;
      pnode->get_indexed_path(m_iaPath);
      m_strName      = pnode->get_name();

   }

   void edit_item::set_value(const sp(::xml::node) pnode)
   {

      m_eaction      = ::xml::set_value;
      pnode->get_indexed_path(m_iaPath);
      m_strValue     = pnode->get_value();

   }

   void edit_item::set_attr(const sp(::xml::node) pnode, const attr * pattr)
   {

      m_eaction      = ::xml::set_attr;
      pnode->get_indexed_path(m_iaPath);
      m_strName      = pattr->name();
      m_strValue     = pattr->get_value();

   }

   void edit_item::add_attr(const sp(::xml::node) pnode, const attr * pattr)
   {

      m_eaction      = ::xml::add_attr;
      pnode->get_indexed_path(m_iaPath);
      m_strName      = pattr->name();
      m_strValue     = pattr->get_value();

   }

   void edit_item::write(::file::output_stream & ostream)
   {

      ostream << (int32_t) m_eaction;
      ostream << m_iaPath;
      ostream << m_strName;
      ostream << m_strValue;

   }

   void edit_item::read(::file::input_stream & istream)
   {

      istream >> (int32_t &) m_eaction;
      istream >> m_iaPath;
      istream >> m_strName;
      istream >> m_strValue;

   }



   edit::edit(sp(::base::application) papp) :
      element(papp),
      ::edit < ::xml::document > (papp)
   {

      m_iEdit = -1;

   }

   edit::~edit()
   {
   }


   void edit::set_name(const sp(::xml::node) pnode)
   {

      if(pnode->get_document() != m_spdata.m_p)
         throw simple_exception(get_app(), "unmatched xml document");

      edit_item * pitem = add_new();

      pitem->set_name(pnode);

   }

   void edit::set_value(const sp(::xml::node) pnode)
   {

      if(pnode->get_document() != m_spdata.m_p)
         throw simple_exception(get_app(), "unmatched xml document");

      edit_item * pitem = add_new();

      pitem->set_value(pnode);

   }

   void edit::set_attr(const sp(::xml::node) pnode, const ::xml::attr * pattr)
   {

      if(pnode->get_document() != m_spdata.m_p)
         throw simple_exception(get_app(), "unmatched xml document");

      edit_item * pitem = add_new();

      pitem->set_attr(pnode, pattr);

   }


   void edit::add_attr(const sp(::xml::node) pnode, const ::xml::attr * pattr)
   {

      if(pnode->get_document() != m_spdata.m_p)
         throw simple_exception(get_app(), "unmatched xml document");

      edit_item * pitem = add_new();

      pitem->add_attr(pnode, pattr);

   }



} // namespace xml



