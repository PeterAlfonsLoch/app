#include "StdAfx.h"

namespace gen
{
   CLASS_DECL_ca new_property g_newproperty;
   CLASS_DECL_ca null_property g_nullproperty;
   CLASS_DECL_ca empty_property g_emptyproperty;

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

   int pair_set_interface::pair_set_interface_find(const char * pszKey, int iStart) const
   {
      int iCount = pair_set_interface_get_count();
      if(get_key_case_insensitive())
      {
         for(int i = iStart; i < iCount; i++)
         {
            if(string(pair_set_interface_get_key(i)).CompareNoCase(pszKey) == 0)
            {
               return i;
            }
         }
      }
      else
      {
         for(int i = iStart; i < iCount; i++)
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
      int iFind = pair_set_interface_find(pszName);
      if(iFind >= 0)
         return pair_set_interface_get_value(iFind);
      if(get_auto_add())
      {
         pair_set_interface_set(pszName, g_newconst);
         iFind = pair_set_interface_find(pszName);
         if(iFind >= 0)
            return pair_set_interface_get_value(iFind);
      }
      return g_newconst;
   }

   var pair_set_interface::operator[](const char * pszName) const
   {
      int iFind = pair_set_interface_find(pszName);
      if(iFind >= 0)
         return pair_set_interface_get_value(iFind);
      return g_newconst;
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

   int str_str_interface::str_str_interface_find(const char * pszKey, int iStart) const
   {
      int iCount = str_str_interface_get_count();
      if(get_key_case_insensitive())
      {
         for(int i = iStart; i < iCount; i++)
         {
            if(string(str_str_interface_get_key(i)).CompareNoCase(pszKey) == 0)
            {
               return i;
            }
         }
      }
      else
      {
         for(int i = iStart; i < iCount; i++)
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
      int iFind = str_str_interface_find(pszName);
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
      int iFind = str_str_interface_find(pszName);
      if(iFind >= 0)
         return str_str_interface_get_value(iFind);
      return empty_string();
   }

   void property::get_value(var & value, int iIndex)
   {
      value = get_value(iIndex);
   }

   void property::get(var & value, int iIndex)
   {
      value = get_value(iIndex);
   }

   var property::get_value(int iIndex) const
   {
      return get_value(iIndex);
   }

   var & property::get(int iIndex)
   {
      return get_value(iIndex);
   }

   void property::set(const var & var, int iIndex)
   {
      set_value(var, iIndex);
   }

   void property::unset(int iIndex)
   {
      get_value(iIndex).unset();
   }

   int property::get_value_count()
   {
      return 1;
   }

   string property::operator + (const char * psz) const
   {
      return get_value() + psz;
   }
   
   string property::operator + (const string & str) const
   {
      return get_value() + str;
   }

   string CLASS_DECL_ca operator + (const char * psz, property & prop)
   {
      return psz + prop.get_value();
   }

   string CLASS_DECL_ca operator + (const string & str, property & prop)
   {
      return str + prop.get_value();
   }


   property & property::operator =(const property & prop)
   {
      if(&prop != this)
      {
         if(m_strName.is_empty())
         {
            m_strName = prop.m_strName;
         }
         set_value((( property & ) prop).get_value());
      }
      return *this;
   }



   var & var_property::get_value(int iIndex)
   {
      if(iIndex < 0)
      {
         if(m_vara.get_count() == 0)
            m_vara.set_size(1);
         return m_vara.last_element();
      }
      else
         return m_vara[iIndex];
   }

   int var_property::get_value_count()
   {
      return m_vara.get_count();
   }

   var var_property::get_value(int iIndex) const
   {
      if(iIndex < 0)
      {
         ASSERT(m_vara.get_count() > 0);
         return m_vara.last_element();
      }
      else
         return m_vara[iIndex];
   }

   void var_property::set_value(const var & var, int iIndex)
   {
      if(m_pset != NULL && m_pset->m_bMultiValue)
      {
         if(iIndex == -1)
         {
            m_vara.add(var);
         }
         else
         {
            m_vara.set_at_grow(iIndex, var);
         }
      }
      else
      {
         m_vara.set_at_grow(0, var);
      }
   }

   var & new_property::get_value(int iIndex)
   {
      UNREFERENCED_PARAMETER(iIndex);
      return m_newconst;
   }

   void new_property::set_value(const var & var, int iIndex)
   {
      UNREFERENCED_PARAMETER(var);
      UNREFERENCED_PARAMETER(iIndex);
      throw "unsupported!";
   }


   var & null_property::get_value(int iIndex)
   {
      UNREFERENCED_PARAMETER(iIndex);
      return m_nullconst;
   }

   void null_property::set_value(const var & var, int iIndex)
   {
      UNREFERENCED_PARAMETER(var);
      UNREFERENCED_PARAMETER(iIndex);
      throw "unsupported!";
   }

   var & empty_property::get_value(int iIndex)
   {
      UNREFERENCED_PARAMETER(iIndex);
      return m_emptyconst;
   }

   void empty_property::set_value(const var & var, int iIndex)
   {
      UNREFERENCED_PARAMETER(var);
      UNREFERENCED_PARAMETER(iIndex);
      throw "unsupported!";
   }

   property::property(void)
   {
      m_pset = NULL;
   }

   var_property::var_property()
   {
   }

   var_property::var_property(const var_property & prop)
   {
      property::operator = ((const property &) prop);
   }

   var_property::var_property(const property & prop)
   {
      property::operator = (prop);
   }

   var_property::var_property(const char * pszName)
   {
      m_strName = pszName;
   }


   var_property::var_property(int iId)
   {
      m_strName.Format("id=%d", iId);
   }

   var_property::var_property(const char * pszName, var & var)
   {
      m_strName = pszName;
      set_value(var);
   }

   var_property & var_property::operator = (const var_property & prop)
   {
      if(&prop != this)
      {
         if(m_strName.is_empty())
         {
            m_strName = prop.m_strName;
         }
         get_value() = ((property &) prop).get_value();
      }
      return *this;
   }

   property::~property(void)
   {
   }

   string & property::name()
   {
      return m_strName;
   }

   string property::name() const
   {
      return m_strName;
   }

   void property::set_value(const var & value, int iIndex)
   {
      UNREFERENCED_PARAMETER(iIndex);
      if(m_pset != NULL)
         m_pset->OnBeforePropertyChange(this);
      var variableOld = get_value();
      set_value(value);
      if(m_pset != NULL)
         m_pset->OnAfterPropertyChange(variableOld, this);
   
   }

   bool property::is_set(int iIndex) const
   {
     return get_value(iIndex).is_set();
   }

   bool property::is_new(int iIndex) const
   {
      return get_value(iIndex).is_new();
   }

   bool property::is_null(int iIndex) const
   {
      return get_value(iIndex).is_null();
   }

   bool property::is_new_or_null(int iIndex) const
   {
      return get_value(iIndex).is_new_or_null();
   }

   bool property::is_empty(int iIndex) const
   {
      return get_value(iIndex).is_empty();
   }

   bool property::is_true(int iIndex) const
   {
      return get_value(iIndex).is_true();
   }

   string property::implode(const char * pszGlue, int iIndex) const
   {
      return get_value(iIndex).implode(pszGlue);
   }


   stringa & property::stra(int iIndex)
   {
      return get_value(iIndex).stra();
   }

   int_array & property::inta(int iIndex)
   {
      return get_value(iIndex).inta();
   }

   var_array & property::vara(int iIndex)
   {
      return get_value(iIndex).vara();
   }

   property_set & property::propset(int iIndex)
   {
      return get_value(iIndex).propset();
   }

   const stringa & property::stra(int iIndex) const
   {
      return get_value(iIndex).stra();
   }

   const int_array & property::inta(int iIndex) const
   {
      return get_value(iIndex).inta();
   }

   const var_array & property::vara(int iIndex) const
   {
      return get_value(iIndex).vara();
   }

   const property_set & property::propset(int iIndex) const
   {
      return get_value(iIndex).propset();
   }

   int property::get_length() const
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

   property & property::operator[](int iId)
   {
      return propset().operator [](iId);
   }

   var property::element_at(int iIndex) const
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
         if(const_cast<property *>(this)->get_count(iIndex) == 1)
            return const_cast<property *>(this)->get_value();
         throw "unsuported!!";
      }
   }

   var property::at(int iIndex) const
   {
      return element_at(iIndex);
   }

   void property::write(ex1::output_stream & ostream)
   {
      ostream << m_strName;
      ostream << get_value();
   }

   void property::read(ex1::input_stream & istream)
   {
      istream >> m_strName;
      istream >> get_value();
   }

   int property::get_count(int iIndex) const
   {
      return get_value(iIndex).get_count();
   }

   int property::array_get_count(int iIndex) const
   {
      return get_value(iIndex).array_get_count();
   }

   bool property::array_contains(const char * psz, int iIndex, index first, index last) const
   {
      return get_value(iIndex).array_contains(psz, first, last);
   }

   bool property::array_contains_ci(const char * psz, int iIndex, index first, index last) const
   {
      return get_value(iIndex).array_contains_ci(psz, first, last);
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


   int property::compare_value_ci(const char * psz, int iIndex) const
   {
      return get_value(iIndex).compare_ci(psz);
   }

   variable_strict_compare property::strict_compare() const
   {
      return const_cast < property * >(this)->get_value();
   }

   int property::str_compare(const property & prop) const
   {
      int iCompare = m_strName.Compare(prop.m_strName);
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

   bool property::strict_equal(int i) const
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

   bool property::strict_different(int i) const
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

   bool property::operator == (int i) const
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

   bool property::operator != (int i) const
   {
      return get_value() != i;
   }

   bool property::operator != (bool b) const
   {
      return get_value() != b;
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

   bool property::operator < (int i) const
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

   bool property::operator <= (int i) const
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

   bool property::operator >= (int i) const
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

   bool property::operator > (int i) const
   {
      return get_value() > i;
   }

   bool property::operator > (bool b) const
   {
      return get_value() > b;
   }




   string CLASS_DECL_ca operator + (const char * psz, const property & prop)
   {
      return psz + prop.get_value();
   }

   string CLASS_DECL_ca operator + (const string & str, const property & prop)
   {
      return str + prop.get_value();
   }


   var property::operator - (int i) const
   {
      return get_value() - i;
   }

   var property::operator - (unsigned int user) const
   {
      return get_value() - user;
   }

   var property::operator - (long i) const
   {
      return get_value() - i;
   }

   var property::operator - (unsigned long user) const
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


   var CLASS_DECL_ca operator - (int i, const property & prop)
   {
      return i - prop.get_value();
   }

   var CLASS_DECL_ca operator - (unsigned int user, const property & prop)
   {
      return user - prop.get_value();
   }

   var CLASS_DECL_ca operator - (long l, const property & prop)
   {
      return l - prop.get_value();
   }

   var CLASS_DECL_ca operator - (unsigned long ul, const property & prop)
   {
      return ul - prop.get_value();
   }

   var CLASS_DECL_ca operator - (double d, const property & prop)
   {
      return d - prop.get_value();
   }

   var CLASS_DECL_ca operator - (const var & var, const property & prop)
   {
      return var - prop.get_value();
   }

   var CLASS_DECL_ca operator - (const property & prop1, const property & prop2)
   {
      return prop1.get_value() - prop2.get_value();
   }


   var property::operator + (int i) const
   {
      return get_value() + i;
   }

   var property::operator + (unsigned int user) const
   {
      return get_value() + user;
   }

   var property::operator + (long i) const
   {
      return get_value() + i;
   }

   var property::operator + (unsigned long user) const
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


   var CLASS_DECL_ca operator + (int i, const property & prop)
   {
      return i + prop.get_value();
   }

   var CLASS_DECL_ca operator + (unsigned int user, const property & prop)
   {
      return user + prop.get_value();
   }

   var CLASS_DECL_ca operator + (long l, const property & prop)
   {
      return l + prop.get_value();
   }

   var CLASS_DECL_ca operator + (unsigned long ul, const property & prop)
   {
      return ul + prop.get_value();
   }

   var CLASS_DECL_ca operator + (double d, const property & prop)
   {
      return d + prop.get_value();
   }

   var CLASS_DECL_ca operator + (const var & var, const property & prop)
   {
      return var + prop.get_value();
   }

   var CLASS_DECL_ca operator + (const property & prop1, const property & prop2)
   {
      return prop1.get_value() + prop2.get_value();
   }













































   var property::operator / (int i) const
   {
      return get_value() / i;
   }

   var property::operator / (unsigned int user) const
   {
      return get_value() / user;
   }

   var property::operator / (long i) const
   {
      return get_value() / i;
   }

   var property::operator / (unsigned long user) const
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


   var CLASS_DECL_ca operator / (int i, const property & prop)
   {
      return i / prop.get_value();
   }

   var CLASS_DECL_ca operator / (unsigned int user, const property & prop)
   {
      return user / prop.get_value();
   }

   var CLASS_DECL_ca operator / (long l, const property & prop)
   {
      return l / prop.get_value();
   }

   var CLASS_DECL_ca operator / (unsigned long ul, const property & prop)
   {
      return ul / prop.get_value();
   }

   var CLASS_DECL_ca operator / (double d, const property & prop)
   {
      return d / prop.get_value();
   }

   var CLASS_DECL_ca operator / (const var & var, const property & prop)
   {
      return var / prop.get_value();
   }

   var CLASS_DECL_ca operator / (const property & prop1, const property & prop2)
   {
      return prop1.get_value() / prop2.get_value();
   }


   var property::operator * (int i) const
   {
      return get_value() * i;
   }

   var property::operator * (unsigned int user) const
   {
      return get_value() * user;
   }

   var property::operator * (long i) const
   {
      return get_value() * i;
   }

   var property::operator * (unsigned long user) const
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


   var CLASS_DECL_ca operator * (int i, const property & prop)
   {
      return i * prop.get_value();
   }

   var CLASS_DECL_ca operator * (unsigned int user, const property & prop)
   {
      return user * prop.get_value();
   }

   var CLASS_DECL_ca operator * (long l, const property & prop)
   {
      return l * prop.get_value();
   }

   var CLASS_DECL_ca operator * (unsigned long ul, const property & prop)
   {
      return ul * prop.get_value();
   }

   var CLASS_DECL_ca operator * (double d, const property & prop)
   {
      return d * prop.get_value();
   }

   var CLASS_DECL_ca operator * (const var & var, const property & prop)
   {
      return var * prop.get_value();
   }

   var CLASS_DECL_ca operator * (const property & prop1, const property & prop2)
   {
      return prop1.get_value() * prop2.get_value();
   }















































   property & property::operator -= (int i)
   {
      operator=(*this - i);
      return *this;
   }

   property & property::operator -= (unsigned int user)
   {
      operator=(*this - user);
      return *this;
   }

   property & property::operator -= (long i)
   {
      operator=(*this - i);
      return *this;
   }

   property & property::operator -= (unsigned long user)
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
      operator=(*this - prop);
      return *this;
   }























































   property & property::operator += (int i)
   {
      operator=(*this + i);
      return *this;
   }

   property & property::operator += (unsigned int user)
   {
      operator=(*this + user);
      return *this;
   }

   property & property::operator += (long i)
   {
      operator=(*this + i);
      return *this;
   }

   property & property::operator += (unsigned long user)
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
      operator=(*this + prop);
      return *this;
   }



























   property & property::operator /= (int i)
   {
      operator=(*this / i);
      return *this;
   }

   property & property::operator /= (unsigned int user)
   {
      operator=(*this / user);
      return *this;
   }

   property & property::operator /= (long i)
   {
      operator=(*this / i);
      return *this;
   }

   property & property::operator /= (unsigned long user)
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
      operator=(*this / prop);
      return *this;
   }

























   property & property::operator *= (int i)
   {
      operator=(*this * i);
      return *this;
   }

   property & property::operator *= (unsigned int user)
   {
      operator=(*this * user);
      return *this;
   }

   property & property::operator *= (long i)
   {
      operator=(*this * i);
      return *this;
   }

   property & property::operator *= (unsigned long user)
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
      operator=(*this * prop);
      return *this;
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

   property * property_set::add(const char * pszName, var var)
   {
      string strName;
      if(pszName == NULL)
      {
         index iMax = -1;
         index idx;
         for(int i = 0; i < m_propertya.get_count(); i++)
         {
            if(m_propertya[i].name() == "0")
            {
               idx = 0;
            }
            else
            {
               idx = atoi(m_propertya[i].name());
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
      m_propertya.add(var_property(strName, var));
      m_propertya.last_element().m_pset = this;
      return &m_propertya.last_element();
   }

   property * property_set::set(const char * pszName, var var)
   {
      property * p = find(pszName);
      if(p != NULL)
      {
         p->get_value() = var;
         return p;
      }
      else
      {
         m_propertya.add(var_property(pszName, var));
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
      return g_newproperty;
   }

   bool property_set::has_property(const char * pszName, index find, index last) const
   {
      return find_first(pszName, find, last) >= 0 && operator[](pszName).get_value().get_type() != var::type_new;
   }

   bool property_set::has_property(string_interface & str, index find, index last) const
   {
      return has_property((const char *) string(str), find, last);
   }

   bool property_set::is_set_empty(count countMinimum) const
   {
      return m_propertya.get_count() < countMinimum;
   }

   bool property_set::has_properties(count countMinimum) const
   {
      return m_propertya.get_count() >= countMinimum;
   }


   index property_set::find_var_ci(const var & var, index find, index last) const
   {
      if(find < 0)
         find += m_propertya.get_count();
      if(last < 0)
         last += m_propertya.get_count();
      for(; find <= last; find++)
      {
         if(m_propertya[find].get_value().compare_ci(var) == 0)
            return find;
      }
      return -1;
   }

   index property_set::find_value_ci(var var, index find, index last) const
   {
      return find_var_ci(var, find, last);
   }


   index property_set::find_var(const var & var, index find, index last) const
   {
      if(find < 0)
         find += m_propertya.get_count();
      if(last < 0)
         last += m_propertya.get_count();
      for(; find <= last; find++)
      {
         if(m_propertya[find].get_value() == var)
            return find;
      }
      return -1;
   }

   index property_set::find_value(var var, index find, index last) const
   {
      return find_var(var, find, last);
   }

   bool property_set::contains_var_ci(const var & var, index find, index last, count countMin, count countMax) const
   {
      count count = 0;
      while((count < countMin || (countMax >= 0 && count <= countMax))
         && (find = find_var_ci(var, find, last)) >= 0)
         count++;
      return count >= countMin && conditional(countMax >= 0, count <= countMax);
   }

   bool property_set::contains_value_ci(var var, index find, index last, count countMin, count countMax) const
   {
      return contains_var_ci(var, find, last, countMin, countMax);
   }

   bool property_set::contains_value_ci(const char * psz, index find, index last, count countMin, count countMax) const
   {
      count count = 0;
      while((count < countMin || (countMax >= 0 && count <= countMax))
         && (find = find_value_ci(psz, find, last)) >= 0)
         count++;
      return count >= countMin && conditional(countMax >= 0, count <= countMax);
   }


   bool property_set::contains_var(const var & var, index find, index last, count countMin, count countMax) const
   {
      count count = 0;
      while((count < countMin || (countMax >= 0 && count <= countMax))
         && (find = find_var(var, find, last)) >= 0)
         count++;
      return count >= countMin && conditional(countMax >= 0, count <= countMax);
   }

   bool property_set::contains_value(var var, index find, index last, count countMin, count countMax) const
   {
      return contains_var(var, find, last, countMin, countMax);
   }

   bool property_set::contains_value(const char * psz, index find, index last, count countMin, count countMax) const
   {
      count count = 0;
      while((count < countMin || (countMax >= 0 && count <= countMax))
         && (find = find_value(psz, find, last)) >= 0)
         count++;
      return count >= countMin && conditional(countMax >= 0, count <= countMax);
   }

   index property_set::remove_first_var_ci(const var & var, index find, index last)
   {
      if((find = find_var_ci(var, find, last)) >= 0)
         m_propertya.remove_at(find);
      return find;
   }

   index property_set::remove_first_value_ci(var var, index find, index last)
   {
      return remove_first_var_ci(var, find, last);
   }

   index property_set::remove_first_value_ci(const char * lpcsz, index find, index last)
   {
      if((find = find_value_ci(lpcsz, find, last)) >= 0)
         m_propertya.remove_at(find);
      return find;
   }

   index property_set::remove_first_var(const var & var, index find, index last)
   {
      if((find = find_var(var, find, last)) >= 0)
         m_propertya.remove_at(find);
      return find;
   }

   index property_set::remove_first_value(var var, index find, index last)
   {
      return remove_first_var(var, find, last);
   }

   index property_set::remove_first_value(const char * lpcsz, index find, index last)
   {
      if((find = find_value(lpcsz, find, last)) >= 0)
         m_propertya.remove_at(find);
      return find;
   }


   count property_set::remove_var_ci(const var & var, index find, index last, count countMin, count countMax)
   {
      count count = 0;
      if(contains_var_ci(var, find, last, countMin, countMax))
         while(conditional(countMax >= 0, count < countMax)
            && (find = remove_first_var_ci(var, find, last)) >= 0)
            count++;
      return count;
   }

   count property_set::remove_value_ci(var var, index find, index last, count countMin, count countMax)
   {
      return remove_var_ci(var, find, last, countMin, countMax);
   }

   count property_set::remove_value_ci(const char * psz, index find, index last, count countMin, count countMax)
   {
      count count = 0;
      if(contains_value_ci(psz, find, last, countMin, countMax))
         while(conditional(countMax >= 0, count < countMax)
            && (find = remove_first_value_ci(psz, find, last)) >= 0)
            count++;
      return count;
   }

   count property_set::remove_var(const var & var, index find, index last, count countMin, count countMax)
   {
      count count = 0;
      if(contains_var(var, find, last, countMin, countMax))
         while(conditional(countMax >= 0, count < countMax)
            && (find = remove_first_var(var, find, last)) >= 0)
            count++;
      return count;
   }

   count property_set::remove_value(var var, index find, index last, count countMin, count countMax)
   {
      return remove_var(var, find, last, countMin, countMax);
   }

   count property_set::remove_value(const char * psz, index find, index last, count countMin, count countMax)
   {
      count count = 0;
      if(contains_value(psz, find, last, countMin, countMax))
         while(conditional(countMax >= 0, count < countMax)
            && (find = remove_first_value(psz, find, last)) >= 0)
            count++;
      return count;
   }



   index property_set::find_first(const char * pszName, index find, index last) const
   {
      if(find < 0)
         find += m_propertya.get_count();
      if(last < 0)
         last += m_propertya.get_count();
      if(m_bKeyCaseInsensitive)
      {
         for(; find <= last; find++)
         {
            if(m_propertya[find].m_strName.CompareNoCase(pszName) == 0)
               return find;
         }
      }
      else
      {
         for(; find <= last; find++)
         {
            if(m_propertya[find].m_strName.Compare(pszName) == 0)
               return find;
         }
      }
      return -1;
   }


   index property_set::find_first(string_interface & str, index find, index last) const
   {
      return find_first((const char *) string(str), find, last);
   }

   count property_set::unset(const char * pszName)
   {
      count countRemove = 0;
restart_finding:
      index iFind = find_first(pszName);
      if(iFind >= 0)
      {
         m_propertya.remove_at(iFind);
         countRemove++;
         goto restart_finding;
      }
      return countRemove;
   }

   property * property_set::find(const char * pszName, index find, index last)
   {
      if((find = find_first(pszName, find, last)) >= 0)
         return &m_propertya[find];
      return NULL;
   }

   property * property_set::find(string_interface & str, index first, index last)
   {
      return find((const char *) string(str), first, last);
   }

   const property * property_set::find(const char * pszName, index find, index last) const
   {
      if((find = find_first(pszName, find, last)) >= 0)
         return &m_propertya[find];
      return NULL;
   }

   const property * property_set::find(string_interface & str, index first, index last) const
   {
      return find((const char *) string(str), first, last);
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

   void property_set::_008Parse(const char * pszCmdLine)
   {
      if(*pszCmdLine == '\0')
         return;
      pszCmdLine++;
      if(*pszCmdLine == '\0')
         return;
      string str;
      string strKey;
      string strValue;
      bool bQuote = false;
      bool bKey = true;
      // find " : "
      while(*pszCmdLine != '\0')
      {
         if(*(pszCmdLine - 1) == ' '
         &&  *pszCmdLine == ':'
         && *(pszCmdLine + 1) == ' ')
         {
            pszCmdLine += 2;
            break;
         }
         pszCmdLine++;
      }
      while(*pszCmdLine != '\0')
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
                  add(strKey, var(strValue));
                  strKey.Empty();
               }
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
               || *pszCmdLine == '\t' || *pszCmdLine == ' ')
            {
               if(bKey)
               {
                  strKey = str;
                  add(strKey, var(strValue));
                  strKey.Empty();
                  str.Empty();
               }
               else if(!strKey.is_empty())
               {
                  strValue = str;
                  add(strKey, var(strValue));
                  strKey.Empty();
                  str.Empty();
               }
               bKey = true;
            }
            else
            {
               str += *pszCmdLine;
            }
         }
         pszCmdLine++;
      }
      if(bKey)
      {
         strKey = str;
         add(strKey, var(strValue));
         strKey.Empty();
         str.Empty();
      }
      else if(!strKey.is_empty())
      {
         strValue = str;
         add(strKey, var(strValue));
         strKey.Empty();
         str.Empty();
      }
   }

   void property_set::parse_url_query(const char * pszUrlQuery)
   {
      stringa stra;
      string strQuery(pszUrlQuery);
      strQuery.trim();
      if(strQuery.find("?") >= 0)
      {
         strQuery = System.url().get_query(strQuery);
      }
      stra.add_tokens(strQuery, "&", TRUE);
      for(int i = 0; i < stra.get_size(); i++)
      {
         string & str = stra[i];
         if(str.get_length() > 0)
         {
            index find = str.find("=");
            if(find <= 0)
            {
               string strKey = System.url().url_decode(str);
               bool bAddArray = gen::str::ends_eat(strKey, "[]");
               if(bAddArray)
               {
                  operator[](strKey).stra().add("");
               }
               else
               {
                  operator[](strKey).get_value() = "";
               }
            }
            else
            {
               string strKey = System.url().url_decode(str.Mid(0, find));
               bool bAddArray = gen::str::ends_eat(strKey, "[]");
               string strValue = System.url().url_decode(str.Mid(find + 1));
               if(bAddArray)
               {
                  operator[](strKey).stra().add(strValue);
               }
               else
               {
                  add(strKey, var(strValue));
               }
            }
         }
      }
   }

   void property_set::parse_http_headers(const char * pszHeaders)
   {
      stringa stra;
      stra.add_tokens(pszHeaders, "\r\n", TRUE);
      string strName;
      for(int i = 0; i < stra.get_size(); i++)
      {
         int iPos = stra[i].find(":");
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

   index property_set::remove_first_by_name(const char * pszName, index find, index last)
   {
      if((find = find_first(pszName, find, last)) >= 0)
         m_propertya.remove_at(find);
      return find;
   }


   count property_set::remove_by_name(const char * pszName, index find, index last)
   {
      count count = 0;
      while((find = remove_first_by_name(pszName, find, last)) >= 0)
         count++;
      return count;
   }

   count property_set::remove_by_name(stringa & stra)
   {
      count count = 0;
      for(int i = 0; i < stra.get_count(); i++)
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
      for(int i = 0; i < m_propertya.get_size(); i++)
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
         opt = System.m_poptionDefault;
      }

      string str;

      str = name();
      str += "=";
      str += opt->value_quotation_mark;
      if(opt->reference_value && opt->m_pentities)
         str += opt->m_pentities->entity_to_ref(get_string());
      else
         str += get_string();
      str += opt->value_quotation_mark;
      str += " ";

      return str;
   }



   void property_set::replace_ex1(string & str)
   {
      int iPos;
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
            int iEnd = str.find('}', iPos + 1);
            if(iEnd < 0)
            {
               //error
               break;
            }
            string strEval = ex2_eval(str.Mid(iPos + 1, iEnd - iPos - 1));
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
            int iStart = iPos;
            int iEnd = iStart + 2;
            for(; iEnd < str.get_length(); iEnd++)
            {
               ch = str[iEnd];
               if(!(isalpha(ch) || ch == '_' || isdigit(ch)))
               {
                  break;
               }
            }
            string strEval = ex2_eval(str.Mid(iStart, iEnd - iStart));
            str = str.Left(iPos) + strEval + str.Mid(iEnd);
            iPos += strEval.get_length() - 1;
         }
      }
   }

   string property_set::eval(const char * psz)
   {
      string str = psz;
      replace_ex1(str);
      return str;
   }


   string property_set::ex2_eval(const char * psz)
   {
      string str;
      ASSERT(psz != NULL);
      ASSERT(psz[0] == '$'); // until now accepts only one var
      ASSERT(strlen(psz) >= 2);
      str = operator [](&psz[1]);   
      replace_ex1(str);
      return str;
   }

   void property_set::clear()
   {
      m_propertya.remove_all();
   }

   void property_set::write(ex1::output_stream & ostream)
   {
      ostream << m_bAutoAdd;
      ostream << m_bMultiValue;
      ostream << m_bKeyCaseInsensitive;
      ostream << m_propertya;
   }

   void property_set::read(ex1::input_stream & istream)
   {
      istream >> m_bAutoAdd;
      istream >> m_bMultiValue;
      istream >> m_bKeyCaseInsensitive;
      istream >> m_propertya;
   }

   string property_set::implode(const char * pszGlue) const
   {
      string str;
      if(m_propertya.get_count() > 0)
      {
         str = m_propertya[0].get_value().get_string();
      }
      for(int i = 1; i < m_propertya.get_count(); i++)
      {
         str += pszGlue;
         str += m_propertya[i].get_value().get_string();
      }
      return str;
   }

   count property_set::get_count() const
   {
      return m_propertya.get_count();
   }

   index property_set::find_value(const char * psz, index find, index last) const
   {
      if(find < 0)
         find += m_propertya.get_count();
      if(last < 0)
         last += m_propertya.get_count();
      for(; find <= last; find++)
      {
         if(m_propertya[find].get_string() == psz)
            return find;
      }
      return -1;
   }

   index property_set::find_value_ci(const char * psz, index find, index last) const
   {
      if(find < 0)
         find += m_propertya.get_count();
      if(last < 0)
         last += m_propertya.get_count();
      for(; find <= last; find++)
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

   property & property_set::at(int iId)
   {
      if(iId >= m_propertya.get_size())
      {
         m_propertya.set_size(iId + 1);
      }
      return m_propertya[iId];
   }

   var_property property_set::at(int iId) const
   {
      if(iId >= m_propertya.get_size())
      {
         const_cast < property_set * > (this)->m_propertya.set_size(iId + 1);
      }
      return const_cast<property_set*>(this)->m_propertya[iId];
   }

   property_set & property_set::operator = (const property_set & set)
   {
      if(&set != this)
      {
         m_propertya.remove_all();
         for(int i = 0; i < set.m_propertya.get_count(); i++)
         {
            m_propertya.add(set.m_propertya[i]);
         }
         m_bAutoAdd              = set.m_bAutoAdd;
         m_bMultiValue           = set.m_bMultiValue;
         m_bKeyCaseInsensitive   = set.m_bKeyCaseInsensitive;
         for(int i = 0; i < m_propertya.get_count(); i++)
         {
            m_propertya[i].m_pset = this;
         }
      }
      return *this;
   }

   property_set & property_set::add(const property_set & set)
   {
      if(&set != this)
      {
         for(int i = 0; i < set.m_propertya.get_count(); i++)
         {
            ((var_property &)operator[](set.m_propertya[i].name())).m_vara.add(set.m_propertya[i].get_value());
         }
      }
      return *this;
   }

   

   property_set & property_set::operator = (const pair_set_interface & set)
   {
   //   if(&set != this)
      {
         m_propertya.remove_all();
         int iCount = set.pair_set_interface_get_count();
         for(int i = 0; i < iCount; i++)
         {
            string strKey = set.pair_set_interface_get_key(i);
            class var var = set.pair_set_interface_get_value(i);
            m_propertya.add(var_property(strKey, var));
         }
         // WOULD ANALYZE each of the following members parameters for
         // auto discovery, calculation or leave as set.
         m_bAutoAdd              = set.get_auto_add();
         //m_bMultiValue           = set.m_bMultiValue;
         m_bKeyCaseInsensitive   = set.get_key_case_insensitive();
         for(int i = 0; i < m_propertya.get_count(); i++)
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
         int iCount = set.str_str_interface_get_count();
         for(int i = 0; i < iCount; i++)
         {
            string strKey = set.str_str_interface_get_key(i);
            class var var = set.str_str_interface_get_value(i);
            m_propertya.add(var_property(strKey, var));
         }
         // WOULD ANALYZE each of the following members parameters for
         // auto discovery, calculation or leave as set.
         m_bAutoAdd              = set.get_auto_add();
         //m_bMultiValue           = set.m_bMultiValue;
         m_bKeyCaseInsensitive   = set.get_key_case_insensitive();
         for(int i = 0; i < m_propertya.get_count(); i++)
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
      for(; find < get_count(); find++)
      {
         if(m_propertya[find].str_compare(property) == 0)
            return find;
      }
      return -1;
   }



   bool property_set::str_contains(const property_set & set) const
   {

      for(index i = 0; i < m_propertya.get_count(); i++)
      {
         if(str_find(m_propertya[i]) < 0)
            return false;
      }
      return true;

   }


   var_property property_set::operator[](const char * pszName) const
   {
      return const_cast<property_set*>(this)->operator[](pszName);
   }

   property & property_set::operator[](int iId)
   {
      return operator[](gen::str::itoa(iId));
   }

   var_property property_set::operator[](int iId) const
   {
      return operator[](gen::str::itoa(iId));
   }

   property & property_set::operator[](const string_interface & str)
   {
      return operator[](string(str));
   }

   var_property property_set::operator[](const string_interface & str) const
   {
      return operator[](string(str));
   }

   property & property_set::operator[](const string & str)
   {
      return operator[]((const char *) str);
   }

   var_property property_set::operator[](const string & str) const
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