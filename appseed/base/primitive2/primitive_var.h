#pragma once


class stringa;

namespace primitive
{

   class memory;

} // namespace primitive

enum para_return
{
   e_fail = 0x80000000,
   s_success = 0
};

bool is_return_ok(para_return eret);



class CLASS_DECL_BASE var
{
public:

   enum e_type
   {
      type_parareturn,
      type_new,
      type_null,
      type_empty,
      type_empty_argument,
      type_string,
      type_pstring,
      type_int32,
      type_pint32,
      type_uint32,
      type_puint32,
      type_int64,
      type_pint64,
      type_uint64,
      type_puint64,
      type_float,
      type_double,
      type_pvar,
      type_element,
      type_bool,
      type_pbool,
      type_stra,
      type_inta,
      type_vara,
      type_propset,
      type_prop,
      type_memory,
      type_time,
      type_filetime,
      type_id,
      type_pid,
      type_int64a,
      type_char,
      type_byte,
      type_duration,
      type_pduration
   };

   e_type             m_etype;
   union
   {
      void               * m_p;
      para_return          m_parareturn;
      bool                 m_b;
      bool *               m_pb;
      int32_t              m_i32;
      uint32_t             m_ui32;
      int64_t              m_i64;
      uint64_t             m_ui64;
      int32_t *            m_pi32;
      uint32_t *           m_pui32;
      int64_t *            m_pi64;
      uint64_t *           m_pui64;
      string *             m_pstr;
      float                m_f;
      double               m_d;
      var *                m_pvar;
      __time64_t           m_time;
      FILETIME             m_filetime;
      id *                 m_pid;
      int_array *          m_pia;
      stringa *            m_pstra;
      int64_array *        m_pia64;
      var_array *          m_pvara;
      property_set *       m_pset;
      property *           m_pprop;
      uchar                m_uch;
      char                 m_ch;
      class duration       m_duration;
      class duration *     m_pduration;
   };


   sp(element)                      m_sp;
   string                           m_str;
   id                               m_id;


   inline var();
   inline var(e_type etype);
   var(bool b);
   var(int32_t i);
   var(uint32_t ui);
   var(int64_t i);
   var(uint64_t ui);
#ifdef APPLEOS
#ifdef OS64BIT
   var(long l);
#endif
#endif
   var(int32_t * pi);
   var(uint32_t * pi);
   var(int64_t * pi);
   var(uint64_t * pui);
//   var(int64_t l);
//   var(uint64_t ul);
//   var(int64_t int64_t ll);
//   var(uint64_t int64_t ull);
   var(float f);
   var(double d);
   var(const char * psz);
   var(string str);
   var(const id & id);
   var(bool * pb);
   var(const ::datetime::time & time);
   var(const FILETIME & time);
   var(const SYSTEMTIME & time);
   var(string * pstr);
   var(var * pvar);
   var(element * pca2);
   var(const stringa & var);
   var(const int_array & var);
   var(const var_array & var);
   var(const property_set & set);
   var(const var & var);
   var(const property & prop);
   var(const pair_set_interface & set);
   var(const str_str_interface & set);
   var(const string_composite & composite);
   var(const class duration & duration);
   var(class duration * pduration);
//#if defined(MOVE_SEMANTICS)
  // inline var(var && v);
//#endif
   template < class T >
   var(const sp(T) & sp)
   {
      m_etype = type_new;
      operator = (sp.m_p);
   }

   ~var();

   void set_type(e_type e_type, bool bConvert = true);
   e_type get_type() const;

   bool is_numeric() const;

   inline bool is_number() const
   {

      return is_numeric();

   }




