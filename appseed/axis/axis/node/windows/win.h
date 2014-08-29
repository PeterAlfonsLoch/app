#pragma once



namespace windows
{

   class interaction_impl;
   class graphics;
   class object;

   template < int32_t t_iHandleCount >
   class handle_base
   {
   public:
      HANDLE m_handlea[t_iHandleCount];
      static const int32_t s_iHandleCount = t_iHandleCount;
   };

   template < class H >
   class handle1 : public handle_base < 1 >
   {
   public:
      handle1() { m_handlea[0] = NULL; }
      typedef handle_base < 1 > HANDLE_AXIS_TYPE;
      inline H get_handle() const { return static_cast < H > (m_handlea[0]); }
      inline operator H () const { return get_handle(); }
      inline H set_handle(H h) { return static_cast < H > (m_handlea[0] = static_cast < HANDLE > (h)); }
   };

   template < class H1, class H2 >
   class handle2 : public handle_base < 2 >
   {
   public:
      handle2() { m_handlea[0] = NULL; m_handlea[1] = NULL; }
      typedef handle_base < 2 > HANDLE_AXIS_TYPE;
      inline H1 get_os_data() const { return static_cast < H1 > (m_handlea[0]); }
      inline H2 get_handle2() const { return static_cast < H2 > (m_handlea[0]); }
      inline H1 set_handle1(H1 h) { return static_cast < H1 > (m_handlea[0] = static_cast < HANDLE > (h)); }
      inline H2 set_handle2(H2 h) { return static_cast < H2 > (m_handlea[1] = static_cast < HANDLE > (h)); }
   };

   typedef handle1 < oswindow > oswindow_handle;
   typedef handle1 < HMENU > hmenu_handle;
   typedef handle2 < HDC, HDC > hdc_handle;
   typedef handle1 < HGDIOBJ > hgdiobj_handle;
   typedef handle1 < HIMAGELIST > himagelist_handle;

} // namespace windows


#include "core/core/ca_fixed_alloc.h"

template<class TYPE>
struct ConstructDestruct
{
   static void Construct(object* pObject)
   { 
      new (pObject) TYPE; 
   }
   static void Destruct(object* pObject)
   {
      TYPE* p = dynamic_cast < TYPE * > (pObject);
      p->~TYPE();
   }
   static void Construct(TYPE * pObject)
   { 
#undef new
      new (pObject) TYPE; 
#define new AURA_NEW
   }
   static void Destruct(TYPE * pObject)
   {
      TYPE* p = dynamic_cast < TYPE * > (pObject);
      p->~TYPE();
   }
};

class WindowsThread;       // forward reference for friend declaration








