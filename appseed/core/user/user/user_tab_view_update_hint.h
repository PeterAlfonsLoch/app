#pragma once

namespace user
{

   class CLASS_DECL_CORE tab_view_update_hint :
      public ::object  
   {
   public:
      enum e_type
      {
         type_get_tab,
         type_set_tab,
         TypeOnShowTab,
         TypeOnBeforeShowTab,
      };

      void set_type(e_type e_type);
      bool is_type_of(e_type e_type);

      tab_view_update_hint();
      virtual ~tab_view_update_hint();

      id m_id;

      e_type m_etype;

   };

} // namespace user