   bool                             get_bool(bool bDefault = false)     const;
   int32_t                          int32(int32_t iDefault = 0)  const;
   uint32_t                         uint32(uint32_t uiDefault = 0)  const;
   int64_t                          int64(int64_t iDefault = 0)  const;
   uint64_t                         uint64(uint64_t uiDefault = 0)  const;
   inline int_ptr                   intptr(int_ptr iDefault = 0)  const;
   inline uint_ptr                  uintptr(uint_ptr uiDefault = 0)  const;
   float                            get_float(float fDefault = 0.f)   const;
   double                           get_double(double dDefault = 0.0)   const;
   string                           to_r_string() const;
   string                           get_string(const char * pszOnNull = NULL) const;
   string &                         get_ref_string(const char * pszOnNull = NULL);
   string                           to_string() const;
   id                               get_id(const char * pszOnNull = NULL)   const;
   id &                             get_ref_id(const char * pszOnNull = NULL);
   class primitive::memory &        memory();
   stringa &                        stra();
   int_array &                      inta();
   int64_array &                    int64a();
   var_array &                      vara();
   class duration &                 duration();
   property_set &                   propset(sp(::axis::application) papp = NULL);
   property &                       prop();
   const class primitive::memory &  memory() const;
   const stringa &                  stra() const;
   const int_array &                inta() const;
   const int64_array &              int64a() const;
   const var_array &                vara()  const;
   const property_set &             propset() const;
   const property &                 prop() const;
   const class duration &           duration() const;

   bool is_scalar() const;
   inline bool is_array() const;
   bool is_real() const;
   bool is_integer() const;
   bool is_natural() const;

   bool is_double() const;
   bool is_duration() const;

   bool ok() const;
   bool failed() const;


   var dereference();


   ::comparison::var_strict strict_compare() const;


   void           set_string(const string & str);
   void           set_id(const id & id);
   void unset();

   bool is_true(bool bDefault = false) const;


   bool is_set() const;
   bool is_new() const;
   bool is_null() const;
   bool is_new_or_null() const;
   bool is_empty() const;
   bool has_char() const;

   bool has_property(const char * pszName) const;

   var & operator ++(int32_t);

   operator bool() const
   {
      return m_etype == type_bool && m_b;
   }

   operator int32_t() const;
#ifdef WINDOWS
   operator LONG() const;
#endif
   operator uint32_t() const;
   operator int64_t() const;
   operator uint64_t() const;
   operator class duration() const;

   //operator string & ();
   //operator id &();
   operator const char * () const;
   //operator ::file_time & ();

   operator string & ()
   {

      if(m_etype == var::type_pstring)
      {

         return *m_pstr;

      }
      else if(m_etype != var::type_string)
      {

         m_str = get_string();

      }

      return m_str;

   }

   operator ::datetime::file_time () const;

   operator ::datetime::time() const;

   void get_string(char * psz) const;

   strsize get_length() const;

/*   template < class T >
   var & operator = (sp(T) p)
   {
      set_type(type_element, false);
      m_sp = p;
      return *this;
   }
*/
   inline var & operator = (element * p)
   {
      set_type(type_element, false);
      m_sp = p;
      return *this;
   }

   var & operator = (para_return & eret);
   var & operator = (bool b);
   var & operator = (bool * pb);
   var & operator = (int32_t i);
   var & operator = (int32_t * pi);
   var & operator = (uint32_t ui);
   var & operator = (uint32_t * pui);
#ifdef WINDOWS
   var & operator = (LPDWORD pui);
#endif
   var & operator = (int64_t i);
   var & operator = (int64_t * pi);
   var & operator = (uint64_t i);
   var & operator = (uint64_t * pi);
   var & operator = (float f);
   var & operator = (double d);
   var & operator = (const ::datetime::time & time);
   var & operator = (const FILETIME & time);
   var & operator = (const SYSTEMTIME & time);
   var & operator = (string str);
   var & operator = (string * pstr);
   var & operator = (var * pvar);
   var & operator = (const char * psz);
   var & operator = (const wchar_t * lpcsz);
   var & operator = (const property & prop);
   var & operator = (const var & var);
   var & operator = (const int_array & ia);
   var & operator = (const stringa & stra);
   var & operator = (const class primitive::memory & memory);
   var & operator = (const var_array & vara);
   var & operator = (const property_set & propset);
   var & operator = (const pair_set_interface & propset);
   var & operator = (const str_str_interface & propset);
   var & operator = (const string_composite & composite);
   var & operator = (const id & id);
   var & operator = (id * pid);
   var & operator = (const class duration & pid);
   var & operator = (class duration * pduration);
//#ifdef MOVE_SEMANTICS
   //inline var & operator = (var && v);
//#endif


