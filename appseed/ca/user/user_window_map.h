#pragma once

#ifdef _WIN64
template <> 
inline UINT HashKey(INT_PTR key)
{
   // default identity hash - works for most primitive values
   return (DWORD)(((DWORD_PTR)key)>>32);
}
#else
template <> 
inline UINT HashKey(INT_PTR key)
{
   // default identity hash - works for most primitive values
   return (DWORD)(((DWORD_PTR)key)>>16);
}
#endif 

namespace user
{

   class ::user::window_interface;

   class CLASS_DECL_ca window_map
   {
   public:
      window_map();
      virtual ~window_map();

      ::user::window_interface * get(INT_PTR iWindow);
      

      void set(INT_PTR iWindow, const ::user::window_interface * pinterface);
      ::collection::map < INT_PTR, INT_PTR, ::user::window_interface *, ::user::window_interface * > m_map;

   };


}
