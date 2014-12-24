#pragma once


namespace database
{

   
   class CLASS_DECL_BASE selection_item  
   {
   public:

      
      id     m_id;
      
      
      selection_item();
      selection_item(id & key);
      virtual ~selection_item();


   };


} // namespace database




