#pragma once

namespace ca
{

   /////////////////////////////////////////////////////////////////////////////
   // graphics_object abstract class for ::ca::graphics_sp SelectObject

   class CLASS_DECL_ca graphics_object : 
      virtual public ::radix::object
   {
   public:


      virtual BOOL is_set();

   // Constructors
      virtual BOOL delete_object();

      virtual void * get_os_data() const;
      virtual void * detach_os_data();

   // Operations
   #pragma push_macro("GetObject")
   #undef GetObject
      virtual int _AFX_FUNCNAME(GetObject)(int nCount, LPVOID lpObject) const;
      virtual int GetObject(int nCount, LPVOID lpObject) const;
   #pragma pop_macro("GetObject")
      virtual UINT GetObjectType() const;
      virtual BOOL CreateStockObject(int nIndex);
      virtual BOOL UnrealizeObject();
      virtual BOOL operator==(const ::ca::graphics_object& obj) const;
      virtual BOOL operator!=(const ::ca::graphics_object& obj) const;

   // Implementation
   public:
      virtual ~graphics_object();
   #ifdef _DEBUG
      virtual void dump(dump_context & dumpcontext) const;
      virtual void assert_valid() const;
   #endif
   };

} // namespace ca