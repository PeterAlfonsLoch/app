#pragma once


#include "gen/gen_signal.h"

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
      public ex1::byte_serializable,
      virtual public string_interface
   {
   public:


      string            m_strName;
      property_set *    m_pset;


      property(void);
      ~property(void);

      string & name();
      string name() const;

      stringa & stra(int iIndex = -1);
      int_array & inta(int iIndex = -1);
      var_array & vara(int iIndex = -1);
      property_set & propset(int iIndex = -1);
      const stringa & stra(int iIndex = -1) const;
      const int_array & inta(int iIndex = -1) const;
      const var_array & vara(int iIndex = -1) const;
      const property_set & propset(int iIndex = -1) const;
      virtual void get_string(char * psz) const;
      virtual int get_length() const;

      string get_xml(::xml::disp_option * opt = ((::xml::disp_option *) 1));


      property & operator[](const char * pszName);
      property & operator[](int iId);

      virtual var & get_value(int iIndex = -1) = 0;
      virtual var get_value(int iIndex = -1) const;
      virtual void   set_value(const var & var, int iIndex = -1) = 0;
      virtual void unset(int iIndex = -1);
      virtual int get_value_count();

      virtual void   get_value(var & value, int iIndex = -1);
      virtual void   get(var & value, int iIndex = -1);
      virtual var &  get(int iIndex = -1);
      virtual void   set(const var & var, int iIndex = -1);



      int get_integer(int iIndex = -1, int iDefault = 0)
      {
         return get_value(iIndex).get_integer(iDefault);
      }

      int get_integer(int iIndex = -1, int iDefault = 0) const
      {
         return get_value(iIndex).get_integer(iDefault);
      }

      double get_double(int iIndex = -1)
      {
         return get_value(iIndex).get_double();
      }

      double get_double(int iIndex = -1) const
      {
         return get_value(iIndex).get_double();
      }

      bool get_bool(int iIndex = -1)
      {
         return get_value(iIndex).get_bool();
      }

      bool get_bool(int iIndex = -1) const
      {
         return get_value(iIndex).get_bool();
      }

      string get_string(int iIndex = -1)
      {
         return get_value(iIndex).get_string();
      }

      string get_string(int iIndex = -1) const
      {
         return get_value(iIndex).get_string();
      }

      void set_string(const char * psz)
      {
         get_value(-1) = psz;
      }

      void set_string(const char * psz, int iIndex)
      {
         get_value(iIndex) = psz;
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


      int get_count(int iIndex = -1) const;
      int array_get_count(int iIndex = -1) const;
      bool array_contains(const char * psz, int iIndex = -1, index first = 0, index last = -1) const;
      bool array_contains_ci(const char * psz, int iIndex = -1, index first = 0, index last = -1) const;


      bool is_set(int iIndex = -1) const;
      bool is_new(int iIndex = -1) const;
      bool is_null(int iIndex = -1) const;
      bool is_new_or_null(int iIndex = -1) const;
      bool is_empty(int iIndex = -1) const;
      bool is_true(int iIndex = -1) const;

      virtual string implode(const char * pszGlue, int iIndex = -1) const;

      var element_at(int iId) const;
      var at(int iId) const;

      int compare_value_ci(const char * psz, int iIndex = -1) const;

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


   };

   class CLASS_DECL_ca var_property :
      public property
   {
   public:


      var_array m_vara;


      var_property();
      var_property(const property & prop);
      var_property(const char * pszName);
      var_property(int iId);
      var_property(const char * pszName, var & var);
      var_property(const var_property & prop);
      virtual ~var_property();

      virtual var & get_value(int iIndex = -1);
      virtual var get_value(int iIndex = -1) const;
      virtual void set_value(const var & var, int iIndex = -1);
      virtual int get_value_count();


      var_property & operator = (const var_property & prop);

   };


   class CLASS_DECL_ca null_property :
      public property
   {
   public:
      virtual var &  get_value(int iIndex = -1);
      virtual void   set_value(const var & var, int iIndex = -1);
   private:
      null_const   m_nullconst;
   };

   class CLASS_DECL_ca empty_property :
      public property
   {
   public:
      virtual var &  get_value(int iIndex = -1);
      virtual void   set_value(const var & var, int iIndex = -1);
   private:
      empty_const   m_emptyconst;
   };

   class CLASS_DECL_ca new_property :
      public property
   {
   public:
      virtual var &  get_value(int iIndex = -1);
      virtual void   set_value(const var & var, int iIndex = -1);
   private:
      new_const   m_newconst;
   };

   class CLASS_DECL_ca var_property_array :
      public ex1::byte_serializable_array < array_ptr_alloc < var_property, var_property & > >
   {
   public:
   };

   class CLASS_DECL_ca property_set :
      public ex1::byte_serializable
   {
   public:
      property_set(::ca::application * papp = NULL, bool bAutoAdd = true, bool bMultiValue = false, bool bKeyCaseInsensitive = true);
      virtual ~property_set(void);
      property_set(const property_set & set);
      property_set(const pair_set_interface & set);
      property_set(const str_str_interface & set);

      property * add(const char * pszName, var var = g_newconst);
      property * set(const char * pszName, var var);
      index remove_first_by_name(const char * pszName, index first = 0, index last = -1);
      count remove_by_name(const char * pszName, index first = 0, index last = -1);
      count remove_by_name(stringa & straName);

      property & operator[](const char * pszName);
      var_property operator[](const char * pszName) const;
      property & operator[](int iId);
      var_property operator[](int iId) const;
      property & operator[](const string_interface & str);
      var_property operator[](const string_interface & str) const;
      property & operator[](const string & str);
      var_property operator[](const string  & str) const;

      property & at(int iId);
      var_property at(int iId) const;

      index find_var_ci(const var & var, index find = 0, index last = -1) const;
      index find_value_ci(var var, index find = 0, index last = -1) const;
      index find_value_ci(const char * psz, index find = 0, index last = -1) const;

      index find_var(const var & var, index find = 0, index last = -1) const;
      index find_value(var var, index find = 0, index last = -1) const;
      index find_value(const char * psz, index find = 0, index last = -1) const;

      index str_find(const property & property, index find = 0) const;

      bool contains_var_ci(const var & var, index find = 0, index last = -1, count countMin = 1, count countMax = -1) const;
      bool contains_value_ci(var var, index find = 0, index last = -1, count countMin = 1, count countMax = -1) const;
      bool contains_value_ci(const char * psz, index find = 0, index last = -1, count countMin = 1, count countMax = -1) const;

      bool contains_var(const var & var, index find = 0, index last = -1, count countMin = 1, count countMax = -1) const;
      bool contains_value(var var, index find = 0, index last = -1, count countMin = 1, count countMax = -1) const;
      bool contains_value(const char * psz, index find = 0, index last = -1, count countMin = 1, count countMax = -1) const;

      bool str_contains(const property_set & set) const;

      index remove_first_var_ci(const var & var, index find = 0, index last = -1);
      index remove_first_value_ci(var var, index find = 0, index last = -1);
      index remove_first_value_ci(const char * psz, index find = 0, index last = -1);

      index remove_first_var(const var & var, index find = 0, index last = -1);
      index remove_first_value(var var, index find = 0, index last = -1);
      index remove_first_value(const char * psz, index find = 0, index last = -1);

      count remove_var_ci(const var & var, index find = 0, index last = -1, count countMin = 0, count countMax = -1);
      count remove_value_ci(var var, index find = 0, index last = -1, count countMin = 0, count countMax = -1);
      count remove_value_ci(const char * psz, index find = 0, index last = -1, count countMin = 0, count countMax = -1);

      count remove_var(const var & var, index find = 0, index last = -1, count countMin = 0, count countMax = -1);
      count remove_value(var var, index find = 0, index last = -1, count countMin = 0, count countMax = -1);
      count remove_value(const char * psz, index find = 0, index last = -1, count countMin = 0, count countMax = -1);

      bool has_property(const char * pszName, index find = 0, index last = -1) const;
      bool has_property(string_interface & str, index find = 0, index last = -1) const;

      bool is_set_empty(count countMinimum = 1) const;
      bool has_properties(count countMinimum = 1) const;

      const property * find(const char * pszName, index find = 0, index last = -1) const;
      const property * find(string_interface & str, index find = 0, index last = -1) const;

      property * find(const char * pszName, index find = 0, index last = -1);
      property * find(string_interface & str, index find = 0, index last = -1);

      index find_first(const char * pszName, index find = 0, index last = -1) const;
      index find_first(string_interface & str, index find = 0, index last = -1) const;

      count unset(const char * pszName);

      bool is_new(const char * pszName) const;
      bool is_new(string_interface & str) const;

      bool is_null(const char * pszName) const;
      bool is_null(string_interface & str) const;

      bool is_new_or_null(const char * pszName) const;
      bool is_new_or_null(string_interface & str) const;

      bool is_empty(const char * pszName) const;
      bool is_empty(string_interface & str) const;

      void OnBeforePropertyChange(property * pproperty);
      void OnAfterPropertyChange(const var & variableOld, property * pproperty);

      void _008ParseCommandLine(const char * pszCmdLine, var & varFile);
      void _008ParseCommandFork(const char * pszCmdLine, var & varFile, string & strApp);
      void _008Parse(bool bApp, const char * pszCmdLine, var & varFile, string & strApp);

      var_property_array m_propertya;
      signal m_signal;
      bool m_bAutoAdd;
      bool m_bMultiValue;
      bool m_bKeyCaseInsensitive;

      void clear();

      void replace_ex1(string & str);
      string eval(const char * psz);

      string ex2_eval(const char * psz);

      void parse_json(const char * & pszJson);
      void parse_json(const char * & pszJson, const char * pszEnd);
      void parse_url_query(const char * pszUrlQuery);
      void parse_http_headers(const char * pszHeaders);
      string get_http_post();

      virtual void write(ex1::byte_output_stream & ostream);
      virtual void read(ex1::byte_input_stream & ostream);

      virtual string implode(const char * pszGlue) const;
      count get_count() const;


      property_set & operator = (const property_set & set);
      property_set & operator = (const pair_set_interface & set);
      property_set & operator = (const str_str_interface & set);

      property_set & operator += (const property_set & set);
      property_set & operator |= (const property_set & set);

      property_set & add(const property_set & set);
      property_set & merge(const property_set & set);

   };

   class CLASS_DECL_ca relation_set :
      public property_set
   {
   public:
      relation_set(::ca::application * papp = NULL);
      virtual ~relation_set();
   };


   class CLASS_DECL_ca PropertySignalObject : public signal_object
   {
   public:
      PropertySignalObject(signal * psignal);
      enum e_type
      {
         TypeBeforeChange,
         TypeAfterChange,
      };
      e_type m_etype;
      var m_variableOldValue;
      property * m_pproperty;
      property_set * m_pset;
   };

   extern CLASS_DECL_ca new_property g_newproperty;
   extern CLASS_DECL_ca null_property g_nullproperty;
   extern CLASS_DECL_ca empty_property g_emptyproperty;


}// namespace gen
