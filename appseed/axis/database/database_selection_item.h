#pragma once


namespace database
{

   
   class CLASS_DECL_BASE selection_item  
   {
   public:

      
      id     m_id;
      id     m_idIndex;
      
      
      selection_item();
      selection_item(id & key, id & idIndex);
      virtual ~selection_item();


   };


} // namespace database




