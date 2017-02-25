#pragma once






namespace xml
{


   template < int32_t m_iNodeNameIndex, class TYPE >
   class smart_pointer_array :
      public ::smart_pointer_array < TYPE >,
      public exportable,
      public importable
   {
   public:


      smart_pointer_array();
      smart_pointer_array(const smart_pointer_array & xmla);


      virtual void xml_export(output_tree & xmlof);
      virtual void xml_import(input_tree & xmlif);


   };


   template < int32_t m_iNodeNameIndex,class TYPE >
   smart_pointer_array<m_iNodeNameIndex,TYPE>::
      smart_pointer_array()
   {
      }

   template < int32_t m_iNodeNameIndex,class TYPE >
   smart_pointer_array<m_iNodeNameIndex,TYPE>::
      smart_pointer_array(const smart_pointer_array & xmla)
   {

      copy(xmla);

   }




} // namespace xml





namespace xml
{


   template < int32_t m_iNodeNameIndex,class TYPE >
   class smart_pointer_array2:
      public ::smart_pointer_array2 < TYPE >,
      public exportable,
      public importable
   {
   public:


      smart_pointer_array2();
      smart_pointer_array2(const smart_pointer_array2 & xmla);


      virtual void xml_export(output_tree & xmlof);
      virtual void xml_import(input_tree & xmlif);


   };


   template < int32_t m_iNodeNameIndex,class TYPE >
   smart_pointer_array2<m_iNodeNameIndex,TYPE>::
      smart_pointer_array2()
   {
   }

   template < int32_t m_iNodeNameIndex,class TYPE >
   smart_pointer_array2<m_iNodeNameIndex,TYPE>::
      smart_pointer_array2(const smart_pointer_array2 & xmla)
   {

      copy(xmla);

   }

   

} // namespace xml



