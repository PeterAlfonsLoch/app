#pragma once


namespace ca
{


   class CLASS_DECL_ca graphics_object : 
      virtual public ::radix::object
   {
   public:


      bool  m_bUpdated;


      virtual ~graphics_object();


      virtual bool is_set();
      virtual bool is_updated();


      virtual void * get_os_data() const;

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

   #ifdef _DEBUG
      virtual void dump(dump_context & dumpcontext) const;
      virtual void assert_valid() const;
   #endif
   };

} // namespace ca