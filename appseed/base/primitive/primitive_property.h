#pragma once


class property;


string CLASS_DECL_BASE operator + (const char * psz, const property & prop);
string CLASS_DECL_BASE operator + (const string & str, const property & prop);

var CLASS_DECL_BASE operator - (int32_t i, const property & prop);
var CLASS_DECL_BASE operator - (uint32_t user, const property & prop);
var CLASS_DECL_BASE operator - (int64_t i, const property & prop);
var CLASS_DECL_BASE operator - (uint64_t ui, const property & prop);
var CLASS_DECL_BASE operator - (double d, const property & prop);
var CLASS_DECL_BASE operator - (const var & var, const property & prop);
var CLASS_DECL_BASE operator - (const property & prop1, const property & prop2);

var CLASS_DECL_BASE operator + (int32_t i, const property & prop);
var CLASS_DECL_BASE operator + (uint32_t user, const property & prop);
var CLASS_DECL_BASE operator + (int64_t i, const property & prop);
var CLASS_DECL_BASE operator + (uint64_t ui, const property & prop);
var CLASS_DECL_BASE operator + (double d, const property & prop);
var CLASS_DECL_BASE operator + (const var & var, const property & prop);
var CLASS_DECL_BASE operator + (const property & prop1, const property & prop2);

var CLASS_DECL_BASE operator / (int32_t i, const property & prop);
var CLASS_DECL_BASE operator / (uint32_t user, const property & prop);
var CLASS_DECL_BASE operator / (int64_t i, const property & prop);
var CLASS_DECL_BASE operator / (uint64_t ui, const property & prop);
var CLASS_DECL_BASE operator / (double d, const property & prop);
var CLASS_DECL_BASE operator / (const var & var, const property & prop);
var CLASS_DECL_BASE operator / (const property & prop1, const property & prop2);

var CLASS_DECL_BASE operator * (int32_t i, const property & prop);
var CLASS_DECL_BASE operator * (uint32_t user, const ::core:: property & prop);
var CLASS_DECL_BASE operator * (int64_t i, const property & prop);
var CLASS_DECL_BASE operator * (uint64_t ui, const property & prop);
var CLASS_DECL_BASE operator * (double d, const property & prop);
var CLASS_DECL_BASE operator * (const var & var, const property & prop);
var CLASS_DECL_BASE operator * (const property & prop1, const property & prop2);


namespace xml
{


   class disp_option;


} // namespace xml


class CLASS_DECL_BASE pair_set_interface
{
public:


   pair_set_interface();


   virtual bool get_auto_add() const;
   virtual bool get_key_case_insensitive() const;


   virtual void pair_set_interface_set(const char * pszKey, var value) = 0;
   virtual var pair_set_interface_get_value(int32_t i) const = 0;
   virtual var & pair_set_interface_get_value(int32_t i) = 0;
   virtual const string_composite pair_set_interface_get_key(int32_t i) const = 0;
   virtual int32_t pair_set_interface_get_count() const = 0;
   virtual int32_t pair_set_interface_find(const char * pszKey, int32_t iStart = 0) const;
   var operator[](const char * pszName) const;
   var & operator[](const char * pszName);
};

class CLASS_DECL_BASE str_str_interface
{
public:

   str_str_interface();


   virtual bool get_auto_add() const;
   virtual bool get_key_case_insensitive() const;

   virtual void str_str_interface_set(const char * pszKey, const char * pszValue) = 0;
   virtual const string_composite str_str_interface_get_value(int32_t i) const = 0;
   virtual string_composite str_str_interface_get_value(int32_t i) = 0;
   virtual const string_composite str_str_interface_get_key(int32_t i) const = 0;
   virtual int32_t str_str_interface_get_count() const = 0;
   virtual int32_t str_str_interface_find(const char * pszKey, int32_t iStart = 0) const;
   const string_composite operator[](const char * pszName) const;
   string_composite operator[](const char * pszName);
   virtual bool contains_key(stringa & stra);
};

class property_set;
class property_map;


