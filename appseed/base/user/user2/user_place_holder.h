#pragma once


namespace user
{


   class place_holder_container;


   class CLASS_DECL_BASE place_holder :
      virtual public interaction
   {
   public:


      interaction_ptr_array  m_uiptraHold;


      place_holder(sp(::axis::application) papp);
      virtual ~place_holder();


      virtual bool create_window(const RECT & rect, sp(::user::place_holder_container) pcontainer,id id);

      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual bool can_merge(sp(::user::interaction) pui);
      virtual bool merge(sp(::user::interaction) pui);
      virtual bool hold(sp(::user::interaction) pui);
      virtual bool unhold(sp(::user::interaction) pui);
      virtual bool is_holding(sp(::user::interaction) pui);

      virtual void _001OnDraw(::draw2d::graphics * pdc);
      virtual void _001OnNcDraw(::draw2d::graphics * pdc);


      virtual void layout();

      ::user::interaction * get_hold();

      virtual bool is_place_holder();

      virtual bool _001IsBackgroundBypass();


   };

   class CLASS_DECL_BASE place_holder_ptra :
      virtual public spa(place_holder)
   {
   public:

      int32_t hold(sp(::user::interaction) pui);
      int32_t unhold(sp(::user::interaction) pui);

   };

} // namespace user
