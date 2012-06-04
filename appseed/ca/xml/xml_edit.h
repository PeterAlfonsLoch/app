#pragma once


namespace xml
{

   enum e_action
   {

      set_attr,
      set_name,
      set_value,
      add_attr,

   };


   class CLASS_DECL_ca edit_item :
      public ex1::byte_serializable
   {
   public:

      
      e_action       m_eaction;
      index_array    m_iaPath;
      string         m_strName;
      string         m_strValue;


      void set_name(const ::xml::node * pnode);
      void set_value(const ::xml::node * pnode);
      void set_attr(const ::xml::node * pnode, const attr * pattr);
      void add_attr(const ::xml::node * pnode, const attr * pattr);


      virtual void write(::ex1::byte_output_stream & ostream);
      virtual void read(::ex1::byte_input_stream & istream);

      
   };

   class CLASS_DECL_ca edit :
      public ::ca::edit < ::xml::document >,
      public ::ex1::byte_serializable_array < array_ptr_alloc < edit_item > >
   {
   public:


      // index of next item to apply
      index       m_iEdit;


      edit(::ca::application * papp);
      virtual ~edit();


      void set_name(const ::xml::node * pnode);
      void set_value(const ::xml::node * pnode);
      void set_attr(const ::xml::node * pnode, const attr * pattr);
      void add_attr(const ::xml::node * pnode, const attr * pattr);


   private:


      edit(const edit &) :
         ::ca::edit < ::xml::document >(NULL)
      {
      }


   };


} // namespace xml



