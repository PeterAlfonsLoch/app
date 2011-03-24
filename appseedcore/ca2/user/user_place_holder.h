#pragma once


namespace user
{

   class place_holder_container;

   class CLASS_DECL_ca place_holder : 
      virtual public control
   {
   public:


      LPWndArray  m_uiptraHold;


      place_holder(::ca::application * papp);
      virtual ~place_holder();


      virtual bool create(place_holder_container * pcontainer);

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pdispatch);

      
      virtual bool can_merge(::user::interaction * pui);
      virtual bool merge(::user::interaction * pui);
      virtual bool hold(::user::interaction * pui);
      virtual bool unhold(::user::interaction * pui);
      virtual bool is_holding(::user::interaction * pui);


      virtual void layout();

      ::user::interaction * get_ui();


   };

} // namespace user