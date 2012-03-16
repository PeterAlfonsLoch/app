#pragma once


#include "gen/gen_signal.h"
#include "gen_var_array.h"


namespace xml
{


   class disp_option;


} // namespace xml


namespace gen
{


   class CLASS_DECL_ca pair_set_interface
   {
   public:


      pair_set_interface();


      virtual bool get_auto_add() const;
      virtual bool get_key_case_insensitive() const;


      virtual void pair_set_interface_set(const char * pszKey, var value) = 0;
      virtual var pair_set_interface_get_value(int i) const = 0;
      virtual var & pair_set_interface_get_value(int i) = 0;
      virtual const string_composite pair_set_interface_get_key(int i) const = 0;
      virtual int pair_set_interface_get_count() const = 0;
      virtual int pair_set_interface_find(const char * pszKey, int iStart = 0) const;
      var operator[](const char * pszName) const;
      var & operator[](const char * pszName);
   };

   class CLASS_DECL_ca str_str_interface
   {
   public:

      str_str_interface();


      virtual bool get_auto_add() const;
      virtual bool get_key_case_insensitive() const;

      virtual void str_str_interface_set(const char * pszKey, const char * pszValue) = 0;
      virtual const string_composite str_str_interface_get_value(int i) const = 0;
      virtual string_composite str_str_interface_get_value(int i) = 0;
      virtual const string_composite str_str_interface_get_key(int i) const = 0;
      virtual int str_str_interface_get_count() const = 0;
      virtual int str_str_interface_find(const char * pszKey, int iStart = 0) const;
      const string_composite operator[](const char * pszName) const;
      string_composite operator[](const char * pszName);
      virtual bool contains_key(stringa & stra);
   };

   class property_set;
   class var_property_array;


