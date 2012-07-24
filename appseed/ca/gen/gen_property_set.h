#pragma once


namespace gen
{


   class CLASS_DECL_ca property_set :
      public ::radix::object,
      public ex1::byte_serializable
   {
   public:


      property_map         m_map;
      property_array       m_propertya;
      signal               m_signal;
      bool                 m_bAutoAdd;
      bool                 m_bMultiValue;
      bool                 m_bKeyCaseInsensitive;



      property_set(::ca::application * papp = NULL, bool bAutoAdd = true, bool bMultiValue = false, bool bKeyCaseInsensitive = true);
      property_set(const property_set & set);
      property_set(const pair_set_interface & set);
      property_set(const str_str_interface & set);
      virtual ~property_set();


//      inline property_map::pair * next(property_pair & pair);
  //    inline const property_map::pair * next(const_property_pair & pair) const;



      property * add(const char * pszName);
      property * lowadd(const string & strLowName);
      property * lowadd(const string & strLowName, const var & var);
      property * add(const char * pszName, var var);
      property * set(const char * pszName, var var);
      property * lowset(const string & strName, const var & var);
      count remove_by_name(const char * pszName);
      count remove_by_name(stringa & straName);
      property & operator[](const char * pszName);
      property operator[](const char * pszName) const;
      property & lowprop(const string & strName);
      property lowprop(const string & strName) const;
      property & operator[](index iIndex);
      property operator[](index iIndex) const;
#ifdef AMD64
      inline property & operator[](int iIndex) { return operator []((index) iIndex); }
      inline property operator[](int iIndex) const { return operator []((index) iIndex); }
#endif
      property & operator[](const var & var);
      property operator[](const var & var) const;
      property & operator[](const string & str);
      property operator[](const string  & str) const;

      property & at(index iId);
      property at(index iId) const;

      index find_var_ci(const var & var) const;
      index find_value_ci(var var) const;
      index find_value_ci(const char * psz) const;

      index find_var(const var & var) const;
      index find_value(var var) const;
      index find_value(const char * psz) const;

      index str_find(const property & property, index find = 0) const;

      bool contains_var_ci(const var & var, count countMin = 1, count countMax = -1) const;
      bool contains_value_ci(var var, count countMin = 1, count countMax = -1) const;
      bool contains_value_ci(const char * psz, count countMin = 1, count countMax = -1) const;

      bool contains_var(const var & var, count countMin = 1, count countMax = -1) const;
      bool contains_value(var var, count countMin = 1, count countMax = -1) const;
      bool contains_value(const char * psz, count countMin = 1, count countMax = -1) const;

      bool str_contains(const property_set & set) const;

      index remove_first_var_ci(const var & var);
      index remove_first_value_ci(var var);
      index remove_first_value_ci(const char * psz);

      index remove_first_var(const var & var);
      index remove_first_value(var var);
      index remove_first_value(const char * psz);

      count remove_var_ci(const var & var, count countMin = 0, count countMax = -1);
      count remove_value_ci(var var, count countMin = 0, count countMax = -1);
      count remove_value_ci(const char * psz, count countMin = 0, count countMax = -1);

      count remove_var(const var & var, count countMin = 0, count countMax = -1);
      count remove_value(var var, count countMin = 0, count countMax = -1);
      count remove_value(const char * psz, count countMin = 0, count countMax = -1);

      bool has_property(const char * pszName) const;
      bool has_property(const string & pszName) const;
      bool has_property(string_interface & str) const;

      bool low_has_property(const char * pszName) const;
      bool low_has_property(const string & pszName) const;
      bool low_has_property(string_interface & str) const;

      bool is_set_empty(count countMinimum = 1) const;
      bool has_properties(count countMinimum = 1) const;

      const property * lowfind(const char * pszName) const;
      const property * lowfind(const string & strName) const;
      const property * lowfind(string_interface & str) const;

      property * lowfind(const char * pszName);
      property * lowfind(const string & strName);
      property * lowfind(string_interface & str);

      const property * find(const char * pszName) const;
      const property * find(string_interface & str) const;

      property * find(const char * pszName);
      property * find(string_interface & str);


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
      void _008Add(const char * pszKey, const char * pszValue);


      void clear();

      void replace_ex1(string & str);
      string eval(const char * psz);

      string ex2_eval(const char * psz);

      void parse_json(const char * & pszJson);
      void parse_json(const char * & pszJson, const char * pszEnd);
      void parse_url_query(const char * pszUrl);
      void _parse_url_query(const char * pszUrlQuery);
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



   inline count property_set::get_count() const
   {
      return m_map.get_count();
   }


/*   inline property_map::pair * property_set::next(property_pair & pair)
   {
      return m_map.next(pair.m_ppair);
   }


   inline const property_map::pair * property_set::next(const_property_pair & pair) const
   {
      return m_map.next(pair.m_ppair);
   }
   */

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

      gen::property * operator ->()
      {
         return &m_set.m_propertya[m_ppair->m_value];
      }

      const gen::property * operator ->() const
      {
         return &m_set.m_propertya[m_ppair->m_value];
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

      const gen::property * operator ->()
      {
         return &m_set.m_propertya[m_ppair->m_value];
      }

      const gen::property * operator ->() const
      {
         return &m_set.m_propertya[m_ppair->m_value];
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

   inline bool property_set::has_property(const string & strName) const
   {
      const property * pproperty = find(strName);
      return pproperty != NULL && pproperty->m_var.m_etype != var::type_new;
   }

   inline bool property_set::has_property(const char * pszName) const
   {
      return has_property(string(pszName));
   }

   inline bool property_set::has_property(string_interface & str) const
   {
      return has_property(string(str));
   }

   inline bool property_set::low_has_property(const string & strName) const
   {
      const property * pproperty = find(strName);
      return pproperty != NULL && pproperty->m_var.m_etype != var::type_new;
   }

   inline bool property_set::low_has_property(const char * pszName) const
   {
      return has_property(string(pszName));
   }

   inline bool property_set::low_has_property(string_interface & str) const
   {
      return has_property(string(str));
   }

   inline property * property_set::lowfind(const string & strName)
   {
      gen::property_map::pair * ppair = m_map.PLookup(strName);
      if(ppair == NULL)
         return NULL;
      return &m_propertya[ppair->m_value];
   }

   inline property * property_set::lowfind(const char * pszName)
   {
      return lowfind(string(pszName));
   }

   inline property * property_set::lowfind(string_interface & str)
   {
      return lowfind(string(str));
   }

   inline property * property_set::set(const char * pszName, var var)
   {
      property * p = find(pszName);
      if(p != NULL)
      {
         p->get_value() = var;
         return p;
      }
      else
      {
         return add(pszName, var);
      }
   }


   inline property * property_set::lowset(const string & strName, const var & var)
   {
      property * p = lowfind(strName);
      if(p != NULL)
      {
         p->get_value() = var;
         return p;
      }
      else
      {
         return lowadd(strName, var);
      }
   }




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

inline const var &  var::operator[] (const char * pszKey) const
{
   return propset().operator[](pszKey).get_value();
}

inline var & var::operator[] (const char * pszKey)
{
   return propset().operator[](pszKey).get_value();
}



