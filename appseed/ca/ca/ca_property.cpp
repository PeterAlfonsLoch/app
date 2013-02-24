#include "framework.h"

#if defined(LINUX)
#include <ctype.h>
#endif

#define ROUND(x,y) (((x)+(y-1))&~(y-1))
#define ROUND16(x) ROUND(x, 16)

void prop_id_debug(::ca::application * papp);




namespace gen
{

   pair_set_interface::pair_set_interface()
   {
   }

   bool pair_set_interface::get_auto_add() const
   {
      return true;
   }

   bool pair_set_interface::get_key_case_insensitive() const
   {
      return true;
   }

   int32_t pair_set_interface::pair_set_interface_find(const char * pszKey, int32_t iStart) const
   {
      int32_t iCount = pair_set_interface_get_count();
      if(get_key_case_insensitive())
      {
         for(int32_t i = iStart; i < iCount; i++)
         {
            if(string(pair_set_interface_get_key(i)).CompareNoCase(pszKey) == 0)
            {
               return i;
            }
         }
      }
      else
      {
         for(int32_t i = iStart; i < iCount; i++)
         {
            if(string(pair_set_interface_get_key(i)) == pszKey)
            {
               return i;
            }
         }
      }
      return -1;
   }

   var & pair_set_interface::operator[](const char * pszName)
   {
      int32_t iFind = pair_set_interface_find(pszName);
      if(iFind >= 0)
         return pair_set_interface_get_value(iFind);
      if(get_auto_add())
      {
         pair_set_interface_set(pszName, ::var(::var::type_new));
         iFind = pair_set_interface_find(pszName);
         if(iFind >= 0)
            return pair_set_interface_get_value(iFind);
      }

      throw "cannot reference absent property";

   }

   var pair_set_interface::operator[](const char * pszName) const
   {
      int32_t iFind = pair_set_interface_find(pszName);
      if(iFind >= 0)
         return pair_set_interface_get_value(iFind);
      return ::var(::var::type_new);
   }

   str_str_interface::str_str_interface()
   {
   }

   bool str_str_interface::get_auto_add() const
   {
      return true;
   }

   bool str_str_interface::get_key_case_insensitive() const
   {
      return true;
   }

   int32_t str_str_interface::str_str_interface_find(const char * pszKey, int32_t iStart) const
   {
      int32_t iCount = str_str_interface_get_count();
      if(get_key_case_insensitive())
      {
         for(int32_t i = iStart; i < iCount; i++)
         {
            if(string(str_str_interface_get_key(i)).CompareNoCase(pszKey) == 0)
            {
               return i;
            }
         }
      }
      else
      {
         for(int32_t i = iStart; i < iCount; i++)
         {
            if(string(str_str_interface_get_key(i)) == pszKey)
            {
               return i;
            }
         }
      }
      return -1;
   }

   bool str_str_interface::contains_key(stringa & stra)
   {
      for(index i = 0; i < stra.get_count(); i++)
      {
         if(str_str_interface_find(stra[i]) < 0)
            return false;
      }
      return true;
   }


   string_composite str_str_interface::operator[](const char * pszName)
   {
      int32_t iFind = str_str_interface_find(pszName);
      if(iFind >= 0)
         return str_str_interface_get_value(iFind);
      if(get_auto_add())
      {
         str_str_interface_set(pszName, "");
         iFind = str_str_interface_find(pszName);
         if(iFind >= 0)
            return str_str_interface_get_value(iFind);
      }
      return string_composite(empty_string());
   }

   const string_composite str_str_interface::operator[](const char * pszName) const
   {
      int32_t iFind = str_str_interface_find(pszName);
      if(iFind >= 0)
         return str_str_interface_get_value(iFind);
      return empty_string();
   }

   void property::get_value(var & value)
   {
      value = get_value();
   }

   void property::get(var & value)
   {
      value = get_value();
   }

   var & property::get()
   {
      return get_value();
   }

   void property::set(const var & var)
   {
      set_value(var);
   }

   void property::unset()
   {
      get_value().unset();
   }

   string property::operator + (const char * psz) const
   {
      return get_value() + psz;
   }

   string property::operator + (const string & str) const
   {
      return get_value() + str;
   }



   property & property::operator = (const property & prop)
   {
      if(&prop != this)
      {
         if(m_strName.is_empty())
         {
            m_strName      = prop.m_strName;
            m_strNameLow   = prop.m_strNameLow;
         }
         m_var = prop.m_var;
      }
      return *this;
   }


   property::property()
   {
      m_pset = NULL;
   }

   property::property(const property & prop)
   {
      property::operator = ((const property &) prop);
   }


   property::property(const char * pszName)
   {
      m_strName = pszName;
      m_strNameLow = m_strName;
      m_strNameLow.make_lower();
   }

   property::property(const char * pszName, var & var)
   {
      m_strName = pszName;
      m_strNameLow = m_strName;
      m_strNameLow.make_lower();
      set_value(var);
   }

   bool property::is_set() const
   {
      return get_value().is_set();
   }

   bool property::is_new() const
   {
      return get_value().is_new();
   }

   bool property::is_null() const
   {
      return get_value().is_null();
   }

   bool property::is_new_or_null() const
   {
      return get_value().is_new_or_null();
   }

   bool property::is_empty() const
   {
      return get_value().is_empty();
   }

   bool property::is_true() const
   {
      return get_value().is_true();
   }

   string property::implode(const char * pszGlue) const
   {
      return get_value().implode(pszGlue);
   }

   void property::parse_json(const string & str)
   {
      const char * pszJson = str;
      parse_json(pszJson, str.get_length());
   }

   void property::parse_json(const char * & pszJson, strsize length)
   {
      parse_json(pszJson, pszJson + length - 1);
   }

   void property::parse_json(const char * & pszJson, const char * pszEnd)
   {
      gen::str::consume_spaces(pszJson, 0, pszEnd);
      m_strName = gen::str::consume_quoted_value(pszJson, pszEnd);
      m_strNameLow = m_strName;
      m_strNameLow.make_lower();
      gen::str::consume(pszJson, ":", 1, pszEnd);
      get_value().parse_json(pszJson, pszEnd);
   }

   stringa & property::stra()
   {
      return get_value().stra();
   }

   int_array & property::inta()
   {
      return get_value().inta();
   }

   var_array & property::vara()
   {
      return get_value().vara();
   }

   property_set & property::propset()
   {
      return get_value().propset();
   }

   const stringa & property::stra() const
   {
      return get_value().stra();
   }

   const int_array & property::inta() const
   {
      return get_value().inta();
   }

   const var_array & property::vara() const
   {
      return get_value().vara();
   }

   const property_set & property::propset() const
   {
      return get_value().propset();
   }

   strsize property::get_length() const
   {
      return get_value().get_length();
   }

   void property::get_string(char * psz) const
   {
      get_value().get_string(psz);
   }

   property & property::operator[](const char * pszName)
   {
      return propset().operator [](pszName);
   }