   template < class T >
   var & operator = (const sp(T) & sp)
   {

      return this->operator = (sp.m_p);

   }

   template < class T >
   sp(T) cast(T * pDefault)
   {
      
      if(m_etype == type_pvar && m_pvar != NULL)
         return m_pvar->cast < T > (pDefault);
      
      if(m_etype != type_element)
         return NULL;
      
      sp(T) p = m_sp;
      
      if (p.is_null())
         return pDefault;

      return p;

   }


   template < class T >
   sp(T) cast(T * pDefault) const
   {
      return ((var *) this)->cast < T >(pDefault);
   }


   template < class T >
   sp(T) cast()
   {

      if(m_etype == type_pvar && m_pvar != NULL)
         return m_pvar->cast < T >();

      if(m_etype != type_element)
         return NULL;

      sp(T) p = m_sp;

      if(p.is_null())
         return NULL;

      return p;

   }


   template < class T >
   sp(T) cast() const
   {
      return ((var *) this)->cast < T >();
   }


   bool strict_equal(const var & var) const;
   bool strict_equal(const char * psz) const;
   bool strict_equal(const string & str) const;
   bool strict_equal(double d) const;
   bool strict_equal(int32_t i) const;
   bool strict_equal(bool b) const;

   bool strict_different(const var & var) const;
   bool strict_different(const char * psz) const;
   bool strict_different(const string & str) const;
   bool strict_different(double d) const;
   bool strict_different(int32_t i) const;
   bool strict_different(bool b) const;

   friend bool CLASS_DECL_BASE strict_equal(const char * psz, const var & var);
   friend bool CLASS_DECL_BASE strict_equal(const string & str, const var & var);
   friend bool CLASS_DECL_BASE strict_equal(double d, const var & var);
   friend bool CLASS_DECL_BASE strict_equal(int32_t i, const var & var);
   friend bool CLASS_DECL_BASE strict_equal(bool b, const var & var);

   friend bool CLASS_DECL_BASE strict_different(const char * psz, const var & var);
   friend bool CLASS_DECL_BASE strict_different(const string & str, const var & var);
   friend bool CLASS_DECL_BASE strict_different(double d, const var & var);
   friend bool CLASS_DECL_BASE strict_different(int32_t i, const var & var);
   friend bool CLASS_DECL_BASE strict_different(bool b, const var & var);

   int32_t compare(const var & var) const;
   int32_t compare(const char * psz) const;

   int32_t compare_ci(const var & var) const;
   int32_t compare_ci(const char * psz) const;

   bool operator == (const var & var) const;
   bool operator == (const char * psz) const;
   bool operator == (const string & str) const;
   bool operator == (int32_t i) const;
   bool operator == (bool b) const;

   bool operator != (const var & var) const;
   bool operator != (const char * psz) const;
   bool operator != (const string & str) const;
   bool operator != (int32_t i) const;
   bool operator != (bool b) const;

   bool operator < (const var & var) const;
   bool operator < (const char * psz) const;
   bool operator < (const string & str) const;
   bool operator < (int32_t i) const;
   bool operator < (bool b) const;

   bool operator <= (const var & var) const;
   bool operator <= (const char * psz) const;
   bool operator <= (const string & str) const;
   bool operator <= (int32_t i) const;
   bool operator <= (bool b) const;

   bool operator >= (const var & var) const;
   bool operator >= (const char * psz) const;
   bool operator >= (const string & str) const;
   bool operator >= (int32_t i) const;
   bool operator >= (bool b) const;

   bool operator > (const var & var) const;
   bool operator > (const char * psz) const;
   bool operator > (const string & str) const;
   bool operator > (int32_t i) const;
   bool operator > (bool b) const;

   void write(::file::output_stream & ostream);
   void read(::file::input_stream & ostream);

   string implode(const char * pszGlue) const;
   var explode(const char * pszGlue, bool bAddEmpty = true) const;

