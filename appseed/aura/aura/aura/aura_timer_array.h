#pragma once


namespace aura
{


   class CLASS_DECL_AURA timer_array :
      virtual public ::object
   {
   public:


      mutex                               m_mutex;
      spa(timer_item)                     m_timera;
      index                               m_iItem;
      ptr_array < ::user::elemental >     m_uiptra;


      timer_array(::aura::application * papp);
      virtual ~timer_array();


      uint_ptr set(::user::elemental * pui,uint_ptr uiId,UINT uiElapse);
      void check();
      bool unset(::user::elemental * pui,uint_ptr uiId);
      void unset(::user::elemental * pui);
      void detach(spa(timer_item) & timera,::user::elemental * pui);
      ::user::elemental * find(object * pobject);
      index find(::user::elemental * pui,uint_ptr uiId);
      index find_from(::user::elemental * pui,index iStart);

      virtual void assert_valid() const;
      virtual void dump(dump_context & dc) const;

      };



} // namespace aura


























































