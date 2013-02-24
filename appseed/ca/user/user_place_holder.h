#pragma once


namespace user
{

   class place_holder_container;

   class CLASS_DECL_ca place_holder :
      virtual public control
   {
   public:


      interaction_ptr_array  m_uiptraHold;


      place_holder(::ca::application * papp);
      virtual ~place_holder();


      using ::user::control::create;
      virtual bool create(place_holder_container * pcontainer, id id);

      virtual void install_message_handling(::ca::message::dispatch * pdispatch);

      virtual bool can_merge(::user::interaction * pui);
      virtual bool merge(::user::interaction * pui);
      virtual bool hold(::user::interaction * pui);
      virtual bool unhold(::user::interaction * pui);
      virtual bool is_holding(::user::interaction * pui);


      virtual void layout();

      ::user::interaction * get_ui();


   };

   class CLASS_DECL_ca place_holder_ptra :
      virtual public comparable_array < place_holder * >
   {
   public:

      int32_t hold(::user::interaction * pui);
      int32_t unhold(::user::interaction * pui);

   };

} // namespace user