   property & property::operator[](index iIndex)
   {
      return propset().operator [](iIndex);
   }

   var property::element_at(index iIndex) const
   {
      switch(get_value().m_etype)
      {
      case var::type_stra:
         return const_cast<property *>(this)->stra().operator [](iIndex);
      case var::type_inta:
         return const_cast<property *>(this)->inta().operator [](iIndex);
      case var::type_vara:
         return const_cast<property *>(this)->vara().operator [](iIndex);
      case var::type_propset:
         return const_cast<property *>(this)->propset().at(iIndex);
      default:
         if(const_cast<property *>(this)->get_count() == 1)
            return const_cast<property *>(this)->get_value();
         throw "unsuported!!";
      }
   }

   var property::at(index iIndex) const
   {
      return this->element_at(iIndex);
   }

   void property::write(gen::byte_output_stream & ostream)
   {
      ostream << m_strName;
      ostream << get_value();
   }

   void property::read(gen::byte_input_stream & istream)
   {
      istream >> m_strName;
      istream >> get_value();
   }

   count property::get_count() const
   {
      return get_value().get_count();
   }

   count property::array_get_count() const
   {
      return get_value().array_get_count();
   }

   bool property::array_contains(const char * psz, index first, index last) const
   {
      return get_value().array_contains(psz, first, last);
   }

   bool property::array_contains_ci(const char * psz, index first, index last) const
   {
      return get_value().array_contains_ci(psz, first, last);
   }


   var property::equals_ci_get(const char * pszCompare, var varOnEqual, var varOnDifferent) const
   {
      if(compare_value_ci(pszCompare) == 0)
      {
         return varOnEqual;
      }
      else
      {
         return varOnDifferent;
      }
   }

   var property::equals_ci_get(const char * pszCompare, var varOnEqual) const
   {
      if(compare_value_ci(pszCompare) == 0)
      {
         return varOnEqual;
      }
      else
      {
         return var();
      }
   }


   int32_t property::compare_value_ci(const char * psz) const
   {
      return get_value().compare_ci(psz);
   }

   variable_strict_compare property::strict_compare() const
   {
      return const_cast < property * >(this)->get_value();
   }

   int32_t property::str_compare(const property & prop) const
   {
      int32_t iCompare = m_strName.Compare(prop.m_strName);
      if(iCompare != 0)
         return iCompare;
      return get_string().Compare(prop.get_string());
   }

   bool property::strict_equal(const property & prop) const
   {
      return get_value().strict_equal(prop.get_value());
   }

   bool property::strict_equal(const var & var) const
   {
      return get_value().strict_equal(var);
   }

   bool property::strict_equal(const char * psz) const
   {
      return get_value().strict_equal(psz);
   }

   bool property::strict_equal(const string & str) const
   {
      return get_value().strict_equal(str);
   }

   bool property::strict_equal(double d) const
   {
      return get_value().strict_equal(d);
   }

   bool property::strict_equal(int32_t i) const
   {
      return get_value().strict_equal(i);
   }

   bool property::strict_equal(bool b) const
   {
      return get_value().strict_equal(b);
   }


   bool property::strict_different(const property & prop) const
   {
      return get_value().strict_different(const_cast < property & > (prop).get_value());
   }

   bool property::strict_different(const var & var) const
   {
      return get_value().strict_different(var);
   }

   bool property::strict_different(const char * psz) const
   {
      return get_value().strict_different(psz);
   }

   bool property::strict_different(const string & str) const
   {
      return get_value().strict_different(str);
   }

   bool property::strict_different(double d) const
   {
      return get_value().strict_different(d);
   }

   bool property::strict_different(int32_t i) const
   {
      return get_value().strict_different(i);
   }

   bool property::strict_different(bool b) const
   {
      return get_value().strict_different(b);
   }


   bool property::operator == (const property & prop) const
   {
      return get_value() == prop.get_value();
   }

   bool property::operator == (const var & var) const
   {
      return get_value() == var;
   }

   bool property::operator == (const char * psz) const
   {
      return get_value() == psz;
   }

   bool property::operator == (const string & str) const
   {
      return get_value() == str;
   }

   bool property::operator == (int32_t i) const
   {
      return get_value() == i;
   }

   bool property::operator == (bool b) const
   {
      return get_value() == b;
   }


   bool property::operator != (const property & prop) const
   {
      return get_value() != prop.get_value();
   }

   bool property::operator != (const var & var) const
   {
      return get_value() != var;
   }

   bool property::operator != (const char * psz) const
   {
      return get_value() != psz;
   }

   bool property::operator != (const string & str) const
   {
      return get_value() != str;
   }

   bool property::operator != (int32_t i) const
   {
      return get_value() != i;
   }

   bool property::operator != (bool b) const
   {
      return get_value() != b;
   }

   var property::explode(const char * pszSeparator, bool bAddEmpty) const
   {
      return get_value().explode(pszSeparator, bAddEmpty);
   }



















   bool property::operator < (const property & prop) const
   {
      return get_value() < prop.get_value();
   }

   bool property::operator < (const var & var) const
   {
      return get_value() < var;
   }

   bool property::operator < (const char * psz) const
   {
      return get_value() < psz;
   }

   bool property::operator < (const string & str) const
   {
      return get_value() < str;
   }

   bool property::operator < (int32_t i) const
   {
      return get_value() < i;
   }

   bool property::operator < (bool b) const
   {
      return get_value() < b;
   }

























   bool property::operator <= (const property & prop) const
   {
      return get_value() <= prop.get_value();
   }

   bool property::operator <= (const var & var) const
   {
      return get_value() <= var;
   }

   bool property::operator <= (const char * psz) const
   {
      return get_value() <= psz;
   }

   bool property::operator <= (const string & str) const
   {
      return get_value() <= str;
   }

   bool property::operator <= (int32_t i) const
   {
      return get_value() <= i;
   }

   bool property::operator <= (bool b) const
   {
      return get_value() <= b;
   }
























   bool property::operator >= (const property & prop) const
   {
      return get_value() >= prop.get_value();
   }

   bool property::operator >= (const var & var) const
   {
      return get_value() >= var;
   }

   bool property::operator >= (const char * psz) const
   {
      return get_value() >= psz;
   }

   bool property::operator >= (const string & str) const
   {
      return get_value() >= str;
   }

   bool property::operator >= (int32_t i) const
   {
      return get_value() >= i;
   }

   bool property::operator >= (bool b) const
   {
      return get_value() >= b;
   }
























   bool property::operator > (const property & prop) const
   {
      return get_value() > prop.get_value();
   }

   bool property::operator > (const var & var) const
   {
      return get_value() > var;
   }

   bool property::operator > (const char * psz) const
   {
      return get_value() > psz;
   }

   bool property::operator > (const string & str) const
   {
      return get_value() > str;
   }

   bool property::operator > (int32_t i) const
   {
      return get_value() > i;
   }

