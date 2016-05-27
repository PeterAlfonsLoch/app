#pragma once


namespace user
{


   class place_holder_container;


   class CLASS_DECL_BASE place_holder :
      virtual public interaction
   {
   public:


      //interaction_spa  m_uiptraHold;


      place_holder(::aura::application * papp);
      virtual ~place_holder();


      sp(place_holder) create_shadow_clone();


      virtual bool create_window(const RECT & rect, ::user::place_holder_container * pcontainer,id id);

      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual bool can_merge(::user::interaction * pui);
      virtual bool merge(::user::interaction * pui);
      virtual bool hold(::user::interaction * pui);
      virtual bool unhold(::user::interaction * pui);
      virtual bool is_holding(::user::interaction * pui);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);
      virtual void _001OnNcDraw(::draw2d::graphics * pgraphics);


      virtual void layout();

      ::user::interaction * get_hold();

      virtual bool is_place_holder();

      virtual bool _001IsBackgroundBypass();

      virtual bool _001OnCmdMsg(::aura::cmd_msg * pcmdmsg);


   };

   class CLASS_DECL_BASE place_holder_ptra :
      virtual public spa(place_holder)
   {
   public:

      int32_t hold(::user::interaction * pui);
      int32_t unhold(::user::interaction * pui);

   };

} // namespace user
