#pragma once




// property set key is case insensitive
class CLASS_DECL_AURA property_set :
   public object,
   public ::file::serializable
{
public:


   property_map         m_map;
   property_array       m_propertya;
   class signal         m_signal;
   bool                 m_bAutoAdd;
   bool                 m_bMultiValue;



   property_set(sp(::aura::application) papp = NULL, bool bAutoAdd = true, bool bMultiValue = false);
   property_set(const property_set & set);
   property_set(const pair_set_interface & set);
   property_set(const str_str_interface & set);
   virtual ~property_set();


   //      inline property_map::pair * next(property_pair & pair);
   //    inline const property_map::pair * next(const_property_pair & pair) const;



   property * add(id idName);
   property * add(id idName, var var);
   property * set(id idName, var var);
   property & defer_auto_add(id idName);
   id get_new_id();
   ::count remove_by_name(id idName);
   ::count remove_by_name(stringa & straName);
   property & operator[](string strName);
   property operator[](string strName) const;
   property & operator[](const char * pszName);
   property operator[](const char * pszName) const;
   property & operator[](index iIndex);
   property operator[](index iIndex) const;
#ifdef OS64BIT
   inline property & operator[](int32_t iIndex) { return operator []((index) iIndex); }
   inline property operator[](int32_t iIndex) const { return operator []((index) iIndex); }
#endif
   property & operator[](const var & var);
   property operator[](const var & var) const;
   property & operator[](id id);
   property operator[](id id) const;

   var lookup(id id) const;
   var lookup(id id, var varDefault) const;

   property & at(index iId);
   property at(index iId) const;

   index find_var_ci(const var & var) const;
   index find_value_ci(var var) const;
   index find_value_ci(const char * psz) const;

   index find_var(const var & var) const;
   index find_value(var var) const;
   index find_value(const char * psz) const;

   index str_find(const property & property, index find = 0) const;

   bool contains_var_ci(const var & var, ::count countMin = 1, ::count countMax = -1) const;
   bool contains_value_ci(var var, ::count countMin = 1, ::count countMax = -1) const;
   bool contains_value_ci(const char * psz, ::count countMin = 1, ::count countMax = -1) const;

   bool contains_var(const var & var, ::count countMin = 1, ::count countMax = -1) const;
   bool contains_value(var var, ::count countMin = 1, ::count countMax = -1) const;
   bool contains_value(const char * psz, ::count countMin = 1, ::count countMax = -1) const;

   bool str_contains(const property_set & set) const;

   index remove_first_var_ci(const var & var);
   index remove_first_value_ci(var var);
   index remove_first_value_ci(const char * psz);

   index remove_first_var(const var & var);
   index remove_first_value(var var);
   index remove_first_value(const char * psz);

   ::count remove_var_ci(const var & var, ::count countMin = 0, ::count countMax = -1);
   ::count remove_value_ci(var var, ::count countMin = 0, ::count countMax = -1);
   ::count remove_value_ci(const char * psz, ::count countMin = 0, ::count countMax = -1);

   ::count remove_var(const var & var, ::count countMin = 0, ::count countMax = -1);
   ::count remove_value(var var, ::count countMin = 0, ::count countMax = -1);
   ::count remove_value(const char * psz, ::count countMin = 0, ::count countMax = -1);

   bool has_property(id idName) const;
   bool has_property(string_interface & str) const;

   bool is_set_empty(::count countMinimum = 1) const;
   bool has_properties(::count countMinimum = 1) const;

   property * find(id idName) const;
   property * find(string_interface & str) const;

   index find_index(id idName) const;
   index find_index(string_interface & str) const;

   ::count unset(id idName);

   bool is_new(id idName) const;
   bool is_new(string_interface & str) const;

   bool is_null(id idName) const;
   bool is_null(string_interface & str) const;

   bool is_new_or_null(id idName) const;
   bool is_new_or_null(string_interface & str) const;

   bool is_empty(id idName) const;
   bool is_empty(string_interface & str) const;

   void OnBeforePropertyChange(property * pproperty);
   void OnAfterPropertyChange(const var & variableOld, property * pproperty);

   void _008ParseCommandLine(const char * pszCmdLine, var & varFile);
   void _008ParseCommandFork(const char * pszCmdLine, var & varFile, string & strApp);
   void _008Parse(bool bApp, const char * pszCmdLine, var & varFile, string & strApp);
   void _008Add(const char * pszKey, const char * pszValue);


   void clear();

   void replace_gen(string & str);
   string eval(const char * psz);

   string gen_eval(const char * psz);

   void parse_json(const char * & pszJson);
   void parse_json(const char * & pszJson, const char * pszEnd);
   void parse_url_query(const char * pszUrl);
   void _parse_url_query(const char * pszUrlQuery);
   void parse_http_headers(const char * pszHeaders);
   string get_http_post();
   string get_json();

   virtual void write(::file::output_stream & ostream);
   virtual void read(::file::input_stream & ostream);

   virtual string implode(const char * pszGlue) const;
   ::count get_count() const;


   property_set & operator = (const property_set & set);
   property_set & operator = (const pair_set_interface & set);
   property_set & operator = (const str_str_interface & set);

   property_set & operator += (const property_set & set);
   property_set & operator |= (const property_set & set);

   property_set & add(const property_set & set);
   property_set & merge(const property_set & set);


   template < class T >
   sp(T) cast(id idName, T * pDefault = NULL)
   {

      if (!has_property(idName))
         return pDefault;

      return operator[](idName).cast < T > (pDefault);

   }


   template < class T >
   sp(T) cast(id idName, T * pDefault = NULL) const
   {

      return ((property_set *) this)->cast < T >(idName, pDefault);

   }


};


