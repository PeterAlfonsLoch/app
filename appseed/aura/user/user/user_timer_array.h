#pragma once


namespace user
{


   class CLASS_DECL_AURA timer_array :
      virtual public ::object
   {
   public:


      mutex                               m_mutex;
      spa(timer_item)                     m_timera;
      index                               m_iItem;
      ptr_array < interaction >           m_uiptra;


      timer_array(sp(::aura::application) papp);
      virtual ~timer_array();


      uint_ptr set(interaction * pui,uint_ptr uiId,UINT uiElapse);
      void check();
      bool unset(interaction * pui,uint_ptr uiId);
      void unset(interaction * pui);
      void detach(spa(timer_item) & timera,interaction * pui);
      interaction * find(element * pca);
      index find(interaction * pui,uint_ptr uiId);
      index find_from(interaction * pui,index iStart);

      virtual void assert_valid() const;
      virtual void dump(dump_context & dc) const;

      };



} // namespace user