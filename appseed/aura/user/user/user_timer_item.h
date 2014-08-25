#pragma once


namespace user
{


   class CLASS_DECL_AURA timer_item :
      virtual public element
   {
   public:


      interaction *        m_pui;
      uint_ptr             m_uiId;
      UINT                 m_uiElapse;
      UINT                 m_uiLastSent;


      timer_item(sp(::aura::application) papp);
      virtual ~timer_item();


      bool check(single_lock & sl);


   };


} // namespace user