class CLASS_DECL_AURA PropertySignalObject : public signal_details
{
public:


   enum e_type
   {
      TypeBeforeChange,
      TypeAfterChange
   };


   e_type m_etype;
   var m_variableOldValue;
   property * m_pproperty;
   property_set * m_pset;


   PropertySignalObject(class signal * psignal);


};



inline ::count property_set::get_count() const
{
   return m_map.get_count();
}


inline property * property_set::add(id idName)
{

   if(idName.is_null())
      idName = get_new_id();

   m_propertya.add(canew(property(idName)));

   m_map.set_at(idName, m_propertya.get_upper_bound());

   return m_propertya.last_element();

}


inline property * property_set::add(id idName, var var)
{

   if(idName.is_null())
      idName = get_new_id();

   m_propertya.add(canew(property(idName, var)));

   m_map.set_at(idName, m_propertya.get_upper_bound());

   return m_propertya.last_element();

}

class property_pair
{
public:


   property_map::pair * m_ppair;
   property_set & m_set;


   property_pair(property_set & set) :
      m_set(set)
   {
      m_ppair = NULL;
   }

   property * operator ->()
   {
      return m_set.m_propertya[m_ppair->m_element2];
   }

   const property * operator ->() const
   {
      return m_set.m_propertya[m_ppair->m_element2];
   }

   operator property_map::pair * ()
   {
      return m_ppair;
   }

   operator const property_map::pair * () const
   {
      return m_ppair;
   }

   bool operator ()()
   {
      return m_set.m_map.next(m_ppair) != NULL;
   }


};


class const_property_pair
{
public:


   const property_map::pair * m_ppair;
   const property_set & m_set;


   const_property_pair(const property_set & set) :
      m_set(set)

   {
      m_ppair = NULL;
   }

   const property * operator ->()
   {
      return m_set.m_propertya[m_ppair->m_element2];
   }

   const property * operator ->() const
   {
      return m_set.m_propertya[m_ppair->m_element2];
   }

   operator const property_map::pair * () const
   {
      return m_ppair;
   }


   bool operator ()()
   {
      return m_set.m_map.next(m_ppair) != NULL;
   }

};

