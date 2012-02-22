#pragma once


namespace gen
{


   class CLASS_DECL_ca property_set :
      public ex1::byte_serializable
   {
   public:


      var_property_array   m_propertya;
      signal               m_signal;
      bool                 m_bAutoAdd;
      bool                 m_bMultiValue;
      bool                 m_bKeyCaseInsensitive;



      property_set(::ca::application * papp = NULL, bool bAutoAdd = true, bool bMultiValue = false, bool bKeyCaseInsensitive = true);
      property_set(const property_set & set);
      property_set(const pair_set_interface & set);
      property_set(const str_str_interface & set);
      virtual ~property_set(void);


      property * add(const char * pszName, var var = g_newconst);
      property * set(const char * pszName, var var);
      index remove_first_by_name(const char * pszName, index first = 0, index last = -1);
      count remove_by_name(const char * pszName, index first = 0, index last = -1);
      count remove_by_name(stringa & straName);

      property & operator[](const char * pszName);
      var_property operator[](const char * pszName) const;
      property & operator[](index iIndex);
      var_property operator[](index iIndex) const;
      property & operator[](const string_interface & str);
      var_property operator[](const string_interface & str) const;
      property & operator[](const string & str);
      var_property operator[](const string  & str) const;

      property & at(index iId);
      var_property at(index iId) const;

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
      

      enum e_type
      {
         TypeBeforeChange,
         TypeAfterChange,
      };
      
      
      e_type m_etype;
      var m_variableOldValue;
      property * m_pproperty;
      property_set * m_pset;


      PropertySignalObject(signal * psignal);


   };


} // namespace gen




// var/property_set inline member functions

inline var var::first() const
{
   return operator[]((var)(int) 0);
}

inline var var::last() const
{
   if(array_get_count() == 0)
      return first();
   else
      return operator[](array_get_upper_bound());
}

inline const var & var::operator[] (var varKey) const
{
   return propset().operator[](varKey).get_value();
}

inline var & var::operator[] (var varKey)
{
   return propset().operator[](varKey).get_value();
}

inline const var & var::operator[] (index iKey) const
{
   return propset().operator[](iKey).get_value();
}

inline var & var::operator[] (index iKey)
{
   return propset().operator[](iKey).get_value();
}

inline const var &  var::operator[] (const char * pszKey) const
{
   return propset().operator[](pszKey).get_value();
}

inline var & var::operator[] (const char * pszKey)
{
   return propset().operator[](pszKey).get_value();
}
