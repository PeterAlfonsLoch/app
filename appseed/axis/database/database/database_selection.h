#pragma once


namespace database
{

   class CLASS_DECL_AXIS selection
   {
   public:

      void add_item(class id id, class id idIndex);
      selection_item & get_item(index iItem);
      ::count get_item_count();
      selection();
      virtual ~selection();

      array < selection_item, selection_item & > m_itema;

   };


   inline ::count selection::get_item_count()
   {
      return m_itema.get_size();
   }

   inline selection_item & selection::get_item(index iItem)
   {
      return m_itema.element_at(iItem);
   }

} // namespace database
