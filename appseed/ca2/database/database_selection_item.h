#pragma once

namespace database
{

   class CLASS_DECL_ca2 selection_item  
   {
   public:
      selection_item();
      selection_item(
         id & key,
         id & idIndex);
      virtual ~selection_item();


      id     m_id;
      id     m_idIndex;
   };


} // namespace database