inline bool property_set::has_property(id idName) const
{
   const property * pproperty = find(idName);
   return pproperty != NULL && pproperty->m_var.m_etype != var::type_new;
}

inline bool property_set::has_property(string_interface & str) const
{
   return has_property(string(str));
}


inline property * property_set::set(id idName, var var)
{
   property * p = find(idName);
   if(p != NULL)
   {
      p->get_value() = var;
      return p;
   }
   else
   {
      return add(idName, var);
   }
}


inline property property_set::operator[] (const char * pszKey) const
{
   return operator[](string(pszKey));
}

inline property & property_set::operator[] (const char * pszKey)
{
   return operator[](string(pszKey));
}


inline property property_set::operator[](id idName) const
{
   return const_cast<property_set*>(this)->operator[](idName);
}

inline property & property_set::operator[](index iIndex)
{
   return operator[](::str::from(iIndex));
}

inline property property_set::operator[](index iIndex) const
{
   return operator[](::str::from(iIndex));
}

inline property & property_set::operator[](const var & var)
{
   return operator[](string(var));
}

inline property property_set::operator[](const var & var) const
{
   return operator[](string(var));
}

inline property property_set::operator[](string str) const
{
   return operator[]((id) str);
}



inline property & property_set::operator[](string strName)
{
   return operator[](id(strName));
}

inline property & property_set::operator[](id idName)
{
   property * pproperty = find(idName);
   if(pproperty != NULL)
      return *pproperty;
   return defer_auto_add(idName);
}

inline var property_set::lookup(id idName) const
{
   property * pproperty = find(idName);
   if (pproperty == NULL)
      return var(var::type_new);
   return pproperty->m_var;
}

inline var property_set::lookup(id idName, var varDefault) const
{
   property * pproperty = find(idName);
   if (pproperty == NULL)
      return varDefault;
   return pproperty->m_var;
}



inline index property_set::find_index(id idName) const
{
   const property_map::pair * ppair = m_map.PLookup(idName);
   if(ppair == NULL)
      return -1;
   return ppair->m_element2;
}

inline index property_set::find_index(string_interface & str) const
{
   return find_index((const char *) string(str));
}


inline property * property_set::find(id idName) const
{

   index i = find_index(idName);

   if(i < 0)
      return NULL;

   return ((property_set *) this)->m_propertya[i];

}

inline property * property_set::find(string_interface & str) const
{
   return find((const char *) string(str));
}




// var/property_set inline member functions

inline var var::first() const
{
   return operator[]((var)(int32_t) 0);
}

inline var var::last() const
{
   if(array_get_count() == 0)
      return first();
   else
      return operator[](array_get_upper_bound());
}

inline const var & var::operator[] (const char * pszKey) const
{
   return propset().operator[](pszKey).get_value();
}

inline var & var::operator[] (const char * pszKey)
{
   return propset().operator[](pszKey).get_value();
}

inline const var & var::operator[] (var varKey) const
{
   return propset().operator[](varKey.get_string()).get_value();
}

inline var & var::operator[] (var varKey)
{
   return propset().operator[](varKey.get_string()).get_value();
}

inline const var & var::operator[] (index iKey) const
{
   return propset().operator[](iKey).get_value();
}

inline var & var::operator[] (index iKey)
{
   return propset().operator[](iKey).get_value();
}

inline const var & var::operator[] (string strKey) const
{
   return propset().operator[](strKey).get_value();
}

inline var & var::operator[] (id idKey)
{
   return propset().operator[](idKey).get_value();
}

inline const var & var::operator[] (id idKey) const
{
   return propset().operator[](idKey).get_value();
}

inline var & var::operator[] (string strKey)
{
   return propset().operator[](strKey).get_value();
}

inline property_set ca_property_set()
{
   return property_set();
}



inline string & operator += (string & str, const property & property)
{

   str += property.get_string();

   return str;

}


