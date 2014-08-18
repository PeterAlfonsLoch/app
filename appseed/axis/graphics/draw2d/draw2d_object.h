#pragma once


namespace draw2d
{


   class CLASS_DECL_AXIS object :
      virtual public ::object
   {
   public:


      bool           m_bUpdated;
      void *         m_powner; // in a normal usage/flow I can change the object only if I am the owner, otherwise create another object



      virtual ~object();


      virtual bool is_set();
      virtual bool is_updated();
      
      virtual void defer_update() const;
      
      virtual bool destroy();
      using ::object::create;
      virtual bool create();


      virtual void * get_os_data() const;
      virtual void * get_os_data_ex(int i) const;

      template < typename T >
      T * get_typed_os_data(int i) const
      {
         return (T *) get_os_data_ex(i);
      }


/*   #pragma push_macro("GetObject")
   #undef GetObject
      virtual int32_t ___FUNCNAME(GetObject)(int32_t nCount, LPVOID lpObject) const;
      virtual int32_t GetObject(int32_t nCount, LPVOID lpObject) const;
   #pragma pop_macro("GetObject")*/
      virtual UINT GetObjectType() const;
      virtual bool CreateStockObject(int32_t nIndex);
      virtual bool UnrealizeObject();
      virtual bool operator==(const ::draw2d::object & obj) const;
      virtual bool operator!=(const ::draw2d::object & obj) const;

      virtual void dump(dump_context & dumpcontext) const;
      virtual void assert_valid() const;

      
   };

   
} // namespace draw2d