   bool property::operator > (bool b) const
   {
      return get_value() > b;
   }




   var property::operator - (int32_t i) const
   {
      return get_value() - i;
   }

   var property::operator - (uint32_t user) const
   {
      return get_value() - user;
   }

   var property::operator - (int64_t i) const
   {
      return get_value() - i;
   }

   var property::operator - (uint64_t user) const
   {
      return get_value() - user;
   }

   var property::operator - (double d) const
   {
      return get_value() - d;
   }

   var property::operator - (const var & var) const
   {
      return get_value() - var;
   }




   var property::operator + (int32_t i) const
   {
      return get_value() + i;
   }

   var property::operator + (uint32_t user) const
   {
      return get_value() + user;
   }

   var property::operator + (int64_t i) const
   {
      return get_value() + i;
   }

   var property::operator + (uint64_t user) const
   {
      return get_value() + user;
   }

   var property::operator + (double d) const
   {
      return get_value() + d;
   }

   var property::operator + (const var & var) const
   {
      return get_value() + var;
   }















































   var property::operator / (int32_t i) const
   {
      return get_value() / i;
   }

   var property::operator / (uint32_t user) const
   {
      return get_value() / user;
   }

   var property::operator / (int64_t i) const
   {
      return get_value() / i;
   }

   var property::operator / (uint64_t user) const
   {
      return get_value() / user;
   }

   var property::operator / (double d) const
   {
      return get_value() / d;
   }

   var property::operator / (const var & var) const
   {
      return get_value() / var;
   }




   var property::operator * (int32_t i) const
   {
      return get_value() * i;
   }

   var property::operator * (uint32_t user) const
   {
      return get_value() * user;
   }

   var property::operator * (int64_t i) const
   {
      return get_value() * i;
   }

   var property::operator * (uint64_t user) const
   {
      return get_value() * user;
   }

   var property::operator * (double d) const
   {
      return get_value() * d;
   }

   var property::operator * (const var & var) const
   {
      return get_value() * var;
   }

















































   property & property::operator -= (int32_t i)
   {
      operator=(*this - i);
      return *this;
   }

   property & property::operator -= (uint32_t user)
   {
      operator=(*this - user);
      return *this;
   }

   property & property::operator -= (int64_t i)
   {
      operator=(*this - i);
      return *this;
   }

   property & property::operator -= (uint64_t user)
   {
      operator=(*this - user);
      return *this;
   }

   property & property::operator -= (double d)
   {
      operator=(*this - d);
      return *this;
   }

   property & property::operator -= (const var & var)
   {
      operator=(*this - var);
      return *this;
   }

   property & property::operator -= (const property & prop)
   {
      operator=(get_value() - prop.get_value());
      return *this;
   }























































   property & property::operator += (int32_t i)
   {
      operator=(*this + i);
      return *this;
   }

   property & property::operator += (uint32_t user)
   {
      operator=(*this + user);
      return *this;
   }

   property & property::operator += (int64_t i)
   {
      operator=(*this + i);
      return *this;
   }

   property & property::operator += (uint64_t user)
   {
      operator=(*this + user);
      return *this;
   }

   property & property::operator += (double d)
   {
      operator=(*this + d);
      return *this;
   }

   property & property::operator += (const var & var)
   {
      operator=(*this + var);
      return *this;
   }

   property & property::operator += (const property & prop)
   {
      operator=(get_value() + prop.get_value());
      return *this;
   }

   property & property::operator += (const char * psz)
   {
      operator=(*this + psz);
      return *this;
   }

   property & property::operator += (const string & str)
   {
      operator=(*this + str);
      return *this;
   }

























   property & property::operator /= (int32_t i)
   {
      operator=(*this / i);
      return *this;
   }

   property & property::operator /= (uint32_t user)
   {
      operator=(*this / user);
      return *this;
   }

   property & property::operator /= (int64_t i)
   {
      operator=(*this / i);
      return *this;
   }

   property & property::operator /= (uint64_t user)
   {
      operator=(*this / user);
      return *this;
   }

   property & property::operator /= (double d)
   {
      operator=(*this / d);
      return *this;
   }

   property & property::operator /= (const var & var)
   {
      operator=(*this / var);
      return *this;
   }

   property & property::operator /= (const property & prop)
   {
      operator=(get_value() / prop.get_value());
      return *this;
   }

























   property & property::operator *= (int32_t i)
   {
      operator=(*this * i);
      return *this;
   }

   property & property::operator *= (uint32_t user)
   {
      operator=(*this * user);
      return *this;
   }

   property & property::operator *= (int64_t i)
   {
      operator=(*this * i);
      return *this;
   }

   property & property::operator *= (uint64_t user)
   {
      operator=(*this * user);
      return *this;
   }

   property & property::operator *= (double d)
   {
      operator=(*this * d);
      return *this;
   }

   property & property::operator *= (const var & var)
   {
      operator=(*this * var);
      return *this;
   }

   property & property::operator *= (const property & prop)
   {
      operator=(get_value() * prop.get_value());
      return *this;
   }











































   property_map::property_map()
   {
      InitHashTable(64);
   }

   property_array::property_array()
   {
      set_size(0, 64);
   }


   property_set::property_set(::ca::application * papp,
      bool bAutoAdd, bool bMultiValue, bool bKeyCaseInsensitive) :
   ca(papp)
   {
      m_bAutoAdd = bAutoAdd;
      m_bMultiValue = bMultiValue;
      m_bKeyCaseInsensitive = bKeyCaseInsensitive;
   }


   property_set::~property_set()
   {
   }

   property * property_set::add(const char * pszName)
   {
      string strName;
      if(pszName == NULL)
      {
         index iMax = -1;
         index idx;
         ::gen::property_pair pair(*this);
         while(pair())
         {
            if(pair->name() == "0")
            {
               idx = 0;
            }
            else
            {
               idx = atoi(pair->name());
               if(idx == 0)
                  idx = -1;
            }
            if(idx > iMax)
               iMax = idx;
         }
         strName.Format("%d", iMax + 1);
      }
      else
      {
         strName = pszName;
      }
      if(m_bKeyCaseInsensitive)
      {
         string strNameLow = strName;
         strNameLow.make_lower();
         m_propertya.add(property(strName));
         m_map.set_at(strNameLow, m_propertya.get_upper_bound());
         m_propertya.last_element().m_pset = this;
         return &m_propertya.last_element();
      }
      else
      {
         m_propertya.add(property(strName));
         m_map.set_at(strName, m_propertya.get_upper_bound());
         m_propertya.last_element().m_pset = this;
         return &m_propertya.last_element();
      }
   }

   property * property_set::lowadd(const string & strLowName)
   {
      property p;
      p.name() = strLowName;
      p.lowname() = strLowName;
      m_propertya.add(p);
      m_map.set_at(strLowName, m_propertya.get_upper_bound());
      m_propertya.last_element().m_pset = this;
      return &m_propertya.last_element();
   }

