#pragma once


namespace xml
{

   
   enum e_action
   {

      set_attr,
      set_name,
      set_value,
      add_attr

   };


   class CLASS_DECL_AXIS edit_item :
      public ::file::serializable
   {
   public:


      e_action       m_eaction;
      index_array    m_iaPath;
      string         m_strName;
      string         m_strValue;


      edit_item(sp(::axis::application) papp);


      void set_name(const sp(::xml::node) pnode);
      void set_value(const sp(::xml::node) pnode);
      void set_attr(const sp(::xml::node) pnode, const attr * pattr);
      void add_attr(const sp(::xml::node) pnode, const attr * pattr);


      virtual void write(::file::output_stream & ostream);
      virtual void read(::file::input_stream & istream);


   };

   class CLASS_DECL_AXIS edit :
      public ::edit < ::xml::document >,
      public ::file::byte_serializable_pointer_array < spa(edit_item) >
   {
   public:


      // index of next item to apply
      index       m_iEdit;


      edit(sp(::axis::application) papp);
      virtual ~edit();


      void set_name(const sp(::xml::node) pnode);
      void set_value(const sp(::xml::node) pnode);
      void set_attr(const sp(::xml::node) pnode, const attr * pattr);
      void add_attr(const sp(::xml::node) pnode, const attr * pattr);


   };


} // namespace xml



