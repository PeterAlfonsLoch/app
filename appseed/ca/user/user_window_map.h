#pragma once

#ifdef _WIN64
template <>
inline UINT HashKey(int_ptr key)
{
   // default identity hash - works for most primitive values
   return (uint32_t)(((uint_ptr)key)>>32);
}
#else
template <>
inline UINT HashKey(int_ptr key)
{
   // default identity hash - works for most primitive values
   return (uint32_t)(((uint_ptr)key)>>16);
}
#endif

namespace user
{


   class window_interface;


   class CLASS_DECL_ca window_map
   {
   public:
      window_map();
      virtual ~window_map();

      ::user::window_interface * get(int_ptr iWindow);


      void set(int_ptr iWindow, const ::user::window_interface * pinterface);
      ::collection::map < int_ptr, int_ptr, ::user::window_interface *, ::user::window_interface * > m_map;

   };


} // namespace user