   property * property_set::lowadd(const string & strLowName, const var & var)
   {
      property p;
      p.name() = strLowName;
      p.lowname() = strLowName;
      p.m_var = var;
      m_propertya.add(p);
      m_map.set_at(strLowName, m_propertya.get_upper_bound());
      m_propertya.last_element().m_pset = this;
      return &m_propertya.last_element();
   }

   property * property_set::add(const char * pszName, var var)
   {
      string strName;
      if(pszName == NULL)
      {
         index iMax = -1;
         index idx;
         ::gen::property_pair pair(*this);
         while(pair())
         {
            if(pair->name() == "0")
            {
               idx = 0;
            }
            else
            {
               idx = atoi(pair->name());
               if(idx == 0)
                  idx = -1;
            }
            if(idx > iMax)
               iMax = idx;
         }
         strName.Format("%d", iMax + 1);
      }
      else
      {
         strName = pszName;
      }
      if(m_bKeyCaseInsensitive)
      {
         string strNameLow = strName;
         strNameLow.make_lower();
         m_propertya.add(property(strName, var));
         m_map.set_at(strNameLow, m_propertya.get_upper_bound());
         m_propertya.last_element().m_pset = this;
         return &m_propertya.last_element();
      }
      else
      {
         m_propertya.add(property(strName, var));
         m_map.set_at(strName, m_propertya.get_upper_bound());
         m_propertya.last_element().m_pset = this;
         return &m_propertya.last_element();
      }
   }

   property & property_set::operator[](const char * pszName)
   {
      property * pproperty = find(pszName);
      if(pproperty != NULL)
         return *pproperty;
      if(m_bAutoAdd)
      {
         add(pszName);
         property * pproperty = find(pszName);
         if(pproperty != NULL)
            return *pproperty;
      }
      throw simple_exception(get_app(), "property with specified name - and specified case sensitivity - does not exist and Auto add Flag is not set");
   }

   property & property_set::lowprop(const string & strName)
   {
      property * pproperty = lowfind(strName);
      if(pproperty != NULL)
         return *pproperty;
      if(m_bAutoAdd)
      {
         pproperty = lowadd(strName);
         if(pproperty != NULL)
            return *pproperty;
      }
      throw simple_exception(get_app(), "property with specified name - and specified case sensitivity - does not exist and Auto add Flag is not set");
   }


   bool property_set::is_set_empty(count countMinimum) const
   {
      return get_count() < countMinimum;
   }

   bool property_set::has_properties(count countMinimum) const
   {
      return get_count() >= countMinimum;
   }


   index property_set::find_var_ci(const var & var) const
   {
      for(index find = 0; find < m_propertya.get_count(); find++)
      {
         if(m_propertya[find].get_value().compare_ci(var) == 0)
            return find;
      }
      return -1;
   }

   index property_set::find_value_ci(var var) const
   {
      return find_var_ci(var);
   }


   index property_set::find_var(const var & var) const
   {
      for(index find = 0; find < m_propertya.get_count(); find++)
      {
         if(m_propertya[find].get_value() == var)
            return find;
      }
      return -1;
   }

   index property_set::find_value(var var) const
   {
      return find_var(var);
   }

   bool property_set::contains_var_ci(const var & var, count countMin, count countMax) const
   {
      count count = 0;
      while((count < countMin || (countMax >= 0 && count <= countMax))
         && (find_var_ci(var)) >= 0)
         count++;
      return count >= countMin && conditional(countMax >= 0, count <= countMax);
   }

   bool property_set::contains_value_ci(var var, count countMin, count countMax) const
   {
      return contains_var_ci(var, countMin, countMax);
   }

   bool property_set::contains_value_ci(const char * psz, count countMin, count countMax) const
   {
      count count = 0;
      while((count < countMin || (countMax >= 0 && count <= countMax))
         && (find_value_ci(psz)) >= 0)
         count++;
      return count >= countMin && conditional(countMax >= 0, count <= countMax);
   }


   bool property_set::contains_var(const var & var, count countMin, count countMax) const
   {
      count count = 0;
      while((count < countMin || (countMax >= 0 && count <= countMax))
         && (find_var(var)) >= 0)
         count++;
      return count >= countMin && conditional(countMax >= 0, count <= countMax);
   }

   bool property_set::contains_value(var var, count countMin, count countMax) const
   {
      return contains_var(var, countMin, countMax);
   }

   bool property_set::contains_value(const char * psz, count countMin, count countMax) const
   {
      count count = 0;
      while((count < countMin || (countMax >= 0 && count <= countMax))
         && (find_value(psz)) >= 0)
         count++;
      return count >= countMin && conditional(countMax >= 0, count <= countMax);
   }

   index property_set::remove_first_var_ci(const var & var)
   {
      index find;
      if((find = find_var_ci(var)) >= 0)
         m_propertya.remove_at(find);
      return find;
   }

   index property_set::remove_first_value_ci(var var)
   {
      return remove_first_var_ci(var);
   }

   index property_set::remove_first_value_ci(const char * lpcsz)
   {
      index find;
      if((find = find_value_ci(lpcsz)) >= 0)
         m_propertya.remove_at(find);
      return find;
   }

   index property_set::remove_first_var(const var & var)
   {
      index find;
      if((find = find_var(var)) >= 0)
         m_propertya.remove_at(find);
      return find;
   }

   index property_set::remove_first_value(var var)
   {
      return remove_first_var(var);
   }

   index property_set::remove_first_value(const char * lpcsz)
   {
      index find;
      if((find = find_value(lpcsz)) >= 0)
         m_propertya.remove_at(find);
      return find;
   }


   count property_set::remove_var_ci(const var & var, count countMin, count countMax)
   {
      count count = 0;
      if(contains_var_ci(var, countMin, countMax))
         while(conditional(countMax >= 0, count < countMax)
            && (remove_first_var_ci(var)) >= 0)
            count++;
      return count;
   }

   count property_set::remove_value_ci(var var, count countMin, count countMax)
   {
      return remove_var_ci(var, countMin, countMax);
   }

   count property_set::remove_value_ci(const char * psz, count countMin, count countMax)
   {
      count count = 0;
      if(contains_value_ci(psz, countMin, countMax))
         while(conditional(countMax >= 0, count < countMax)
            && (remove_first_value_ci(psz)) >= 0)
            count++;
      return count;
   }

   count property_set::remove_var(const var & var, count countMin, count countMax)
   {
      count count = 0;
      if(contains_var(var, countMin, countMax))
         while(conditional(countMax >= 0, count < countMax)
            && (remove_first_var(var)) >= 0)
            count++;
      return count;
   }

   count property_set::remove_value(var var, count countMin, count countMax)
   {
      return remove_var(var, countMin, countMax);
   }

   count property_set::remove_value(const char * psz, count countMin, count countMax)
   {
      count count = 0;
      if(contains_value(psz, countMin, countMax))
         while(conditional(countMax >= 0, count < countMax)
            && (remove_first_value(psz)) >= 0)
            count++;
      return count;
   }




