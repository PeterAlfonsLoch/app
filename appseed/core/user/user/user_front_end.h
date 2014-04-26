#pragma once


#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

typedef void * HHOOK ;

#endif // defined(LINUX)


namespace user
{
   class menu;

} // namespace user

namespace user
{

   class CLASS_DECL_CORE front_end
   {
   public:


      static ::user::menu *    s_pmenu;
      static HHOOK            s_hhookMouse;
      static int32_t              s_iMouseHookCount;


      front_end(void);
      ~front_end(void);

      static LRESULT CALLBACK MouseProc(int32_t nCode, WPARAM wparam, LPARAM lparam);



   };

} // namespace user
