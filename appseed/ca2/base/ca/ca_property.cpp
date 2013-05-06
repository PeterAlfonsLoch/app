#include "framework.h"

#if defined(LINUX)
#include <ctype.h>
#endif

#define ROUND(x,y) (((x)+(y-1))&~(y-1))
#define ROUND16(x) ROUND(x, 16)

void prop_id_debug(sp(::ca::application) papp);




namespace ca
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

   property::property(::ca::application * papp) :
      ::ca::ca(papp)
   {
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
         if(m_idName.is_empty())
         {
            m_idName      = prop.m_idName;
         }
         m_var = prop.m_var;
      }
      return *this;
   }


   property::property()
   {
//      m_pset = ::null();
   }

   property::property(const property & prop)
   {
      property::operator = ((const property &) prop);
   }


   property::property(id strName)
   {
      m_idName = strName;
   }

   property::property(id strName, var var)
   {
      m_idName = strName;
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
      ::ca::str::consume_spaces(pszJson, 0, pszEnd);
      string str = ::ca::str::consume_quoted_value(pszJson, pszEnd);
      m_idName = str;
      ::ca::str::consume(pszJson, ":", 1, pszEnd);
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

   property & property::operator[](id idName)
   {
      return propset().operator [](idName);
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

   void property::write(::ca::byte_output_stream & ostream)
   {
      ostream << m_idName;
      ostream << get_value();
   }

   void property::read(::ca::byte_input_stream & istream)
   {
      istream >> m_idName;
      istream >> get_value();
   }

   ::count property::get_count() const
   {
      return get_value().get_count();
   }

   ::count property::array_get_count() const
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

   property_array::property_array(sp(::ca::application) papp) :
      ::ca::ca(papp)
   {
      set_size(0, 64);
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
         strPost += m_propertya.element_at(i)->name();
         strPost += "=";
         strPost += System.url().url_encode(m_propertya.element_at(i)->get_value().get_string());
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
      ASSERT(psz != ::null());
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

   void property_set::write(::ca::byte_output_stream & ostream)
   {
      ostream << m_bAutoAdd;
      ostream << m_bMultiValue;
      //ostream << m_bKeyCaseInsensitive;
      ostream << m_propertya;
   }

   void property_set::read(::ca::byte_input_stream & istream)
   {
      istream >> m_bAutoAdd;
      istream >> m_bMultiValue;
      //istream >> m_bKeyCaseInsensitive;
      istream >> m_propertya;
      for(int32_t i = 0; i < m_propertya.get_count(); i++)
      {
         //if(m_bKeyCaseInsensitive)
         /*{
            m_map.set_at(m_propertya[i].lowname(), i);
         }
         else
         {*/
            m_map.set_at(m_propertya[i].name(), i);
         //}
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
         ::lemon::copy(m_propertya, set.m_propertya);
         m_bAutoAdd              = set.m_bAutoAdd;
         m_bMultiValue           = set.m_bMultiValue;
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
            m_propertya.add(canew(property(strKey, var)));
         }
         // WOULD ANALYZE each of the following members parameters for
         // auto discovery, calculation or leave as set.
         m_bAutoAdd              = set.get_auto_add();
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
            m_propertya.add(canew(property(strKey, var)));
         }
         // WOULD ANALYZE each of the following members parameters for
         // auto discovery, calculation or leave as set.
         m_bAutoAdd              = set.get_auto_add();
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










































   relation_set::relation_set(sp(::ca::application) papp) :
      ca(papp),
      property_set(papp, true, true)
   {
   }



   relation_set::~relation_set()
   {
   }


} // namespace ca



void prop_id_debug(sp(::ca::application) papp)
{

   comparable_array < ::id > idaSchema;

   ::ca::property_set set(papp);

   idaSchema.add(set["prop1"]);


}
















string CLASS_DECL_ca2 operator + (const char * psz, const ::ca::property & prop)
{
   return psz + prop.get_value();
}


string CLASS_DECL_ca2 operator + (const string & str, const ::ca::property & prop)
{
   return str + prop.get_value();
}
















var CLASS_DECL_ca2 operator - (int32_t i, const ::ca::property & prop)
{
   return i - prop.get_value();
}


var CLASS_DECL_ca2 operator - (uint32_t user, const ::ca::property & prop)
{
   return user - prop.get_value();
}


var CLASS_DECL_ca2 operator - (int64_t l, const ::ca::property & prop)
{
   return l - prop.get_value();
}


var CLASS_DECL_ca2 operator - (uint64_t ul, const ::ca::property & prop)
{
   return ul - prop.get_value();
}


var CLASS_DECL_ca2 operator - (double d, const ::ca::property & prop)
{
   return d - prop.get_value();
}


var CLASS_DECL_ca2 operator - (const var & var, const ::ca::property & prop)
{
   return var - prop.get_value();
}


var CLASS_DECL_ca2 operator - (const ::ca::property & prop1, const ::ca::property & prop2)
{
   return prop1.get_value() - prop2.get_value();
}
















var CLASS_DECL_ca2 operator + (int32_t i, const ::ca::property & prop)
{
   return i + prop.get_value();
}


var CLASS_DECL_ca2 operator + (uint32_t user, const ::ca::property & prop)
{
   return user + prop.get_value();
}


var CLASS_DECL_ca2 operator + (int64_t l, const ::ca::property & prop)
{
   return l + prop.get_value();
}


var CLASS_DECL_ca2 operator + (uint64_t ul, const ::ca::property & prop)
{
   return ul + prop.get_value();
}


var CLASS_DECL_ca2 operator + (double d, const ::ca::property & prop)
{
   return d + prop.get_value();
}


var CLASS_DECL_ca2 operator + (const var & var, const ::ca::property & prop)
{
   return var + prop.get_value();
}


var CLASS_DECL_ca2 operator + (const ::ca::property & prop1, const ::ca::property & prop2)
{
   return prop1.get_value() + prop2.get_value();
}
















var CLASS_DECL_ca2 operator / (int32_t i, const ::ca::property & prop)
{
   return i / prop.get_value();
}


var CLASS_DECL_ca2 operator / (uint32_t user, const ::ca::property & prop)
{
   return user / prop.get_value();
}


var CLASS_DECL_ca2 operator / (int64_t l, const ::ca::property & prop)
{
   return l / prop.get_value();
}


var CLASS_DECL_ca2 operator / (uint64_t ul, const ::ca::property & prop)
{
   return ul / prop.get_value();
}


var CLASS_DECL_ca2 operator / (double d, const ::ca::property & prop)
{
   return d / prop.get_value();
}


var CLASS_DECL_ca2 operator / (const var & var, const ::ca::property & prop)
{
   return var / prop.get_value();
}


var CLASS_DECL_ca2 operator / (const ::ca::property & prop1, const ::ca::property & prop2)
{
   return prop1.get_value() / prop2.get_value();
}
















var CLASS_DECL_ca2 operator * (int32_t i, const ::ca::property & prop)
{
   return i * prop.get_value();
}


var CLASS_DECL_ca2 operator * (uint32_t user, const ::ca::property & prop)
{
   return user * prop.get_value();
}


var CLASS_DECL_ca2 operator * (int64_t l, const ::ca::property & prop)
{
   return l * prop.get_value();
}


var CLASS_DECL_ca2 operator * (uint64_t ul, const ::ca::property & prop)
{
   return ul * prop.get_value();
}


var CLASS_DECL_ca2 operator * (double d, const ::ca::property & prop)
{
   return d * prop.get_value();
}


var CLASS_DECL_ca2 operator * (const var & var, const ::ca::property & prop)
{
   return var * prop.get_value();
}


var CLASS_DECL_ca2 operator * (const ::ca::property & prop1, const ::ca::property & prop2)
{
   return prop1.get_value() * prop2.get_value();
}
















































