#pragma once


#ifdef LINUX

typedef void * HHOOK ;

#endif // defined(LINUX)


namespace userbase
{
   class menu;

} // namespace userbase

namespace user
{

   class CLASS_DECL_ca2 front_end
   {
   public:

      front_end(void);
      ~front_end(void);

      static LRESULT CALLBACK MouseProc(
         int32_t      nCode,
         WPARAM   wparam,
         LPARAM   lparam);

   protected:
      static ::userbase::menu *    s_pmenu;
      static HHOOK            s_hhookMouse;
      static int32_t              s_iMouseHookCount;
   };

} // namespace user