   var first() const;
   var last() const;
   inline ::count get_count() const;
   const var & operator[] (var varKey) const;
   const var & operator[] (string strKey) const;
   const var & operator[] (const char * pszKey) const;
   const var & operator[] (id idKey) const;
   const var & operator[] (index iKey) const;
   var & operator[] (var varKey);
   var & operator[] (string strKey);
   var & operator[] (const char * pszKey);
   var & operator[] (id idKey);
   var & operator[] (index iKey);
   var at(index i) const;
   var at(index i);
   var key(index i) const;
#if OSBIT != 32
   inline const var & operator[] (int32_t iKey) const { return operator[]((index) iKey); }
   inline var & operator[] (int32_t iKey) { return operator[]((index) iKey); }
   inline var at(int32_t i) const { return at((index) i); }
   inline var at(int32_t i) { return at((index) i); }
   inline var key(int32_t i) const { return key((index) i); }
#endif
   inline ::count array_get_count() const;
   inline index array_get_upper_bound() const;
   bool array_contains(const char * psz, index find = 0, ::count count = -1) const;
   bool array_contains_ci(const char * psz, index find = 0, ::count count = -1) const;

   var equals_ci_get(const char * pszCompare, var varOnEqual, var varOnDifferent) const;
   var equals_ci_get(const char * pszCompare, var varOnEqual) const;


   var operator - (int32_t i) const;
   var operator - (uint32_t ui) const;
   var operator - (int64_t i) const;
   var operator - (uint64_t ui) const;
   var operator - (double d) const;

   friend var CLASS_DECL_BASE operator - (int32_t i, const var & var);
   friend var CLASS_DECL_BASE operator - (uint32_t ui, const var & var);
   friend var CLASS_DECL_BASE operator - (int64_t l, const var & var);
   friend var CLASS_DECL_BASE operator - (uint64_t ul, const var & var);
   friend var CLASS_DECL_BASE operator - (double d, const var & var);
   friend var CLASS_DECL_BASE operator - (const var & var1, const var & var2);

   var operator + (int32_t i) const;
   var operator + (uint32_t ui) const;
   var operator + (int64_t i) const;
   var operator + (uint64_t ui) const;
   var operator + (double d) const;

   friend var CLASS_DECL_BASE operator + (int32_t i, const var & var);
   friend var CLASS_DECL_BASE operator + (uint32_t ui, const var & var);
   friend var CLASS_DECL_BASE operator + (int64_t l, const var & var);
   friend var CLASS_DECL_BASE operator + (uint64_t ul, const var & var);
   friend var CLASS_DECL_BASE operator + (double d, const var & var);
   friend var CLASS_DECL_BASE operator + (const var & var1, const var & var2);

   var operator / (int32_t i) const;
   var operator / (uint32_t ui) const;
   var operator / (int64_t i) const;
   var operator / (uint64_t ui) const;
   var operator / (double d) const;

   friend var CLASS_DECL_BASE operator / (int32_t i, const var & var);
   friend var CLASS_DECL_BASE operator / (uint32_t ui, const var & var);
   friend var CLASS_DECL_BASE operator / (int64_t l, const var & var);
   friend var CLASS_DECL_BASE operator / (uint64_t ul, const var & var);
   friend var CLASS_DECL_BASE operator / (double d, const var & var);
   friend var CLASS_DECL_BASE operator / (const var & var1, const var & var2);

   var operator * (int32_t i) const;
   var operator * (uint32_t ui) const;
   var operator * (int64_t i) const;
   var operator * (uint64_t ui) const;
   var operator * (double d) const;

   friend var CLASS_DECL_BASE operator * (int32_t i, const var & var);
   friend var CLASS_DECL_BASE operator * (uint32_t ui, const var & var);
   friend var CLASS_DECL_BASE operator * (int64_t l, const var & var);
   friend var CLASS_DECL_BASE operator * (uint64_t ul, const var & var);
   friend var CLASS_DECL_BASE operator * (double d, const var & var);
   friend var CLASS_DECL_BASE operator * (const var & var1, const var & var2);

   var & operator -= (int32_t i);
   var & operator -= (uint32_t ui);
   var & operator -= (int64_t i);
   var & operator -= (uint64_t ui);
   var & operator -= (double d);
   var & operator -= (const var & var);

