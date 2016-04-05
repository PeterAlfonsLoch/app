#pragma once


namespace user
{

   class interaction_base;

} // namespace user


namespace windows
{


   class CLASS_DECL_BASE window_draw:
      virtual public ::user::window_draw
   {
   public:


      window_draw(::aura::application * papp);
      virtual ~window_draw();



   };


} // namespace windows


