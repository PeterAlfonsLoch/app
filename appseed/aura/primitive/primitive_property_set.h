#pragma once




// property set key is case insensitive
class CLASS_DECL_AURA property_set :
   public property_map,
   public ::file::serializable
{
public:

   int                  m_iIndex;

   class signal         m_signal;


   property_set(::aura::application * papp = NULL, bool bAutoAdd = true, bool bMultiValue = false);
   property_set(const property_set & set);
//   property_set(const pair_set_interface & set);
//   property_set(const str_str_interface & set);
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
   const property & operator[](string strName) const;
   property & operator[](const char * pszName);
   const property & operator[](const char * pszName) const;
   property & operator[](index iIndex);
   const property & operator[](index iIndex) const;
#ifdef OS64BIT
   inline property & operator[](int32_t iIndex) { return operator []((index) iIndex); }
   inline const property & operator[](int32_t iIndex) const { return operator []((index) iIndex); }
#endif
   property & operator[](const var & var);
   const property & operator[](const var & var) const;
   property & operator[](id id);
   const property & operator[](id id) const;

   var lookup(id id) const;
   var lookup(id id, var varDefault) const;

   property & get(id id);

   property & at(index iId);
   property at(index iId) const;

   property * find_var_ci(const var & var) const;
   property * find_value_ci(var var) const;
   property * find_value_ci(const char * psz) const;

   property * find_var(const var & var) const;
   property * find_value(var var) const;
   property * find_value(const char * psz) const;

   property * str_find(const property & property) const;

   bool contains_var_ci(const var & var, ::count countMin = 1, ::count countMax = -1) const;
   bool contains_value_ci(var var, ::count countMin = 1, ::count countMax = -1) const;
   bool contains_value_ci(const char * psz, ::count countMin = 1, ::count countMax = -1) const;

   bool contains_var(const var & var, ::count countMin = 1, ::count countMax = -1) const;
   bool contains_value(var var, ::count countMin = 1, ::count countMax = -1) const;
   bool contains_value(const char * psz, ::count countMin = 1, ::count countMax = -1) const;

   bool str_contains(const property_set & set) const;

   bool remove_first_var_ci(const var & var);
   bool remove_first_value_ci(var var);
   bool remove_first_value_ci(const char * psz);

   bool remove_first_var(const var & var);
   bool remove_first_value(var var);
   bool remove_first_value(const char * psz);

   ::count remove_var_ci(const var & var, ::count countMin = 0, ::count countMax = -1);
   ::count remove_value_ci(var var, ::count countMin = 0, ::count countMax = -1);
   ::count remove_value_ci(const char * psz, ::count countMin = 0, ::count countMax = -1);

   ::count remove_var(const var & var, ::count countMin = 0, ::count countMax = -1);
   ::count remove_value(var var, ::count countMin = 0, ::count countMax = -1);
   ::count remove_value(const char * psz, ::count countMin = 0, ::count countMax = -1);

   bool has_property(id idName) const;
   //bool has_property(string_interface & str) const;

   bool is_set_empty(::count countMinimum = 1) const;
   bool has_properties(::count countMinimum = 1) const;

   property * find(id idName) const;
   //property * find(string_interface & str) const;

   index find_index(id idName) const;
   //index find_index(string_interface & str) const;


   ::count unset(id idName);

   bool is_new(id idName) const;
//   bool is_new(string_interface & str) const;

   bool is_null(id idName) const;
//   bool is_null(string_interface & str) const;

   bool is_new_or_null(id idName) const;
//   bool is_new_or_null(string_interface & str) const;

   bool is_empty(id idName) const;
//   bool is_empty(string_interface & str) const;

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
   string & get_http_post(string & str) const;
   string & get_json(string & str) const;
   string get_http_post() const { string str; return get_http_post(str); }
   string get_json() const { string str; return get_json(str); }

   virtual void write(::file::ostream & ostream) const;
   virtual void read(::file::istream & ostream);

   virtual string implode(const char * pszGlue) const;
   //::count get_count() const;


   property_set & operator = (const property_set & set);
//   property_set & operator = (const pair_set_interface & set);
//   property_set & operator = (const str_str_interface & set);

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


//
//inline ::count property_set::get_count() const
//{
//   return get_count();
//}


inline property * property_set::add(id idName)
{

   if(idName.is_null())
      idName = get_new_id();

   return set_at(idName,property(idName, m_iIndex++));

}


inline property * property_set::add(id idName, var var)
{

   if(idName.is_null())
      idName = get_new_id();

   return set_at(idName,property(idName, var, m_iIndex++));

}


//class property_pair
//{
//public:
//
//
//   property_map::pair * m_ppair;
//   property_set & m_set;
//
//
//   property_pair(property_set & set) :
//      m_set(set)
//   {
//      m_ppair = NULL;
//   }
//
//   property * operator ->()
//   {
//      return m_set.m_propertyptra[m_ppair->m_element2];
//   }
//
//   const property * operator ->() const
//   {
//      return m_set.m_propertyptra[m_ppair->m_element2];
//   }
//
//   operator property_map::pair * ()
//   {
//      return m_ppair;
//   }
//
//   operator const property_map::pair * () const
//   {
//      return m_ppair;
//   }
//
//   bool operator ()()
//   {
//      return m_set.next(m_ppair) != NULL;
//   }
//
//
//};
//
//
//class const_property_pair
//{
//public:
//
//
//   const property_map::pair * m_ppair;
//   const property_set & m_set;
//
//
//   const_property_pair(const property_set & set) :
//      m_set(set)
//
//   {
//      m_ppair = NULL;
//   }
//
//   const property * operator ->()
//   {
//      return m_set.m_propertyptra[m_ppair->m_element2];
//   }
//
//   const property * operator ->() const
//   {
//      return m_set.m_propertyptra[m_ppair->m_element2];
//   }
//
//   operator const property_map::pair * () const
//   {
//      return m_ppair;
//   }
//
//
//   bool operator ()()
//   {
//      return m_set.next(m_ppair) != NULL;
//   }
//
//};

inline bool property_set::has_property(id idName) const
{

   const property * pproperty = find(idName);

   return pproperty != NULL && pproperty->m_element2.m_etype != var::type_new;

}

//inline bool property_set::has_property(string_interface & str) const
//{
//   return has_property(string(str));
//}


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


inline const property & property_set::operator[] (const char * pszKey) const
{
   return operator[](string(pszKey));
}

inline property & property_set::operator[] (const char * pszKey)
{
   return operator[](string(pszKey));
}


inline const property & property_set::operator[](id idName) const
{

   return const_cast<property_set*>(this)->operator[](idName);

}

inline property & property_set::operator[](index iIndex)
{

   for(auto & property : *this)
   {
      if(property.m_iIndex == iIndex)
         return property;
   }

   return *add(::property(::id(iIndex), iIndex));

}

inline const property &  property_set::operator[](index iIndex) const
{
   return operator[](::id(iIndex));
}

inline property & property_set::operator[](const var & var)
{
   return operator[](string(var));
}

inline const property &  property_set::operator[](const var & var) const
{
   return operator[](string(var));
}

inline const property &  property_set::operator[](string str) const
{
   return operator[]((id) str);
}



inline property & property_set::operator[](string strName)
{
   return operator[](id(strName));
}


inline property & property_set::operator[](id idName)
{

   return get(idName);

}

inline property & property_set::get(id idName)
{
   
   assoc * p = get_assoc(idName);

   if(p->m_iIndex < 0)
      p->m_iIndex = get_count() - 1;

   return *p;

}


inline var property_set::lookup(id idName) const
{
   property * pproperty = find(idName);
   if (pproperty == NULL)
      return var(var::type_new);
   return pproperty->m_element2;
}

inline var property_set::lookup(id idName, var varDefault) const
{
   property * pproperty = find(idName);
   if (pproperty == NULL)
      return varDefault;
   return pproperty->m_element2;
}



inline index property_set::find_index(id idName) const
{

   for(auto property : *this)
   {

      if(property.name() == idName)
      {

         return property.m_iIndex;

      }

   }

   return -1;

}


//inline index property_set::find_index(string_interface & str) const
//{
//
//   return find_index((const char *) string(str));
//
//}


inline property * property_set::find(id idName) const
{

   return (property *) PLookup(idName);

}


//inline property * property_set::find(string_interface & str) const
//{
//   return find((const char *) string(str));
//}




// var/property_set inline member functions

inline var var::first() const
{
   return at(0);
}

inline var var::last() const
{
   if(array_get_count() == 0)
      return first();
   else
      return at(array_get_upper_bound());
}

inline var var::first()
{
   return at(0);
}

inline var var::last()
{
   if(array_get_count() == 0)
      return first();
   else
      return at(array_get_upper_bound());
}

inline const var & var::operator[] (const char * pszKey) const
{
   return propset().operator[](pszKey).get_value();
}

inline var & var::operator[] (const char * pszKey)
{
   return propset().operator[](pszKey).get_value();
}

inline var var::operator[] (var varKey) const
{
   if(varKey.is_integer())
   {
      return at((index)varKey.int64());
   }
   else
   {
      return &propset().operator[](varKey.get_string()).get_value();
   }
}

inline var var::operator[] (var varKey)
{
   if(varKey.is_integer())
   {
      return at((index)varKey.int64());
   }
   else
   {
      return &propset().operator[](varKey.get_string()).get_value();
   }

}

inline var var::operator[] (index iKey) const
{
   return at(iKey);
}

inline var var::operator[] (index iKey)
{
   return at(iKey);
}

inline const var & var::operator[] (string strKey) const
{
   return propset().operator[](strKey).get_value();
}

inline var var::operator[] (id idKey)
{
   if(idKey.m_etype == id::type_integer)
   {
      return at((index) idKey.m_i);
   }
   else
   {
      return &propset().operator[](idKey).get_value();
   }
}

inline var var::operator[] (id idKey) const
{
   if(idKey.m_etype == id::type_integer)
   {
      return at((index) idKey.m_i);
   }
   else
   {
      return &propset().operator[](idKey).get_value();
   }
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


