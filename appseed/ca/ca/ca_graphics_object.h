#pragma once


namespace ca
{


   class CLASS_DECL_ca graphics_object :
      virtual public ::gen::object
   {
   public:


      bool  m_bUpdated;


      virtual ~graphics_object();


      virtual bool is_set();
      virtual bool is_updated();


      virtual void * get_os_data() const;

/*   #pragma push_macro("GetObject")
   #undef GetObject
      virtual int32_t ___FUNCNAME(GetObject)(int32_t nCount, LPVOID lpObject) const;
      virtual int32_t GetObject(int32_t nCount, LPVOID lpObject) const;
   #pragma pop_macro("GetObject")*/
      virtual UINT GetObjectType() const;
      virtual bool CreateStockObject(int32_t nIndex);
      virtual bool UnrealizeObject();
      virtual bool operator==(const ::ca::graphics_object& obj) const;
      virtual bool operator!=(const ::ca::graphics_object& obj) const;

      virtual void dump(dump_context & dumpcontext) const;
      virtual void assert_valid() const;

   };

} // namespace ca