   var & operator += (int32_t i);
   var & operator += (uint32_t ui);
   var & operator += (int64_t i);
   var & operator += (uint64_t ui);
   var & operator += (double d);
   var & operator += (const var & var);

   var & operator /= (int32_t i);
   var & operator /= (uint32_t ui);
   var & operator /= (int64_t i);
   var & operator /= (uint64_t ui);
   var & operator /= (double d);
   var & operator /= (const var & var);

   var & operator *= (int32_t i);
   var & operator *= (uint32_t ui);
   var & operator *= (int64_t i);
   var & operator *= (uint64_t ui);
   var & operator *= (double d);
   var & operator *= (const var & var);

   void consume_number(const char * & psz);
   void consume_number(const char * & psz, const char * pszEnd);
   void consume_identifier(const char * & psz);
   void consume_identifier(const char * & psz, const char * pszEnd);
   void parse_json(const char * & pszJson);
   void parse_json(const char * & pszJson, const char * pszEnd);

   string get_json();


//#undef new
  // DECLARE_BASE_FIXED_ALLOC(var)

    void null();

};


namespace str
{


   inline CLASS_DECL_BASE string from(const var & var)
   {

      return var.get_string();

   }


} // namespace str


inline string CLASS_DECL_BASE operator+ (const char * psz, const var & var)
{

   string strResult(psz);

   strResult += var.get_string();

   return strResult;
}


inline string CLASS_DECL_BASE operator+ (const var & var, const char * psz)
{

   string strResult(var.get_string());

   strResult += psz;

   return strResult;
}


inline string CLASS_DECL_BASE operator+ (const string & str, const var & var)
{

   string strResult(str);

   strResult += var.get_string();

   return strResult;
}


inline string CLASS_DECL_BASE operator+ (const var & var, const string & str)
{

   string strResult(var.get_string());

   strResult += str;

   return strResult;
}


inline bool var::get_bool(bool bDefault) const
{
   return is_true(bDefault);
}

// returns 0 for unknown conversions
inline var::operator int32_t() const
{
   return int32();
}

// returns 0 for unknown conversions
inline var::operator uint32_t() const
{
   return uint32();
}

// returns 0 for unknown conversions
inline var::operator int64_t() const
{
   return int64();
}

// returns 0 for unknown conversions
inline var::operator uint64_t() const
{
   return uint64();
}

inline var::operator class duration() const
{
   return duration();
}

inline int_ptr var::intptr(int_ptr iDefault) const
{

#if defined(OS64BIT)

   return int64(iDefault);

#else

   return int32(iDefault);

#endif

}

inline uint_ptr var::uintptr(uint_ptr uiDefault) const
{

#ifdef OS64BIT

   return uint64(uiDefault);

#else

   return uint32(uiDefault);

#endif

}


#ifdef WINDOWS

inline var::operator LONG () const
{

	return operator int32_t();

}

inline var & var::operator = (LPDWORD pui)
{

	return operator = ((uint32_t *) pui);

}

#endif


inline string var::to_string() const
{
   return get_string();
}


inline string::string(const var & var) :
   simple_string(string_trait::GetDefaultManager())
{

   operator = (var.to_string());

}


inline string & string::operator = (const var & var)
{

   return operator = (var.to_string());

}


inline string  & operator += (string & str, const var & var)
{

   str += var.get_string();

   return str;

}


/*#ifdef MOVE_SEMANTICS


inline var::var(var && v)
{

   memcpy(this, &v, sizeof(var));

   v.m_sp.m_p           = NULL;
   v.m_str.m_pszData    = NULL;
   v.m_id.m_pstr        = NULL;

}


#endif

#ifdef MOVE_SEMANTICS
inline var & var::operator = (var && v)
{

   if(this != &v)
   {

      m_sp.release();
      m_str.~string();
      m_id.~id();

      memcpy(this, &v, sizeof(var));

      v.m_sp.m_p           = NULL;
      v.m_str.m_pszData    = NULL;
      v.m_id.m_pstr        = NULL;

   }

   return *this;

}

#endif
*/

