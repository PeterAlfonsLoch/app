#pragma once

struct id_all
{

   int64_t            m_iType;
   int64_t            m_iBody;

};

class CLASS_DECL_AURA id
{
public:


   enum e_type : int64_t
   {

      type_null = 0,
      type_empty = 1,
      type_integer = 2,
      type_text = 3

   };


   union
   {

      struct
      {

         e_type                  m_etype;

         union
         {

            int64_t              m_i;
            const char *         m_psz;

         };

      };

      struct
      {

         int64_t            m_iType;
         int64_t            m_iBody;

      };

      id_all                  m_all;

   };

protected:
   friend id_space;
   inline id(const char * psz, id_space *);
public:


   inline id();
   inline id(const id & id);
   id(const char * psz);
   id(int_ptr i);
   id(uint_ptr ui);
#if defined(_LP64) || defined(_AMD64_)
   id(int32_t i);
   id(uint32_t ui);
#endif
   id(const string & str);
   id(const string_interface & str);
   id(const var & var);


   void raw_set(const char * psz);


   string str() const;
#ifndef __GNUC__
   operator string() const;
#endif


   inline bool operator == (const id & id) const;
   inline bool operator != (const id & id) const;
   inline bool operator < (const id & id) const;
   inline bool operator <= (const id & id) const;
   inline bool operator > (const id & id) const;
   inline bool operator >= (const id & id) const;
   inline id & operator = (const id & id);


   inline bool operator == (const char * psz) const;
   inline bool operator != (const char * psz) const;
   inline bool operator < (const char * psz) const;
   inline bool operator <= (const char * psz) const;
   inline bool operator > (const char * psz) const;
   inline bool operator >= (const char * psz) const;
   id & operator = (const char * psz);


   inline bool operator == (const string & str) const;
   inline bool operator != (const string & str) const;
   inline bool operator < (const string & str) const;
   inline bool operator <= (const string & str) const;
   inline bool operator > (const string & str) const;
   inline bool operator >= (const string & str) const;
   id & operator = (const string & str);


   inline bool operator == (int_ptr i) const;
   inline bool operator != (int_ptr i) const;
   inline bool operator < (int_ptr i) const;
   inline bool operator <= (int_ptr i) const;
   inline bool operator > (int_ptr i) const;
   inline bool operator >= (int_ptr i) const;
   inline id & operator = (int_ptr i);


#if defined(_LP64) || defined(_AMD64_)


   inline bool operator == (int32_t i) const;
   inline bool operator != (int32_t i) const;
   inline bool operator < (int32_t i) const;
   inline bool operator <= (int32_t i) const;
   inline bool operator > (int32_t i) const;
   inline bool operator >= (int32_t i) const;
   inline id & operator = (int32_t i);


#endif


   inline bool operator == (const string_interface & str) const;
   inline bool operator != (const string_interface & str) const;
   inline bool operator < (const string_interface & str) const;
   inline bool operator <= (const string_interface & str) const;
   inline bool operator > (const string_interface & str) const;
   inline bool operator >= (const string_interface & str) const;

   id & operator = (const string_interface & str);
   id & operator = (const var & var);
   id & operator = (const property & prop);


   inline operator int64_t() const;


   inline operator const char *() const;
   inline string & to_string(string & str) const;
   inline string to_string() const;



   inline bool is_null() const;
   inline bool is_empty() const;
   inline bool has_char() const;
   inline void empty();
   inline void clear();


   inline int_ptr CompareNoCase(const char * psz) const { return compare_ci(psz); }
   inline int_ptr compare_ci(const char * psz) const;


   inline bool is_text() const { return m_etype == type_text; }
   inline bool is_integer() const { return m_etype == type_integer; }

};




inline id::id()
{

   m_all = {};

}

inline id::id(const id & id)
{

   m_all = id.m_all;

}

inline id::id(const char * psz,id_space *)
{

   m_all ={};

   m_etype = type_text;
   m_psz    = psz;

}

inline bool id::operator == (const id & id) const
{
   return m_iType == id.m_iType && m_iBody == id.m_iBody;
}

inline bool id::operator != (const id & id) const
{
   return ! operator == (id);
}

inline bool id::operator < (const id & id) const
{
   return m_iType < id.m_iType || ((m_iType == id.m_iType) && m_iBody < id.m_iBody);
}
inline bool id::operator >(const id & id) const
{
   return m_iType > id.m_iType || ((m_iType == id.m_iType) && m_iBody > id.m_iBody);
}
inline bool id::operator <= (const id & id) const
{
   return id > *this;
}
inline bool id::operator >= (const id & id) const
{
   return id < *this;
}

inline id & id::operator = (const id & id)
{
   m_all         = id.m_all;
   return *this;
}


namespace comparison
{


   template < >
   class equals_type_arg_type < id, const id & >
   {
   public:

      inline static bool CompareElements(const id * pElement1, const id & element2)
      {
         return *pElement1 == element2;
      }

   };


   class strid_equals
   {
   public:

      inline static bool CompareElements(const id * pElement1, const id & element2)
      {
         return strcmp(pElement1->m_psz, element2.m_psz) == 0;
      }

   };


   template < >
   class less < id, const id & >
   {
   public:

      inline bool operator()(const id & element1, const id & element2) const
      {
         return element1 < element2;
      }

   };





   class strid_less
   {
   public:

      inline static bool compare(const id & element1, const id & element2)
      {
         return strcmp(element1.m_psz,  element2.m_psz) < 0;
      }

   };











  class CLASS_DECL_AURA strid_hash
   {
   public:

      inline static UINT HashKey(const id & key)
      {
         return (((UINT)key.m_iType) << 24) | (((UINT)key.m_iBody) >> 8);
      }

   };


   template < >
   class CLASS_DECL_AURA hash < id >
   {
   public:

      inline static UINT HashKey(const id & key)
      {
         return strid_hash::HashKey(key);
      }


   };






} // namespace comparison














template <> inline UINT HashKey(const id & id)
{
   // default identity hash - works for most primitive values
   return ::comparison::strid_hash::HashKey(id);
}






