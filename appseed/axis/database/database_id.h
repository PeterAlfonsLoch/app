#pragma once


namespace database
{

   
   class CLASS_DECL_AXIS id
   {
   public:
      id(const id & id);
      id(::id id);
      id(const char * psz);
      id(int32_t i);
      id(int32_t i1, int32_t i2, int32_t i3);
      id(const string & str);
      id();
      ~id();

      virtual ::id get_id();
      virtual void set_id(::id id);

      virtual bool is_null();

      ::id m_id;

      bool operator == (const id & id) const;
      bool operator == (const char * psz) const;
      bool operator == (int32_t i) const;

      const id & operator = (::id id);
      const id & operator = (const char * psz);
      const id & operator = (int32_t i);
      const id & operator = (const string & str);
   };

   inline id::id(const string & str)
   {
      m_id = str;
   }

   inline id::id(const id & key)
   {
      m_id = key.m_id;
   }

   inline id::id(::id id)
   {
      m_id =  id;
   }

   inline id::id(const char * psz)
   {
      m_id = psz;
   }

   inline id::id(int32_t i)
   {
      m_id = i;
   }

   inline id::id(int32_t i1, int32_t i2, int32_t i3)
   {
      m_id = ::str::from(i1) + "." + ::str::from(i2) + "." + ::str::from(i3);
   }

   inline id::id()
   {
   }

   inline id::~id()
   {
   }

   inline bool id::operator == (const id & id) const
   {
      return m_id == id.m_id;
   }

   inline bool id::operator == (const char * psz) const
   {
      return m_id == psz;
   }

   inline bool id::operator == (int32_t i) const
   {
      return m_id == i;
   }

   inline const id & id::operator = (::id id)
   {
      m_id = id;
      return *this;
   }

   inline const id & id::operator = (const char * psz)
   {
      m_id = psz;
      return *this;
   }

   inline const id & id::operator = (int32_t i)
   {
      m_id = i;
      return *this;
   }

   inline const id & id::operator = (const string & str)
   {
      m_id = (const char *) str;
      return *this;
   }

   
} // namespace dabase



