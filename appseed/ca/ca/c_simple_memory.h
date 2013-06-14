#pragma once




class CLASS_DECL_c simple_memory
{
public:

   
   char *            m_psz;
   ::count m_iAlloc;
   ::count m_iSize;

   ::count m_iPos;
   bool              m_bAttach;


   simple_memory();
   simple_memory(const simple_memory & memory);
   simple_memory(const char * psz);
   ~simple_memory();


   void allocate(::count iSize);

   void attach(void * p, ::count iSize);


   void write(void * p, ::count iCount);


   ::count read(void * p, ::count iCount) const;


   void from_string(const vsstring & str);

   vsstring str();

   void to_string(vsstring & str);

   inline void * get_data() { return m_psz; }

   inline const void * get_data() const { return m_psz; }

   inline ::count get_size() const { return m_iSize; } 

   void FromAsc(const char * psz);

   void From(const char * psz);

   void ToAsc(vsstring & str);

   void To(vsstring & str, size_t dwStart = 0, size_t dwEnd = -1);

   simple_memory & operator = (const simple_memory & memory);


   void to_hex(vsstring & strHex);

   bool from_hex(const char * pszHex);

#ifdef METROWIN

   inline Platform::Array < uchar, 1U > ^ get_os_bytes() const
   {
      return ref new Platform::Array < uchar, 1U > ((uchar *) m_psz, m_iSize);
   }

   inline ::Windows::Storage::Streams::IBuffer ^ get_os_stream_buffer() const
   {
      return ::Windows::Security::Cryptography::CryptographicBuffer::CreateFromByteArray(get_os_bytes());
   }

   inline void set_os_bytes(Platform::Array < uchar, 1U > ^ a)
   {
      allocate(a->Length);
      memcpy(get_data(), a->Data, get_size());
   }

   inline void set_os_stream_buffer(::Windows::Storage::Streams::IBuffer ^ ibuf)
   {
      Platform::Array < uchar, 1U > ^ a = nullptr;
      ::Windows::Security::Cryptography::CryptographicBuffer::CopyToByteArray(ibuf, &a);
      return set_os_bytes(a);
   }
    
#elif defined(MACOS)
    
    inline CFDataRef get_os_cf_data() const
    {
        return CFDataCreate(kCFAllocatorNull, (const UInt8 *) m_psz, (CFIndex) m_iSize);
    }
    
    inline void set_os_cf_data(CFDataRef data)
    {
        allocate(CFDataGetLength(data));
        memcpy(get_data(), CFDataGetBytePtr(data), get_size());
    }

#endif

   bool to_file(const char * pszFile);

};






