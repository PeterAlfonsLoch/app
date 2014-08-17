#pragma once


namespace xml
{


   template < int32_t m_iNodeNameIndex, class TYPE, class ARG_TYPE = const TYPE &, class ARRAY = ::smart_pointer_array < TYPE > >
   class array :
      public ARRAY,
      public exportable,
      public importable
   {
   public:


      array();
      array(const array & xmla);


      virtual void xml_export(output_tree & xmlof);
      virtual void xml_import(input_tree & xmlif);


   };


   template < int32_t m_iNodeNameIndex, class TYPE, class ARG_TYPE, class ARRAY >
   array<m_iNodeNameIndex, TYPE, ARG_TYPE, ARRAY>::
      array()
   {
   }

   template < int32_t m_iNodeNameIndex, class TYPE, class ARG_TYPE, class ARRAY >
   array<m_iNodeNameIndex, TYPE, ARG_TYPE, ARRAY>::
      array(const array & xmla) :
      ARRAY (xmla)
   {
   }



   template < int32_t m_iNodeNameIndex, class TYPE, class ARG_TYPE, class ARRAY >
   void
      array<m_iNodeNameIndex, TYPE, ARG_TYPE, ARRAY>::
      xml_export(output_tree & xmlof)
   {
      xmlof.set_attr("count", this->get_size());
      for(int32_t i = 0; i < this->get_size(); i++)
      {
         node * pnode = xmlof.export_node(xmlof.get_node_name(m_iNodeNameIndex), this->element_at(i));
         pnode->add_attr("array_index", i);
      }
   }


   template < int32_t m_iNodeNameIndex, class TYPE, class ARG_TYPE, class ARRAY >
   void
      array<m_iNodeNameIndex, TYPE, ARG_TYPE, ARRAY>::
      xml_import(input_tree & xmlif)
   {
      int32_t iSize;
      xmlif.get_attr("count", iSize);
      ARRAY::set_size(iSize);
      for(int32_t i = 0; i < this->get_size(); i++)
      {
         attr_array attra(this->get_app());
         attra.add("array_index", i);
         xmlif.import_node(xmlif.get_node_name(m_iNodeNameIndex), attra, this->element_at(i));
      }
   }



} // namespace xml




