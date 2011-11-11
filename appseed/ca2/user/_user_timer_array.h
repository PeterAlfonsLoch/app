#pragma once

namespace user
{
   class CLASS_DECL_ca timer_item
   {
   public:
      interaction *     m_pguie;
      UINT                 m_uiId;
      UINT                 m_uiElapse;
      UINT                 m_uiLastSent;  
      void check();
   };


   class CLASS_DECL_ca timer_array :
         public base_array < timer_item, timer_item & >,
         public pointer_array < interaction >
      {
      public:
         void OnPointerClear(interaction * pui);
         UINT set(interaction * pguie, UINT uiId, UINT uiElapse);
         void check();
         bool unset(interaction * pguie, UINT uiId);
         void unset(interaction * pguie);
         int find(interaction * pguie, UINT uiId);
         int find_from(interaction * pguie, int iStart);

         virtual void assert_valid() const;
         virtual void dump(dump_context & dc) const;

      };

} // namespace user