#pragma once

#include "gen_base_enum.h"
#include "ex1/ex1_serializable.h"
#include "gen/gen_variable_strict_compare.h"
#include "gen/gen_holder.h"
#include "gen/gen_raw_pointer.h"
#include "gen/gen_full_pointer.h"
#include "template/time.h"

class stringa;

namespace primitive
{
   class memory;
} // namespace primitive

namespace gen
{
   enum para_return
   {
      e_fail = 0x80000000,
      s_success = 0,
   };

   bool ok(para_return eret);
}

class var_array;

namespace gen
{
   class property;
   class var_property;
   class property_set;
   class pair_set_interface;
   class str_str_interface;
}


class CLASS_DECL_ca var :
   virtual public ex1::serializable,
   virtual public string_interface
{
public:

   enum _etype
   {
      type_parareturn,
      type_new,
      type_null,
      type_empty,
      type_empty_argument,
      type_string,
      type_pstring,
      type_integer,
      type_pinteger,
      type_ulong,
      type_pvar,
      type_ca2,
      type_bool,
      type_pbool,
      type_double,
      type_stra,
      type_inta,
      type_vara,
      type_propset,
      type_prop,
      type_memory,
      type_int64,
      type_pint64,
      type_uint64,
      type_puint64,
      type_time,
      type_filetime,
      type_uint,
   };

   typedef base_enum < _etype, type_null > e_type;

   
   void set_type(e_type e_type);
   virtual e_type get_type() const;

   var();
   var(bool b);
   var(int i);
   var(__int64 i64);
   var(unsigned int ui);
   var(unsigned __int64 ui64);
   var(unsigned long ul);
   var(double d);
   var(const char * psz);
   var(string str);
   var(bool * pb);
   var(int * pi);
   var(__int64 * pi);
   var(unsigned __int64 * pui);
   var(const class ::time & time);
   var(const FILETIME & time);
   var(const SYSTEMTIME & time);
   var(string * pstr);
   var(var * pvar);
   var(::ca::ca * pca2);
   var(const stringa & var);
   var(const int_array & var);
   var(const var_array & var);
   var(const gen::property_set & set);
   var(const var & var);
   var(const gen::property & prop);
   var(const gen::var_property & prop);
   var(const gen::pair_set_interface & set);
   var(const gen::str_str_interface & set);
   virtual ~var();

   e_type             m_etype;
   union
   {
      gen::para_return     m_parareturn;
      int                  m_i;
      __int64              m_i64;
      unsigned __int64     m_ui64;
      int *                m_pi;
      __int64 *            m_pi64;
      unsigned __int64 *   m_pui64;
      bool *               m_pb;
      string *             m_pstr;
      unsigned long        m_ul;
      bool                 m_b;
      double               m_d;
      var *                m_pvar;
      __time64_t           m_time;
      FILETIME             m_filetime;
      unsigned int         m_ui;
   };
   ::ca::ca *                       m_pca2;
   string                           m_str;

   string                           to_r_string() const;
   const string &                   get_ref_string(const char * pszOnNull = NULL)   const;
   string                           get_string(const char * pszOnNull = NULL)   const;
   int                              get_integer(int iDefault = 0)  const;
   unsigned long                    get_ulong()    const;
   double                           get_double()   const;
   bool                             get_bool()     const;
   class primitive::memory &        memory();
   stringa &                        stra();
   int_array &                      inta();
   var_array &                      vara();
   gen::property_set &              propset(::ca::application * papp = NULL);
   gen::property &                  prop();
   const class primitive::memory &  memory() const;
   const stringa &                  stra() const;
   const int_array &                inta() const;
   const var_array &                vara()  const;
   const gen::property_set &        propset() const;
   const gen::property &            prop() const;

   bool is_scalar() const;
   bool is_array() const;
   bool is_double() const;
   bool is_integer() const;
   bool is_ulong() const;

   bool ok() const;
   bool failed() const;


   var dereference();

   virtual void on_delete(::ca::ca * poc);


   variable_strict_compare strict_compare() const;


   void           set_string(const char * psz);
   virtual void unset();

   virtual bool is_true() const;
   

   virtual bool is_set() const;
   virtual bool is_new() const;
   virtual bool is_null() const;
   virtual bool is_new_or_null() const;
   virtual bool is_empty() const;
   virtual bool has_char() const;

   bool has_property(const char * pszName) const;

   var & operator ++(int);

   operator unsigned int();
   operator long();
   operator int();
   operator __int64();
   operator string &();
   operator const char * () const;
   operator ::CFileTime & ();
   operator ::CFileTime () const;
   operator class ::time() const;
   operator bool()
   {
      return m_etype == type_bool && m_b;
   }
   virtual void get_string(char * psz) const;
   virtual int get_length() const;
   var & operator = (::ca::ca * pca2);
   var & operator = (gen::para_return & eret);
   var & operator = (bool b);
   var & operator = (bool * pb);
   var & operator = (int i);
   var & operator = (int * pi);
   var & operator = (__int64 i);
   var & operator = (__int64 * pi);
   var & operator = (unsigned __int64 i);
   var & operator = (unsigned __int64 * pi);
   var & operator = (const class ::time & time);
   var & operator = (const FILETIME & time);
   var & operator = (const SYSTEMTIME & time);
   var & operator = (unsigned long ul);
   var & operator = (unsigned int ui);
   var & operator = (double d);
   var & operator = (string str);
   var & operator = (string * pstr);
   var & operator = (var * pvar);
   var & operator = (const char * psz);
   var & operator = (const wchar_t * lpcsz);
   var & operator = (const gen::property & prop);
   var & operator = (const gen::var_property & prop);
   var & operator = (const var & var);
   var & operator = (const int_array & ia);
   var & operator = (const stringa & stra);
   var & operator = (const class primitive::memory & memory);
   var & operator = (const var_array & vara);
   var & operator = (const gen::property_set & propset);
   var & operator = (const gen::pair_set_interface & propset);
   var & operator = (const gen::str_str_interface & propset);

   template < class T >
   T * ca2()
   {
      if(m_etype != type_ca2 || m_pca2 == NULL)
         return NULL;
      return dynamic_cast < T * > (m_pca2);
   }

   template < class T >
   const T * ca2() const
   {
      if(m_etype != type_ca2 || m_pca2 == NULL)
         return NULL;
      return dynamic_cast < T * > (m_pca2);
   }

   bool strict_equal(const var & var) const;
   bool strict_equal(const char * psz) const;
   bool strict_equal(const string & str) const;
   bool strict_equal(double d) const;
   bool strict_equal(int i) const;
   bool strict_equal(bool b) const;
   
   bool strict_different(const var & var) const;
   bool strict_different(const char * psz) const;
   bool strict_different(const string & str) const;
   bool strict_different(double d) const;
   bool strict_different(int i) const;
   bool strict_different(bool b) const;

   friend bool CLASS_DECL_ca strict_equal(const char * psz, const var & var);
   friend bool CLASS_DECL_ca strict_equal(const string & str, const var & var);
   friend bool CLASS_DECL_ca strict_equal(double d, const var & var);
   friend bool CLASS_DECL_ca strict_equal(int i, const var & var);
   friend bool CLASS_DECL_ca strict_equal(bool b, const var & var);

   friend bool CLASS_DECL_ca strict_different(const char * psz, const var & var);
   friend bool CLASS_DECL_ca strict_different(const string & str, const var & var);
   friend bool CLASS_DECL_ca strict_different(double d, const var & var);
   friend bool CLASS_DECL_ca strict_different(int i, const var & var);
   friend bool CLASS_DECL_ca strict_different(bool b, const var & var);

   int compare(const var & var) const;
   int compare(const char * psz) const;

   int compare_ci(const var & var) const;
   int compare_ci(const char * psz) const;

   bool operator == (const var & var) const;
   bool operator == (const char * psz) const;
   bool operator == (const string & str) const;
   bool operator == (int i) const;
   bool operator == (bool b) const;

   bool operator != (const var & var) const;
   bool operator != (const char * psz) const;
   bool operator != (const string & str) const;
   bool operator != (int i) const;
   bool operator != (bool b) const;

   bool operator < (const var & var) const;
   bool operator < (const char * psz) const;
   bool operator < (const string & str) const;
   bool operator < (int i) const;
   bool operator < (bool b) const;

   bool operator <= (const var & var) const;
   bool operator <= (const char * psz) const;
   bool operator <= (const string & str) const;
   bool operator <= (int i) const;
   bool operator <= (bool b) const;

   bool operator >= (const var & var) const;
   bool operator >= (const char * psz) const;
   bool operator >= (const string & str) const;
   bool operator >= (int i) const;
   bool operator >= (bool b) const;

   bool operator > (const var & var) const;
   bool operator > (const char * psz) const;
   bool operator > (const string & str) const;
   bool operator > (int i) const;
   bool operator > (bool b) const;

   void write(ex1::output_stream & ostream);
   void read(ex1::input_stream & ostream);

   string implode(const char * pszGlue) const;

   var first() const;
   var last() const;
   int get_count() const;
   const var & operator[] (var varKey) const;
   const var & operator[] (const char * pszKey) const;
   const var & operator[] (int iKey) const;
   var & operator[] (var varKey);
   var & operator[] (const char * pszKey);
   var & operator[] (int iKey);
   var at(int i) const;
   var key(int i) const;
   int array_get_count() const;
   int array_get_upper_bound() const;
   bool array_contains(const char * psz, index find = 0, count count = -1) const;
   bool array_contains_ci(const char * psz, index find = 0, count count = -1) const;

   var equals_ci_get(const char * pszCompare, var varOnEqual, var varOnDifferent) const;
   var equals_ci_get(const char * pszCompare, var varOnEqual) const;


   string operator + (const char * psz) const;
   string operator + (const string & str) const;

   friend string CLASS_DECL_ca operator + (const char * psz, const var & var);
   friend string CLASS_DECL_ca operator + (const string & str, const var & var);

   var operator - (int i) const;
   var operator - (unsigned int user) const;
   var operator - (long i) const;
   var operator - (unsigned long user) const;
   var operator - (double d) const;

   friend var CLASS_DECL_ca operator - (int i, const var & var);
   friend var CLASS_DECL_ca operator - (unsigned int user, const var & var);
   friend var CLASS_DECL_ca operator - (long l, const var & var);
   friend var CLASS_DECL_ca operator - (unsigned long ul, const var & var);
   friend var CLASS_DECL_ca operator - (double d, const var & var);
   friend var CLASS_DECL_ca operator - (const var & var1, const var & var2);

   var operator + (int i) const;
   var operator + (unsigned int user) const;
   var operator + (long i) const;
   var operator + (unsigned long user) const;
   var operator + (double d) const;

   friend var CLASS_DECL_ca operator + (int i, const var & var);
   friend var CLASS_DECL_ca operator + (unsigned int user, const var & var);
   friend var CLASS_DECL_ca operator + (long l, const var & var);
   friend var CLASS_DECL_ca operator + (unsigned long ul, const var & var);
   friend var CLASS_DECL_ca operator + (double d, const var & var);
   friend var CLASS_DECL_ca operator + (const var & var1, const var & var2);

   var operator / (int i) const;
   var operator / (unsigned int user) const;
   var operator / (long i) const;
   var operator / (unsigned long user) const;
   var operator / (double d) const;

   friend var CLASS_DECL_ca operator / (int i, const var & var);
   friend var CLASS_DECL_ca operator / (unsigned int user, const var & var);
   friend var CLASS_DECL_ca operator / (long l, const var & var);
   friend var CLASS_DECL_ca operator / (unsigned long ul, const var & var);
   friend var CLASS_DECL_ca operator / (double d, const var & var);
   friend var CLASS_DECL_ca operator / (const var & var1, const var & var2);

   var operator * (int i) const;
   var operator * (unsigned int user) const;
   var operator * (long i) const;
   var operator * (unsigned long user) const;
   var operator * (double d) const;

   friend var CLASS_DECL_ca operator * (int i, const var & var);
   friend var CLASS_DECL_ca operator * (unsigned int user, const var & var);
   friend var CLASS_DECL_ca operator * (long l, const var & var);
   friend var CLASS_DECL_ca operator * (unsigned long ul, const var & var);
   friend var CLASS_DECL_ca operator * (double d, const var & var);
   friend var CLASS_DECL_ca operator * (const var & var1, const var & var2);

   var & operator -= (int i);
   var & operator -= (unsigned int user);
   var & operator -= (long i);
   var & operator -= (unsigned long user);
   var & operator -= (double d);
   var & operator -= (const var & var);

   var & operator += (int i);
   var & operator += (unsigned int user);
   var & operator += (long i);
   var & operator += (unsigned long user);
   var & operator += (double d);
   var & operator += (const var & var);

   var & operator /= (int i);
   var & operator /= (unsigned int user);
   var & operator /= (long i);
   var & operator /= (unsigned long user);
   var & operator /= (double d);
   var & operator /= (const var & var);

   var & operator *= (int i);
   var & operator *= (unsigned int user);
   var & operator *= (long i);
   var & operator *= (unsigned long user);
   var & operator *= (double d);
   var & operator *= (const var & var);

};