   count property_set::unset(const char * pszName)
   {
      if(m_bKeyCaseInsensitive)
      {
         string strName(pszName);
         strName.make_lower();
         gen::property_map::pair * ppair = m_map.PLookup(strName);
         if(ppair == NULL)
            return 0;
         m_propertya.remove_at(ppair->m_value);
         m_map.remove_key(strName);
         return 1;
      }
      else
      {
         gen::property_map::pair * ppair = m_map.PLookup(pszName);
         if(ppair == NULL)
            return 0;
         m_propertya.remove_at(ppair->m_value);
         m_map.remove_key(pszName);
         return 1;
      }
   }

   index property_set::find_index(const char * pszName)
   {
      if(m_bKeyCaseInsensitive)
      {
         string strName(pszName);
         strName.make_lower();
         gen::property_map::pair * ppair = m_map.PLookup(strName);
         if(ppair == NULL)
            return -1;
         return ppair->m_value;
      }
      else
      {
         gen::property_map::pair * ppair = m_map.PLookup(pszName);
         if(ppair == NULL)
            return -1;
         return ppair->m_value;
      }
   }

   index property_set::find_index(string_interface & str)
   {
      return find_index((const char *) string(str));
   }


   index property_set::find_index(const char * pszName) const
   {
      return ((property_set *) this)->find_index(pszName);
   }


   index property_set::find_index(string_interface & str) const
   {
      return find_index((const char *) string(str));
   }

   property * property_set::find(const char * pszName)
   {

      index i = find_index(pszName);

      if(i < 0)
         return NULL;

      return &m_propertya[i];

   }

   property * property_set::find(string_interface & str)
   {
      return find((const char *) string(str));
   }


   const property * property_set::find(const char * pszName) const
   {
      return ((property_set *) this)->find(pszName);
   }


   const property * property_set::find(string_interface & str) const
   {
      return find((const char *) string(str));
   }

   const property * property_set::lowfind(const char * pszName) const
   {
      return ((property_set *) this)->lowfind(pszName);
   }

   const property * property_set::lowfind(string_interface & str) const
   {
      return lowfind((const char *) string(str));
   }

   bool property_set::is_new(const char * pszName) const
   {
      const property * pproperty = find(pszName);
      if(pproperty == NULL)
         return true;
      return pproperty->is_new();
   }

   bool property_set::is_new(string_interface & str) const
   {
      return is_new((const char *) string(str));
   }

   bool property_set::is_null(const char * pszName) const
   {
      const property * pproperty = find(pszName);
      if(pproperty == NULL)
         return true;
      return pproperty->is_null();
   }

   bool property_set::is_null(string_interface & str) const
   {
      return is_null((const char *) string(str));
   }

   bool property_set::is_new_or_null(const char * pszName) const
   {
      const property * pproperty = find(pszName);
      if(pproperty == NULL)
         return true;
      return pproperty->is_new_or_null();
   }

   bool property_set::is_new_or_null(string_interface & str) const
   {
      return is_new_or_null((const char *) string(str));
   }


   bool property_set::is_empty(const char * pszName) const
   {
      const property * pproperty = find(pszName);
      if(pproperty == NULL)
         return true;
      return pproperty->is_empty();
   }

   bool property_set::is_empty(string_interface & str) const
   {
      const property * pproperty = find((const char *) string(str));
      if(pproperty == NULL)
         return true;
      return pproperty->is_empty();
   }

   void property_set::OnBeforePropertyChange(property * pproperty)
   {
      PropertySignalObject signal_object(&m_signal);
      signal_object.m_etype = PropertySignalObject::TypeBeforeChange;
      signal_object.m_pproperty = pproperty;
      signal_object.m_pset = this;
      m_signal.emit(&signal_object);
   }


   void property_set::OnAfterPropertyChange(const var & variableOld, property * pproperty)
   {
      UNREFERENCED_PARAMETER(variableOld);
      PropertySignalObject signal_object(&m_signal);
      signal_object.m_etype = PropertySignalObject::TypeAfterChange;
      signal_object.m_pproperty = pproperty;
      signal_object.m_pset = this;
      m_signal.emit(&signal_object);
   }


   void property_set::_008ParseCommandLine(const char * pszCmdLineParam, var & varFile)
   {
      string strApp;
      _008Parse(false, pszCmdLineParam, varFile, strApp);
   }

   void property_set::_008ParseCommandFork(const char * pszCmdLineParam, var & varFile, string & strApp)
   {
      _008Parse(true, pszCmdLineParam, varFile, strApp);
   }


   void property_set::_008Add(const char * pszKey, const char * pszValue)
   {

      stringa straKey;

      straKey.explode(".", pszKey);

      gen::property_set * pset = this;

      int32_t i = 0;

      while(i  < straKey.get_upper_bound())
      {
         pset = &pset->operator[](straKey[i]).propset();
         i++;
      }

      if(pset->has_property(straKey[i]))
      {
         pset->operator[](straKey[i]).stra().add(pszValue);
      }
      else
      {
         pset->add(straKey[i], var(pszValue));
      }

   }

