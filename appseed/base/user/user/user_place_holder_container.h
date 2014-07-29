#pragma once


namespace user
{

   class CLASS_DECL_BASE place_holder_container :
      virtual public interaction
   {
   public:


      spa(place_holder) m_holdera;


      place_holder_container(sp(::base::application) papp);
      virtual ~place_holder_container();


      void install_message_handling(::message::dispatch * pdispatch);


      using ::user::interaction::create;
      virtual bool create(sp(::user::interaction) puiParent, id id);


      virtual sp(place_holder) get_new_place_holder(LPCRECT lpcrectCreate);
      virtual bool remove_place_holder(sp(place_holder) pholder);


      virtual sp(place_holder) place(sp(::user::interaction) pui,LPCRECT lpcrectCreate);
      virtual bool unplace(sp(::user::interaction) pui);

      virtual bool on_hold(sp(::user::interaction) pui, sp(place_holder) pholder);
      virtual bool on_unhold(sp(::user::interaction) pui, sp(place_holder) pholder);

   };


   class CLASS_DECL_BASE place_holder_container_ptra :
      virtual public spa(place_holder_container)
   {
   public:

      virtual place_holder_ptra place(sp(::user::interaction) pui, LPCRECT lpcrectCreate);
      virtual int32_t unplace(sp(::user::interaction) pui);

   };

} // namespace user
