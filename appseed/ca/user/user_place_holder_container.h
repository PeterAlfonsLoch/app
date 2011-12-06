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


      void install_message_handling(::gen::message::dispatch * pdispatch);


      virtual bool create(::user::interaction * puiParent, id id);

      
      virtual place_holder * get_new_place_holder();
      virtual bool remove_place_holder(place_holder * pholder);


      virtual place_holder * hold(::user::interaction * pui);
      virtual bool unhold(::user::interaction * pui);

      virtual bool on_hold(::user::interaction * pui, place_holder * pholder);
      virtual bool on_unhold(::user::interaction * pui, place_holder * pholder);

   };


   class CLASS_DECL_ca place_holder_container_ptra :
      virtual public comparable_array < place_holder_container * >
   {
   public:

      virtual place_holder_ptra hold(::user::interaction * pui);   
      virtual int unhold(::user::interaction * pui);

   };

} // namespace user