   void property_set::_008Parse(bool bApp, const char * pszCmdLineParam, var & varFile, string & strApp)
   {

      const char * pszCmdLine =  pszCmdLineParam;

      if(pszCmdLine == NULL)
         return;

      string str;
      string strKey;
      string strValue;
      bool bQuote = false;
      bool bKey = false;
      bool bTwoDots = false;
      bool bFile = !bApp;
      bool bRun = true;
      bool bStarted = false;


      const char * pszStart = pszCmdLine;
      while(bRun)
      {
         bRun = bRun && *pszCmdLine != '\0';
         if(!bStarted && !bQuote && *pszCmdLine != '\0' && gen::ch::is_space_char(pszCmdLine))
         {
            pszStart = gen::str::utf8_inc(pszCmdLine);
            bStarted = true;
         }
         if(pszStart <= pszCmdLine && (((bApp || bFile) && ((!bQuote && isspace(*pszCmdLine)) || (bQuote && *pszCmdLine == '\"' && (*(pszCmdLine - 1)) != '\\') || !bRun)) || (!bTwoDots && !bQuote && *pszCmdLine == ':')))
         {
            if(!bTwoDots && !bQuote && *pszCmdLine == ':')
            {
               bTwoDots    = true;
            }
            if(bApp)
            {
               strApp = string(pszStart, pszCmdLine - pszStart);
               bApp = false;
               bFile = true;
               bStarted = false;
            }
            else if(bFile)
            {
               string strFile = string(pszStart, pszCmdLine - pszStart);
               strFile.trim();
               if(strFile.has_char())
               {
                  if(varFile.is_empty())
                  {
                     varFile = strFile;
                     if(bQuote)
                     {
                        pszCmdLine++;
                        bRun = bRun && *pszCmdLine != '\0';
                     }
                     bStarted = false;
                  }
                  else if(varFile.get_type() == var::type_string)
                  {
                     varFile.stra().add(strFile);
                     bStarted = false;
                  }
                  else if(varFile.get_type() == var::type_stra)
                  {
                     varFile.stra().add(strFile);
                     bStarted = false;
                  }
                  else if(varFile.get_type() == var::type_propset)
                  {
                     varFile.propset()["stra"].stra().add(strFile);
                     bStarted = false;
                  }
                  else
                  {
                     varFile.propset()["varFile"] = varFile;
                     varFile.propset()["stra"].stra().add(strFile);
                     bStarted = false;
                  }
               }
               pszStart = pszCmdLine;

            }
            if(bTwoDots)
            {
               bApp = false;
               bFile = false;
            }
            bQuote = false;
         }
         else if(bRun && !bQuote && *pszCmdLine == '\"' && (pszCmdLine == pszCmdLineParam || (*(pszCmdLine - 1)) != '\\'))
         {
            bQuote = true;
            pszStart = pszCmdLine + 1;
         }
         else if(bTwoDots)
         {
            if(*pszCmdLine == '\"' && *(pszCmdLine - 1) != '\\')
            {
               if(bQuote)
               {
                  if(bKey)
                  {
                     strKey = str;
                     str.Empty();
                  }
                  else
                  {
                     strValue = str;
                     str.Empty();
                     _008Add(strKey, strValue);
                     strKey.Empty();
                     strValue.Empty();
                  }
                  bQuote = false;
               }
            }
            else
            {
               if(bQuote)
               {
                  str += *pszCmdLine;
               }
               else if(*pszCmdLine == '=')
               {
                  strKey = str;
                  str.Empty();

                  bKey = false;
               }
               else if(*pszCmdLine == '\n' || *pszCmdLine == '\r'
                  || *pszCmdLine == '\t' || *pszCmdLine == ' '
                  || *pszCmdLine == '\0' || !bRun)
               {
                  if(bKey)
                  {
                     strKey = str;
                     _008Add(strKey, strValue);
                     strKey.Empty();
                     strValue.Empty();
                     str.Empty();
                  }
                  else if(!strKey.is_empty())
                  {
                     strValue = str;
                     _008Add(strKey, strValue);
                     strKey.Empty();
                     strValue.Empty();
                     str.Empty();
                  }
                  bKey = true;
               }
               else
               {
                  str += *pszCmdLine;
               }
            }
         }
         pszCmdLine++;
      }
   }

   void property_set::parse_json(const char * & pszJson)
   {
      parse_json(pszJson, pszJson + strlen(pszJson) - 1);
   }

   void property_set::parse_json(const char * & pszJson, const char * pszEnd)
   {
      gen::str::consume_spaces(pszJson, 0, pszEnd);
      gen::str::consume(pszJson, "{", 1, pszEnd);
      gen::str::consume_spaces(pszJson, 0, pszEnd);
      while(true)
      {
         m_propertya.set_size(m_propertya.get_size() + 1);
         m_propertya.last_element().parse_json(pszJson, pszEnd);
         m_map.set_at(m_propertya.last_element().lowname(), m_propertya.get_upper_bound());
         gen::str::consume_spaces(pszJson, 0, pszEnd);
         if(*pszJson == ',')
         {
            pszJson++;
            continue;
         }
         else if(*pszJson == '}')
         {
            pszJson++;
            return;
         }
         else
         {
            string str = "not expected character : ";
            str += pszJson;
            throw str;
         }
      }
   }


   void property_set::parse_url_query(const char * pszUrl)
   {
      if(pszUrl == NULL)
         return;
      const char * pszUrlQuery = strchr(pszUrl, '?');
      if(pszUrlQuery == NULL)
         return _parse_url_query(pszUrl);
      else
         return _parse_url_query(pszUrlQuery + 1);
   }

   void property_set::_parse_url_query(const char * pszUrlQuery)
   {
      if(pszUrlQuery == NULL)
         return;
      const char * pszParam = pszUrlQuery;
      const char * pszParamEnd;
      const char * pszKeyEnd;
      string strKey;
      while(true)
      {
         pszParamEnd = strchr(pszParam, '&');
         pszKeyEnd   = strchr(pszParam, '=');
         if(pszParamEnd == NULL)
         {
            if(pszKeyEnd == NULL)
            {
               strKey = System.url().url_decode(pszParam, strlen(pszUrlQuery) - (pszParam - pszUrlQuery));
               _008Add(strKey, "");
            }
            else
            {
               string strKey = System.url().url_decode(pszParam, pszKeyEnd - pszParam);
               string strValue = System.url().url_decode(pszKeyEnd + 1, strlen(pszUrlQuery) - (pszKeyEnd + 1 - pszUrlQuery));
               _008Add(strKey, strValue);
            }
            return;
         }
         else
         {
            if(pszKeyEnd == NULL || pszKeyEnd > pszParamEnd)
            {
               strKey = System.url().url_decode(pszParam, pszParamEnd - pszParam);
               _008Add(strKey, "");
            }
            else
            {
               string strKey = System.url().url_decode(pszParam, pszKeyEnd - pszParam);
               string strValue = System.url().url_decode(pszKeyEnd + 1, pszParamEnd - (pszKeyEnd + 1));
               _008Add(strKey, strValue);
            }
         }
         pszParam = pszParamEnd + 1;
      }

   }

