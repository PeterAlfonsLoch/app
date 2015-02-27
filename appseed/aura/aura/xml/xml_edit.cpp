//#include "framework.h"


namespace xml
{


   edit_item::edit_item(::aura::application * papp) :
      object(papp)
   {
   }


   void edit_item::set_name(const ::xml::node node)
   {

      m_eaction      = ::xml::set_name;
      node.get_indexed_path(m_iaPath);
      m_strName      = node.get_name();

   }

   void edit_item::set_value(const ::xml::node node)
   {

      m_eaction      = ::xml::set_value;
      node.get_indexed_path(m_iaPath);
      m_strValue     = node.get_value();

   }

   void edit_item::set_attr(const ::xml::node node, const ::xml::attribute * pattr)
   {

      m_eaction      = ::xml::set_attr;
      node.get_indexed_path(m_iaPath);
      m_strName      = pattr->name();
      m_strValue     = pattr->value();

   }

   void edit_item::add_attr(const ::xml::node node, const xml::attribute * pattr)
   {

      m_eaction      = ::xml::add_attr;
      node.get_indexed_path(m_iaPath);
      m_strName      = pattr->name();
      m_strValue     = pattr->value();

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



   edit::edit(::aura::application * papp) :
      object(papp),
      ::edit < ::xml::document > (papp)
   {

      m_iEdit = -1;

   }

   edit::~edit()
   {
   }


   void edit::set_name(const ::xml::node node)
   {

      if(node.root() != m_spdata.cast < data >()->m_document)
         throw simple_exception(get_app(), "unmatched xml document");

      edit_item * pitem = add_new();

      pitem->set_name(node);

   }

   void edit::set_value(const ::xml::node node)
   {

      if(node.root() != m_spdata.cast < data >()->m_document)
         throw simple_exception(get_app(), "unmatched xml document");

      edit_item * pitem = add_new();

      pitem->set_value(node);

   }

   void edit::set_attr(const ::xml::node node, const ::xml::attribute * pattr)
   {

      if(node.root() != m_spdata.cast < data >()->m_document)
         throw simple_exception(get_app(), "unmatched xml document");

      edit_item * pitem = add_new();

      pitem->set_attr(node, pattr);

   }


   void edit::add_attr(const ::xml::node node, const ::xml::attribute * pattr)
   {

      if(node.root() != m_spdata.cast < data >()->m_document)
         throw simple_exception(get_app(), "unmatched xml document");

      edit_item * pitem = add_new();

      pitem->add_attr(node, pattr);

   }



} // namespace xml



