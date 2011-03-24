#pragma once


namespace user
{

   class CLASS_DECL_ca place_holder_container : 
      virtual public control
   {
   public:

      
      array_app_alloc < place_holder, place_holder & > m_holdera;


      place_holder_container(::ca::application * papp);
      virtual ~place_holder_container();


      void _001InstallMessageHandling(::user::win::message::dispatch * pdispatch);


      virtual bool create(::user::interaction * puiParent);


      virtual place_holder * hold(::user::interaction * pui);
      virtual bool unhold(::user::interaction * pui);

      virtual bool on_hold(::user::interaction * pui, place_holder * pholder);
      virtual bool on_unhold(::user::interaction * pui, place_holder * pholder);

   };

} // namespace user