class CLASS_DECL_BASE property :
   public object,
   public ::file::serializable
{
protected:


   id                m_idName;

public:

   var               m_var;


   property(sp(base_application) papp);
   property();
   property(const property & prop);
   property(id strName);
   property(id strName, var var);
#ifdef MOVE_SEMANTICS
   property(property && prop)
   {
      m_idName.m_pstr = prop.m_idName.m_pstr;
      m_var.m_sp.release();
      m_var.m_str.~string();
      memcpy(&m_var, &prop.m_var, sizeof(var));
      prop.m_var.m_sp.m_p           = NULL;
      prop.m_var.m_str.m_pszData    = NULL;
      prop.m_var.m_id.m_pstr        = NULL;
   }
#endif
   ~property()
   {
   }

   inline id name()
   {
      return m_idName;
   }

   inline id name() const
   {
      return m_idName;
   }

   inline void set_name(id id)
   {
      m_idName = id;
   }

   inline void set_name(string str)
   {
      m_idName = id(str);
   }

   inline void set_name(const var & var)
   {
      set_name(id(var.get_string()));
   }

   inline void set_name(const property & prop)
   {
      set_name(id(prop.get_string()));
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
   strsize get_length() const;

   string get_xml(::xml::disp_option * opt = ((::xml::disp_option *) 1));


   property & operator[](id idName);
   property & operator[](const char * pszName);

   inline var & get_value()
   {
      return m_var;
   }
   inline const var & get_value() const
   {
      return m_var;
   }
   inline void set_value(const var & var)
   {
      m_var = var;
   }

   void unset();


   inline void   get_value(var & value);
   inline void   get(var & value);
   inline var &  get();
   inline void   set(const var & var);



   bool get_bool() const
   {
      return get_value().get_bool();
   }

   int32_t int32(int32_t iDefault = 0) const
   {
      return get_value().int32(iDefault);
   }

   uint32_t uint32(uint32_t uiDefault = 0) const
   {
      return get_value().uint32(uiDefault);
   }

   int64_t int64(int64_t iDefault = 0) const
   {
      return get_value().int64(iDefault);
   }

   uint64_t uint64(uint64_t uiDefault = 0) const
   {
      return get_value().uint64(uiDefault);
   }

   double get_double() const
   {
      return get_value().get_double();
   }

   string get_string() const
   {
      return m_var.get_string();
   }

   string to_string() const
   {
      return get_string();
   }


   void set_string(const char * psz)
   {
      get_value() = psz;
   }

   property & operator++(int32_t)
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

   property & operator =(const string & str)
   {
      get_value() = str;
      return *this;
   }

   property & operator =(const stringa & stra)
   {
      get_value() = stra;
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

   property & operator =(int32_t i)
   {
      get_value() = i;
      return *this;
   }

#ifdef WINDOWS

   property & operator =(LONG l)
   {
      get_value() = l;
      return *this;
   }

#endif

   property & operator =(uint32_t ui)
   {
      get_value() = ui;
      return *this;
   }


   property & operator =(int64_t i)
   {
      get_value() = i;
      return *this;
   }

   property & operator =(uint64_t ui)
   {
      get_value() = ui;
      return *this;
   }

   property & operator =(bool b)
   {
      get_value() = b;
      return *this;
   }

   template < class T >
   property & operator =(const smart_pointer < T > & p)
   {
      get_value() = p.m_p;
      return *this;
   }

   property & operator =(element * p)
   {
      get_value() = p;
      return *this;
   }
#ifdef MOVE_SEMANTICS
   property & operator = (property && prop)
   {
      if(this != &prop)
      {
         m_var.m_sp.release();
         m_var.m_str.~string();
         m_idName.m_pstr = prop.m_idName.m_pstr;
         memcpy(&m_var, &prop.m_var, sizeof(var));
         prop.m_var.m_sp.m_p = NULL;
         prop.m_var.m_str.m_pszData = NULL;
      }
      return *this;
   }
#endif

   template < class T >
   sp(T) cast(T * pDefault = NULL)
   {
      return get_value().cast < T >(pDefault);
   }

   template < class T >
   sp(T) cast(T * pDefault = NULL) const
   {
      return ((property *) this)->get_value().cast < T >(pDefault);
   }

   operator const char *() const
   {

      ((property *) this)->m_var.m_str = get_value().get_string();

      return m_var.m_str;

   }

   operator string & ()
   {

      return m_var.operator string &();

   }

   operator id()
   {
      return m_var.get_id();
   }

   /*      operator const id()
   {
   return get_value().get_id();
   }

   operator id &()
   {
   get_value().m_id = get_value().get_id();
   return get_value().m_id;
   }

   operator const id &()
   {
   get_value().m_id = get_value().get_id();
   return get_value().m_id;
   }*/

   operator double()
   {
      return get_value().get_double();
   }

   operator int32_t()
   {
      return get_value().operator int32_t();
   }

#ifdef WINDOWS

   operator LONG()
   {
      return get_value().operator LONG();
   }

#endif

   operator uint32_t()
   {
      return get_value().operator uint32_t();
   }

   operator int64_t()
   {
      return get_value().operator int64_t();
   }

   operator uint64_t()
   {
      return get_value().operator uint64_t();
   }

   operator bool()
   {
      return get_value().operator bool();
   }

   var equals_ci_get(const char * pszCompare, var varOnEqual, var varOnDifferent) const;
   var equals_ci_get(const char * pszCompare, var varOnEqual) const;


   ::count get_count() const;
   ::count array_get_count() const;
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

   int32_t compare_value_ci(const char * psz) const;

   ::comparison::var_strict strict_compare() const;

   int32_t str_compare(const property & prop) const;


   bool strict_equal(const property & prop) const;
   bool strict_equal(const var & var) const;
   bool strict_equal(const char * psz) const;
   bool strict_equal(const string & str) const;
   bool strict_equal(double d) const;
   bool strict_equal(int32_t i) const;
   bool strict_equal(bool b) const;

   bool strict_different(const property & prop) const;
   bool strict_different(const var & var) const;
   bool strict_different(const char * psz) const;
   bool strict_different(const string & str) const;
   bool strict_different(double d) const;
   bool strict_different(int32_t i) const;
   bool strict_different(bool b) const;

   bool operator == (const property & prop) const;
   bool operator == (const var & var) const;
   bool operator == (const char * psz) const;
   bool operator == (const string & str) const;
   bool operator == (int32_t i) const;
   bool operator == (bool b) const;

   bool operator != (const property & prop) const;
   bool operator != (const var & var) const;
   bool operator != (const char * psz) const;
   bool operator != (const string & str) const;
   bool operator != (int32_t i) const;
   bool operator != (bool b) const;

   bool operator < (const property & prop) const;
   bool operator < (const var & var) const;
   bool operator < (const char * psz) const;
   bool operator < (const string & str) const;
   bool operator < (int32_t i) const;
   bool operator < (bool b) const;

   bool operator <= (const property & prop) const;
   bool operator <= (const var & var) const;
   bool operator <= (const char * psz) const;
   bool operator <= (const string & str) const;
   bool operator <= (int32_t i) const;
   bool operator <= (bool b) const;

   bool operator >= (const property & prop) const;
   bool operator >= (const var & var) const;
   bool operator >= (const char * psz) const;
   bool operator >= (const string & str) const;
   bool operator >= (int32_t i) const;
   bool operator >= (bool b) const;

   bool operator > (const property & prop) const;
   bool operator > (const var & var) const;
   bool operator > (const char * psz) const;
   bool operator > (const string & str) const;
   bool operator > (int32_t i) const;
   bool operator > (bool b) const;

   void write(::file::output_stream & ostream);
   void read(::file::input_stream & ostream);


   string operator + (const char * psz) const;
   string operator + (const string & str) const;

   //      friend string CLASS_DECL_BASE operator + (const char * psz, const property & var);
   //      friend string CLASS_DECL_BASE operator + (const string & str, const property & var);

   var operator - (int32_t i) const;
   var operator - (uint32_t user) const;
   var operator - (int64_t i) const;
   var operator - (uint64_t ui) const;
   var operator - (double d) const;
   var operator - (const var & var) const;

   //      friend var CLASS_DECL_BASE operator - (int32_t i, const property & prop);
   //      friend var CLASS_DECL_BASE operator - (uint32_t user, const property & prop);
   //      friend var CLASS_DECL_BASE operator - (int64_t i, const property & prop);
   //      friend var CLASS_DECL_BASE operator - (uint64_t ui, const property & prop);
   //      friend var CLASS_DECL_BASE operator - (double d, const property & prop);
   //      friend var CLASS_DECL_BASE operator - (const var & var, const property & prop);
   //      friend var CLASS_DECL_BASE operator - (const property & prop1, const property & prop2);

   var operator + (int32_t i) const;
   var operator + (uint32_t user) const;
   var operator + (int64_t i) const;
   var operator + (uint64_t ui) const;
   var operator + (double d) const;
   var operator + (const var & var) const;

   //      friend var CLASS_DECL_BASE operator + (int32_t i, const property & prop);
   //      friend var CLASS_DECL_BASE operator + (uint32_t user, const property & prop);
   //      friend var CLASS_DECL_BASE operator + (int64_t i, const property & prop);
   //      friend var CLASS_DECL_BASE operator + (uint64_t ui, const property & prop);
   //      friend var CLASS_DECL_BASE operator + (double d, const property & prop);
   //      friend var CLASS_DECL_BASE operator + (const var & var, const property & prop);
   //      friend var CLASS_DECL_BASE operator + (const property & prop1, const property & prop2);

   var operator / (int32_t i) const;
   var operator / (uint32_t user) const;
   var operator / (int64_t i) const;
   var operator / (uint64_t ui) const;
   var operator / (double d) const;
   var operator / (const var & var) const;

   //      friend var CLASS_DECL_BASE operator / (int32_t i, const property & prop);
   //      friend var CLASS_DECL_BASE operator / (uint32_t user, const property & prop);
   //      friend var CLASS_DECL_BASE operator / (int64_t i, const property & prop);
   //      friend var CLASS_DECL_BASE operator / (uint64_t ui, const property & prop);
   //      friend var CLASS_DECL_BASE operator / (double d, const property & prop);
   //      friend var CLASS_DECL_BASE operator / (const var & var, const property & prop);
   //      friend var CLASS_DECL_BASE operator / (const property & prop1, const property & prop2);

   var operator * (int32_t i) const;
   var operator * (uint32_t user) const;
   var operator * (int64_t i) const;
   var operator * (uint64_t ui) const;
   var operator * (double d) const;
   var operator * (const var & var) const;

   //      friend var CLASS_DECL_BASE operator * (int32_t i, const property & prop);
   //      friend var CLASS_DECL_BASE operator * (uint32_t user, const property & prop);
   //      friend var CLASS_DECL_BASE operator * (int64_t i, const property & prop);
   //      friend var CLASS_DECL_BASE operator * (uint64_t ui, const property & prop);
   //      friend var CLASS_DECL_BASE operator * (double d, const property & prop);
   //      friend var CLASS_DECL_BASE operator * (const var & var, const property & prop);
   //      friend var CLASS_DECL_BASE operator * (const property & prop1, const property & prop2);

   property & operator -= (int32_t i);
   property & operator -= (uint32_t user);
   property & operator -= (int64_t i);
   property & operator -= (uint64_t ui);
   property & operator -= (double d);
   property & operator -= (const var & var);
   property & operator -= (const property & prop);

   property & operator += (int32_t i);
   property & operator += (uint32_t user);
   property & operator += (int64_t i);
   property & operator += (uint64_t ui);
   property & operator += (double d);
   property & operator += (const var & var);
   property & operator += (const property & prop);
   property & operator += (const char * psz);
   property & operator += (const string & str);

   property & operator /= (int32_t i);
   property & operator /= (uint32_t user);
   property & operator /= (int64_t i);
   property & operator /= (uint64_t ui);
   property & operator /= (double d);
   property & operator /= (const var & var);
   property & operator /= (const property & prop);

   property & operator *= (int32_t i);
   property & operator *= (uint32_t user);
   property & operator *= (int64_t i);
   property & operator *= (uint64_t ui);
   property & operator *= (double d);
   property & operator *= (const var & var);
   property & operator *= (const property & prop);


   void parse_json(const string & str);
   void parse_json(const char * & pszJson, strsize length);
   void parse_json(const char * & pszJson, const char * pszEnd);


   var explode(const char * pszSeparator, bool bAddEmpty = true) const;


//   DECLARE_BASE_FIXED_ALLOC(property)
    
    
    void null() { m_var.null(); }


};



class CLASS_DECL_BASE property_array :
   public ::file::byte_serializable_pointer_array < spa(property) >
{
public:


   property_array(sp(base_application) papp = NULL);




};

class CLASS_DECL_BASE property_map :
   public id_to_index
{
public:



   property_map();




};





inline property & property::operator[](const char * pszName)
{
   return operator [](id(string(pszName)));
}


namespace str
{
   inline bool CLASS_DECL_BASE begins(const property & property, const char * lpcszPrefix) { return begins(property.get_string(), lpcszPrefix); };
}



inline bool operator == (const string & str, const property & prop)
{
   return str == prop.get_string();
}


inline string::string(const property & prop) :
simple_string(string_trait::GetDefaultManager())
{

   operator = (prop.to_string());

}

inline string & string::operator = (const property & prop)
{

   return operator = (prop.to_string());

}
