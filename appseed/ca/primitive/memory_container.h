#pragma once


namespace primitive
{


   class CLASS_DECL_ca memory_container :
      virtual public ::radix::object
   {
   protected:


      sp(base_memory)                        m_spmemory;
      primitive_array < void ** >            m_vppa;
      memory_size                            m_dwAllocationAddUp;


   public:

      memory_container(::ca::application * papp);
      memory_container(::ca::application * papp, void * pMemory, memory_size dwSize);
      memory_container(::ca::application * papp, base_memory * pmemory);
      memory_container(const memory_container & container);
      virtual ~memory_container();


      void allocate_add_up(memory_size dwAddUp);
      void allocate(memory_size dwNewLength);
      void allocate_internal(memory_size dwNewLength);

      virtual base_memory * create_memory();
      base_memory * get_memory() const;

      memory_size get_size() const;

      void from_string(const wchar_t * pwsz);
      void from_string(const char * psz);
      void from_string(const string & str);
      void from_string(const var & str);
      void to_string(string & str);

      void FullLoad(base_memory *pmemorystorage);
      void FullLoad(ex1::file & file);

      void keep_pointer(void **ppvoid);
      void offset_kept_pointers(memory_offset iOffset);

      LPBYTE get_data();

      bool IsValid() const;

      memory_container & operator =(const memory_container &container);

      bool Attach(base_memory *pstorage);

      base_memory * detach();

      virtual memory *          get_primitive_memory();
      virtual shared_memory *   get_shared_memory();
      virtual virtual_memory *  get_virtual_memory();

      virtual memory *          detach_primitive_memory();
      virtual shared_memory *   detach_shared_memory();
      virtual virtual_memory *  detach_virtual_memory();

      virtual LPBYTE            detach_primitive_storage();
      virtual HGLOBAL           detach_shared_storage();
      virtual LPBYTE            detach_virtual_storage();

   };


} // namespace primitive



