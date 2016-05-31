#pragma once


namespace ace
{


   class CLASS_DECL_ACE timer_item :
      virtual public object
   {
   public:


      ::user::primitive *     m_pui;
      uint_ptr                m_uiId;
      UINT                    m_uiElapse;
      UINT                    m_uiLastSent;


      timer_item(::ace::application * papp);
      virtual ~timer_item();


      bool check(single_lock & sl);


   };


} // namespace namespace ace