   void property_set::parse_http_headers(const char * pszHeaders)
   {
      stringa stra;
      stra.add_tokens(pszHeaders, "\r\n", TRUE);
      string strName;
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         strsize iPos = stra[i].find(":");
         if(iPos < 0)
         {
            strName = stra[i];
            add(strName, var(""));
         }
         else
         {
            strName = stra[i].Left(iPos).make_lower();
            add(strName, var(stra[i].Mid(iPos + 2)));
         }
      }
   }


   count property_set::remove_by_name(const char * pszName)
   {
      return unset(pszName);
   }

   count property_set::remove_by_name(stringa & stra)
   {
      count count = 0;
      for(int32_t i = 0; i < stra.get_count(); i++)
      {
         count += remove(stra[i]);
      }
      return count;
   }


   PropertySignalObject::PropertySignalObject(signal * psignal)
      : signal_object(psignal)
   {
   }

   string property_set::get_http_post()
   {
      string strPost;
      for(int32_t i = 0; i < m_propertya.get_size(); i++)
      {
         strPost += m_propertya.element_at(i).name();
         strPost += "=";
         strPost += System.url().url_encode(m_propertya.element_at(i).get_value().get_string());
         if(i < m_propertya.get_size() - 1)
            strPost += "&";
      }
      return strPost;
   }



   string property::get_xml(::xml::disp_option * opt /*= &optDefault*/ )
   {
      //   std::ostringstream ostring;
      //   //ostring << (const char *)m_strName << "='" << (const char *)m_strValue << "' ";

      //   ostring << (const char *)m_strName << L"=" << (CHAR)opt->value_quotation_mark
      //      << (const char *)(opt->reference_value&&opt->m_pentities?opt->m_pentities->entity_to_ref(m_strValue):m_strValue)
      //      << (CHAR)opt->value_quotation_mark << L" ";
      //   return ostring.str();

      if(opt == ((::xml::disp_option *) 1))
      {
         opt = System.xml().m_poptionDefault;
      }

      string str;

      str = name();
      str += "=";
      str += opt->value_quotation_mark;
      string strValue;
      if(opt->reference_value && opt->m_pentities)
         strValue = opt->m_pentities->entity_to_ref(get_string());
      else
         strValue = get_string();

      strValue.replace("\\", "\\\\"); // should be first
      strValue.replace("\n", "\\n");
      strValue.replace("\t", "\\t");
      strValue.replace("\r", "\\r");
      strValue.replace("'", "\\'");
      strValue.replace("\"", "\\\"");

      str += strValue;
      str += opt->value_quotation_mark;
      str += " ";

      return str;
   }



   void property_set::replace_gen(string & str)
   {

      strsize iPos;

      char ch;

      char chNext;

      for(iPos = 0; iPos < str.get_length(); iPos++)
      {
         ch = str[iPos];
         if(iPos + 1 < str.get_length())
            chNext = str[iPos + 1];
         else
            chNext = '\0';
         if(ch == '\\')
         {
            iPos++;
            continue;
         }
         else if(ch == '{' && chNext == '$')
         {
            strsize iEnd = str.find('}', iPos + 1);
            if(iEnd < 0)
            {
               //error
               break;
            }
            string strEval = gen_eval(str.Mid(iPos + 1, iEnd - iPos - 1));
            str = str.Left(iPos) + strEval + str.Mid(iEnd + 1);
            iPos += strEval.get_length() - 1;
         }
         else if(ch == '$')
         {
            if(!(isalpha(chNext) || chNext == '_'))
            {
               // error
               break;
            }
            strsize iStart = iPos;
            strsize iEnd = iStart + 2;
            for(; iEnd < str.get_length(); iEnd++)
            {
               ch = str[iEnd];
               if(!(isalpha(ch) || ch == '_' || isdigit(ch)))
               {
                  break;
               }
            }
            string strEval = gen_eval(str.Mid(iStart, iEnd - iStart));
            str = str.Left(iPos) + strEval + str.Mid(iEnd);
            iPos += strEval.get_length() - 1;
         }
      }
   }

   string property_set::eval(const char * psz)
   {
      string str = psz;
      replace_gen(str);
      return str;
   }


   string property_set::gen_eval(const char * psz)
   {
      string str;
      ASSERT(psz != NULL);
      ASSERT(psz[0] == '$'); // until now accepts only one var
      ASSERT(strlen(psz) >= 2);
      str = operator [](&psz[1]);
      replace_gen(str);
      return str;
   }

   void property_set::clear()
   {
      m_propertya.remove_all();
      m_map.remove_all();
   }

   void property_set::write(gen::byte_output_stream & ostream)
   {
      ostream << m_bAutoAdd;
      ostream << m_bMultiValue;
      ostream << m_bKeyCaseInsensitive;
      ostream << m_propertya;
   }

   void property_set::read(gen::byte_input_stream & istream)
   {
      istream >> m_bAutoAdd;
      istream >> m_bMultiValue;
      istream >> m_bKeyCaseInsensitive;
      istream >> m_propertya;
      for(int32_t i = 0; i < m_propertya.get_count(); i++)
      {
         if(m_bKeyCaseInsensitive)
         {
            m_map.set_at(m_propertya[i].lowname(), i);
         }
         else
         {
            m_map.set_at(m_propertya[i].name(), i);
         }
      }
   }

   string property_set::implode(const char * pszGlue) const
   {
      string str;
      if(m_propertya.get_count() > 0)
      {
         str = m_propertya[0].get_value().get_string();
      }
      for(int32_t i = 1; i < m_propertya.get_count(); i++)
      {
         str += pszGlue;
         str += m_propertya[i].get_value().get_string();
      }
      return str;
   }

   index property_set::find_value(const char * psz) const
   {
      for(index find = 0; find < m_propertya.get_count(); find++)
      {
         if(m_propertya[find].get_string() == psz)
            return find;
      }
      return -1;
   }

   index property_set::find_value_ci(const char * psz) const
   {
      for(index find = 0; find < m_propertya.get_count(); find++)
      {
         if(m_propertya[find].get_string().CompareNoCase(psz) == 0)
            return find;
      }
      return -1;
   }

   property_set::property_set(const property_set & set)
   {
      operator = (set);
   }

   property_set::property_set(const pair_set_interface & set)
   {
      operator = (set);
   }

   property_set::property_set(const str_str_interface & set)
   {
      operator = (set);
   }

   property & property_set::at(index iIndex)
   {
      if(iIndex >= m_propertya.get_size())
      {
         m_propertya.set_size(iIndex + 1);
      }
      return m_propertya[iIndex];
   }

   property property_set::at(index iIndex) const
   {
      if(iIndex >= m_propertya.get_size())
      {
         const_cast < property_set * > (this)->m_propertya.set_size(iIndex + 1);
      }
      return const_cast<property_set*>(this)->m_propertya[iIndex];
   }

   property_set & property_set::operator = (const property_set & set)
   {
      if(&set != this)
      {
         m_propertya.set_size(set.m_propertya.get_size());
         for(int32_t i = 0; i < set.m_propertya.get_count(); i++)
         {
            m_propertya[i] = set.m_propertya[i];
         }
         m_bAutoAdd              = set.m_bAutoAdd;
         m_bMultiValue           = set.m_bMultiValue;
         m_bKeyCaseInsensitive   = set.m_bKeyCaseInsensitive;
         for(int32_t i = 0; i < m_propertya.get_count(); i++)
         {
            m_propertya[i].m_pset = this;
         }
         m_map                   = set.m_map;
      }
      return *this;
   }

   property_set & property_set::add(const property_set & set)
   {
      if(&set != this)
      {
         for(int32_t i = 0; i < set.m_propertya.get_count(); i++)
         {
            ((property &)operator[](set.m_propertya[i].name())).m_var = set.m_propertya[i].get_value();
         }
      }
      return *this;
   }

   property_set & property_set::merge(const property_set & set)
   {
      if(&set != this)
      {
         for(int32_t i = 0; i < set.m_propertya.get_count(); i++)
         {
            ((property &)operator[](set.m_propertya[i].name())).m_var = set.m_propertya[i].m_var;
         }
      }
      return *this;
   }

   property_set & property_set::operator += (const property_set & set)
   {
      return add(set);
   }

   property_set & property_set::operator |= (const property_set & set)
   {
      return merge(set);
   }

   property_set & property_set::operator = (const pair_set_interface & set)
   {
      //   if(&set != this)
      {
         m_propertya.remove_all();
         int32_t iCount = set.pair_set_interface_get_count();
         for(int32_t i = 0; i < iCount; i++)
         {
            string strKey = set.pair_set_interface_get_key(i);
            class var var = set.pair_set_interface_get_value(i);
            m_propertya.add(property(strKey, var));
         }
         // WOULD ANALYZE each of the following members parameters for
         // auto discovery, calculation or leave as set.
         m_bAutoAdd              = set.get_auto_add();
         //m_bMultiValue           = set.m_bMultiValue;
         m_bKeyCaseInsensitive   = set.get_key_case_insensitive();
         for(int32_t i = 0; i < m_propertya.get_count(); i++)
         {
            m_propertya[i].m_pset = this;
         }
      }
      return *this;
   }








   property_set & property_set::operator = (const str_str_interface & set)
   {
      //   if(&set != this)
      {
         m_propertya.remove_all();
         int32_t iCount = set.str_str_interface_get_count();
         for(int32_t i = 0; i < iCount; i++)
         {
            string strKey = set.str_str_interface_get_key(i);
            class var var = set.str_str_interface_get_value(i);
            m_propertya.add(property(strKey, var));
         }
         // WOULD ANALYZE each of the following members parameters for
         // auto discovery, calculation or leave as set.
         m_bAutoAdd              = set.get_auto_add();
         //m_bMultiValue           = set.m_bMultiValue;
         m_bKeyCaseInsensitive   = set.get_key_case_insensitive();
         for(int32_t i = 0; i < m_propertya.get_count(); i++)
         {
            m_propertya[i].m_pset = this;
         }
      }
      return *this;
   }




   index property_set::str_find(const property & property, index find) const
   {
      if(find < 0)
         find = 0;
      for(; find < this->get_count(); find++)
      {
         if(m_propertya[find].str_compare(property) == 0)
            return find;
      }
      return -1;
   }



   bool property_set::str_contains(const property_set & set) const
   {

      for(index i = 0; i < set.m_propertya.get_count(); i++)
      {
         if(str_find(set.m_propertya[i]) < 0)
            return false;
      }
      return true;

   }


   property property_set::operator[](const char * pszName) const
   {
      return const_cast<property_set*>(this)->operator[](pszName);
   }

   property property_set::lowprop(const string & strName) const
   {
      return const_cast<property_set*>(this)->lowprop(strName);
   }

   property & property_set::operator[](index iIndex)
   {
      return operator[](gen::str::from(iIndex));
   }

   property property_set::operator[](index iIndex) const
   {
      return operator[](gen::str::from(iIndex));
   }

   property & property_set::operator[](const var & var)
   {
      return operator[](string(var));
   }

   property property_set::operator[](const var & var) const
   {
      return operator[](string(var));
   }

   property & property_set::operator[](const string & str)
   {
      return operator[]((const char *) str);
   }

   property property_set::operator[](const string & str) const
   {
      return operator[]((const char *) str);
   }
















































   relation_set::relation_set(::ca::application * papp) :
      ca(papp),
      property_set(papp, true, true)
   {
   }



   relation_set::~relation_set()
   {
   }


} // namespace gen