   class CLASS_DECL_ca property :
      public ::radix::object,
      public ex1::byte_serializable,
      public string_interface
   {
   public:


      string            m_strName;
      property_set *    m_pset;
      var               m_var;


      property();
      property(const property & prop);
      property(const char * pszName);
      property(index iIndex);
      property(const char * pszName, var & var);
      ~property(void);

      inline string & name()
      {
         return m_strName;
      }
      inline string name() const
      {
         return m_strName;
      }

      stringa & stra();
      int_array & inta();
      var_array & vara();
      property_set & propset();
      const stringa & stra() const;
      const int_array & inta() const;
      const var_array & vara() const;
      const property_set & propset() const;
      inline void get_string(char * psz) const;
      inline strsize get_length() const;

      string get_xml(::xml::disp_option * opt = ((::xml::disp_option *) 1));


      property & operator[](const char * pszName);
      property & operator[](index iIndex);

      inline var & get_value()
      {
         return m_var;
      }
      inline var get_value() const
      {
         return m_var;
      }
      inline void set_value(const var & var)
      {
         m_var = var;
      }
      inline void unset();

      inline void   get_value(var & value);
      inline void   get(var & value);
      inline var &  get();
      inline void   set(const var & var);



      int get_integer(int iDefault = 0)
      {
         return get_value().get_integer(iDefault);
      }

      int get_integer(int iDefault = 0) const
      {
         return get_value().get_integer(iDefault);
      }

      double get_double()
      {
         return get_value().get_double();
      }

      double get_double() const
      {
         return get_value().get_double();
      }

      bool get_bool()
      {
         return get_value().get_bool();
      }

      bool get_bool() const
      {
         return get_value().get_bool();
      }

      string get_string()
      {
         return get_value().get_string();
      }

      string get_string() const
      {
         return get_value().get_string();
      }

      void set_string(const char * psz)
      {
         get_value() = psz;
      }

      property & operator++(int)
      {
         get_value()++;
         return *this;
      }

      property & operator =(const property & prop);

      property & operator =(const var & var)
      {
         get_value() = var;
         return *this;
      }

      property & operator =(const char * psz)
      {
         get_value() = psz;
         return *this;
      }

      property & operator =(string str)
      {
         get_value() = str;
         return *this;
      }

      property & operator =(const id & id)
      {
         get_value() = id;
         return *this;
      }

      property & operator =(double d)
      {
         get_value() = d;
         return *this;
      }

      property & operator =(int i)
      {
         get_value() = i;
         return *this;
      }

      property & operator =(__int64 i)
      {
         get_value() = i;
         return *this;
      }

      property & operator =(bool b)
      {
         get_value() = b;
         return *this;
      }

      property & operator =(::ca::ca * pca2)
      {
         get_value() = pca2;
         return *this;
      }

      template < class T >
      T * ca2()
      {
         return get_value().ca2 < T >();
      }

      operator const char *()
      {
         get_value().m_str = get_value().get_string();
         return get_value().m_str;
      }

      operator string &()
      {
         get_value().m_str = get_value().get_string();
         return get_value().m_str;
      }

      operator string()
      {
         return get_value().get_string();
      }

      operator double()
      {
         return get_value().get_double();
      }

      operator int()
      {
         return get_value().get_integer();
      }

      operator __int64()
      {
         return get_value().get_integer();
      }

      operator bool()
      {
         return get_value().operator bool();
      }

      var equals_ci_get(const char * pszCompare, var varOnEqual, var varOnDifferent) const;
      var equals_ci_get(const char * pszCompare, var varOnEqual) const;


      count get_count() const;
      count array_get_count() const;
      bool array_contains(const char * psz, index first = 0, index last = -1) const;
      bool array_contains_ci(const char * psz, index first = 0, index last = -1) const;


      bool is_set() const;
      bool is_new() const;
      bool is_null() const;
      bool is_new_or_null() const;
      bool is_empty() const;
      bool is_true() const;

      inline string implode(const char * pszGlue) const;

      var element_at(index iIndex) const;
      var at(index iIndex) const;

      int compare_value_ci(const char * psz) const;

      variable_strict_compare strict_compare() const;

      int str_compare(const property & prop) const;


      bool strict_equal(const property & prop) const;
      bool strict_equal(const var & var) const;
      bool strict_equal(const char * psz) const;
      bool strict_equal(const string & str) const;
      bool strict_equal(double d) const;
      bool strict_equal(int i) const;
      bool strict_equal(bool b) const;

      bool strict_different(const property & prop) const;
      bool strict_different(const var & var) const;
      bool strict_different(const char * psz) const;
      bool strict_different(const string & str) const;
      bool strict_different(double d) const;
      bool strict_different(int i) const;
      bool strict_different(bool b) const;

      bool operator == (const property & prop) const;
      bool operator == (const var & var) const;
      bool operator == (const char * psz) const;
      bool operator == (const string & str) const;
      bool operator == (int i) const;
      bool operator == (bool b) const;

      bool operator != (const property & prop) const;
      bool operator != (const var & var) const;
      bool operator != (const char * psz) const;
      bool operator != (const string & str) const;
      bool operator != (int i) const;
      bool operator != (bool b) const;

      bool operator < (const property & prop) const;
      bool operator < (const var & var) const;
      bool operator < (const char * psz) const;
      bool operator < (const string & str) const;
      bool operator < (int i) const;
      bool operator < (bool b) const;

      bool operator <= (const property & prop) const;
      bool operator <= (const var & var) const;
      bool operator <= (const char * psz) const;
      bool operator <= (const string & str) const;
      bool operator <= (int i) const;
      bool operator <= (bool b) const;

      bool operator >= (const property & prop) const;
      bool operator >= (const var & var) const;
      bool operator >= (const char * psz) const;
      bool operator >= (const string & str) const;
      bool operator >= (int i) const;
      bool operator >= (bool b) const;

      bool operator > (const property & prop) const;
      bool operator > (const var & var) const;
      bool operator > (const char * psz) const;
      bool operator > (const string & str) const;
      bool operator > (int i) const;
      bool operator > (bool b) const;

      void write(ex1::byte_output_stream & ostream);
      void read(ex1::byte_input_stream & ostream);


      string operator + (const char * psz) const;
      string operator + (const string & str) const;

      friend string CLASS_DECL_ca operator + (const char * psz, const property & var);
      friend string CLASS_DECL_ca operator + (const string & str, const property & var);

      var operator - (int i) const;
      var operator - (unsigned int user) const;
      var operator - (long i) const;
      var operator - (unsigned long user) const;
      var operator - (double d) const;
      var operator - (const var & var) const;

      friend var CLASS_DECL_ca operator - (int i, const property & prop);
      friend var CLASS_DECL_ca operator - (unsigned int user, const property & prop);
      friend var CLASS_DECL_ca operator - (long l, const property & prop);
      friend var CLASS_DECL_ca operator - (unsigned long ul, const property & prop);
      friend var CLASS_DECL_ca operator - (double d, const property & prop);
      friend var CLASS_DECL_ca operator - (const var & var, const property & prop);
      friend var CLASS_DECL_ca operator - (const property & prop1, const property & prop2);

      var operator + (int i) const;
      var operator + (unsigned int user) const;
      var operator + (long i) const;
      var operator + (unsigned long user) const;
      var operator + (double d) const;
      var operator + (const var & var) const;

      friend var CLASS_DECL_ca operator + (int i, const property & prop);
      friend var CLASS_DECL_ca operator + (unsigned int user, const property & prop);
      friend var CLASS_DECL_ca operator + (long l, const property & prop);
      friend var CLASS_DECL_ca operator + (unsigned long ul, const property & prop);
      friend var CLASS_DECL_ca operator + (double d, const property & prop);
      friend var CLASS_DECL_ca operator + (const var & var, const property & prop);
      friend var CLASS_DECL_ca operator + (const property & prop1, const property & prop2);

      var operator / (int i) const;
      var operator / (unsigned int user) const;
      var operator / (long i) const;
      var operator / (unsigned long user) const;
      var operator / (double d) const;
      var operator / (const var & var) const;

      friend var CLASS_DECL_ca operator / (int i, const property & prop);
      friend var CLASS_DECL_ca operator / (unsigned int user, const property & prop);
      friend var CLASS_DECL_ca operator / (long l, const property & prop);
      friend var CLASS_DECL_ca operator / (unsigned long ul, const property & prop);
      friend var CLASS_DECL_ca operator / (double d, const property & prop);
      friend var CLASS_DECL_ca operator / (const var & var, const property & prop);
      friend var CLASS_DECL_ca operator / (const property & prop1, const property & prop2);

      var operator * (int i) const;
      var operator * (unsigned int user) const;
      var operator * (long i) const;
      var operator * (unsigned long user) const;
      var operator * (double d) const;
      var operator * (const var & var) const;

      friend CLASS_DECL_ca var operator * (int i, const property & prop);
      friend CLASS_DECL_ca var operator * (unsigned int user, const property & prop);
      friend CLASS_DECL_ca var operator * (long l, const property & prop);
      friend CLASS_DECL_ca var operator * (unsigned long ul, const property & prop);
      friend CLASS_DECL_ca var operator * (double d, const property & prop);
      friend CLASS_DECL_ca var operator * (const var & var, const property & prop);
      friend CLASS_DECL_ca var operator * (const property & prop1, const property & prop2);

      property & operator -= (int i);
      property & operator -= (unsigned int user);
      property & operator -= (long i);
      property & operator -= (unsigned long user);
      property & operator -= (double d);
      property & operator -= (const var & var);
      property & operator -= (const property & prop);

      property & operator += (int i);
      property & operator += (unsigned int user);
      property & operator += (long i);
      property & operator += (unsigned long user);
      property & operator += (double d);
      property & operator += (const var & var);
      property & operator += (const property & prop);
      property & operator += (const char * psz);
      property & operator += (const string & str);

      property & operator /= (int i);
      property & operator /= (unsigned int user);
      property & operator /= (long i);
      property & operator /= (unsigned long user);
      property & operator /= (double d);
      property & operator /= (const var & var);
      property & operator /= (const property & prop);

      property & operator *= (int i);
      property & operator *= (unsigned int user);
      property & operator *= (long i);
      property & operator *= (unsigned long user);
      property & operator *= (double d);
      property & operator *= (const var & var);
      property & operator *= (const property & prop);


      void parse_json(const string & str);
      void parse_json(const char * & pszJson, strsize length);
      void parse_json(const char * & pszJson, const char * pszEnd);


      var explode(const char * pszSeparator, bool bAddEmpty = true) const;


      #undef new
      #undef delete
            void * PASCAL operator new(size_t nSize);
            void * PASCAL operator new(size_t, void * p);
            void PASCAL operator delete(void * p);
      #if _MSC_VER >= 1200 || defined(LINUX)
            void PASCAL operator delete(void * p, void * pPlace);
      #endif

      #if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)  || defined(LINUX)
            // for file name/line number tracking using DEBUG_NEW
            void * PASCAL operator new(size_t nSize, const char * lpszFileName, int nLine);
      #if _MSC_VER >= 1200  || defined(LINUX)
            void PASCAL operator delete(void *p, const char * lpszFileName, int nLine);
      #endif
      #endif
      #define new DEBUG_NEW

   };


   class CLASS_DECL_ca property_array :
      public ex1::byte_serializable_array < array_ptr_alloc < property, property & > >
   {
   public:
      
      
      property_array();


   };


   namespace str
   {
      inline bool CLASS_DECL_ca begins(const gen::property & property, const char * lpcszPrefix) { return begins((const string &) property, lpcszPrefix); };
   }


} // namespace gen