void prop_id_debug(::ca::application * papp)
{

   comparable_array < ::id > idaSchema;

   gen::property_set set(papp);

   idaSchema.add(set["prop1"]);


}
















string CLASS_DECL_ca operator + (const char * psz, const gen::property & prop)
{
   return psz + prop.get_value();
}


string CLASS_DECL_ca operator + (const string & str, const gen::property & prop)
{
   return str + prop.get_value();
}
















var CLASS_DECL_ca operator - (int32_t i, const gen::property & prop)
{
   return i - prop.get_value();
}


var CLASS_DECL_ca operator - (uint32_t user, const gen::property & prop)
{
   return user - prop.get_value();
}


var CLASS_DECL_ca operator - (int64_t l, const gen::property & prop)
{
   return l - prop.get_value();
}


var CLASS_DECL_ca operator - (uint64_t ul, const gen::property & prop)
{
   return ul - prop.get_value();
}


var CLASS_DECL_ca operator - (double d, const gen::property & prop)
{
   return d - prop.get_value();
}


var CLASS_DECL_ca operator - (const var & var, const gen::property & prop)
{
   return var - prop.get_value();
}


var CLASS_DECL_ca operator - (const gen::property & prop1, const gen::property & prop2)
{
   return prop1.get_value() - prop2.get_value();
}
















var CLASS_DECL_ca operator + (int32_t i, const gen::property & prop)
{
   return i + prop.get_value();
}


var CLASS_DECL_ca operator + (uint32_t user, const gen::property & prop)
{
   return user + prop.get_value();
}


var CLASS_DECL_ca operator + (int64_t l, const gen::property & prop)
{
   return l + prop.get_value();
}


var CLASS_DECL_ca operator + (uint64_t ul, const gen::property & prop)
{
   return ul + prop.get_value();
}


var CLASS_DECL_ca operator + (double d, const gen::property & prop)
{
   return d + prop.get_value();
}


var CLASS_DECL_ca operator + (const var & var, const gen::property & prop)
{
   return var + prop.get_value();
}


var CLASS_DECL_ca operator + (const gen::property & prop1, const gen::property & prop2)
{
   return prop1.get_value() + prop2.get_value();
}
















var CLASS_DECL_ca operator / (int32_t i, const gen::property & prop)
{
   return i / prop.get_value();
}


var CLASS_DECL_ca operator / (uint32_t user, const gen::property & prop)
{
   return user / prop.get_value();
}


var CLASS_DECL_ca operator / (int64_t l, const gen::property & prop)
{
   return l / prop.get_value();
}


var CLASS_DECL_ca operator / (uint64_t ul, const gen::property & prop)
{
   return ul / prop.get_value();
}


var CLASS_DECL_ca operator / (double d, const gen::property & prop)
{
   return d / prop.get_value();
}


var CLASS_DECL_ca operator / (const var & var, const gen::property & prop)
{
   return var / prop.get_value();
}


var CLASS_DECL_ca operator / (const gen::property & prop1, const gen::property & prop2)
{
   return prop1.get_value() / prop2.get_value();
}
















var CLASS_DECL_ca operator * (int32_t i, const gen::property & prop)
{
   return i * prop.get_value();
}


var CLASS_DECL_ca operator * (uint32_t user, const gen::property & prop)
{
   return user * prop.get_value();
}


var CLASS_DECL_ca operator * (int64_t l, const gen::property & prop)
{
   return l * prop.get_value();
}


var CLASS_DECL_ca operator * (uint64_t ul, const gen::property & prop)
{
   return ul * prop.get_value();
}


var CLASS_DECL_ca operator * (double d, const gen::property & prop)
{
   return d * prop.get_value();
}


var CLASS_DECL_ca operator * (const var & var, const gen::property & prop)
{
   return var * prop.get_value();
}


var CLASS_DECL_ca operator * (const gen::property & prop1, const gen::property & prop2)
{
   return prop1.get_value() * prop2.get_value();
}
















































