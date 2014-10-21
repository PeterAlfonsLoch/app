#include "framework.h"


property_set::property_set(sp(::aura::application) papp, bool bAutoAdd, bool bMultiValue) :
   element(papp),
   m_propertya(papp)
{
   m_bAutoAdd = bAutoAdd;
   m_bMultiValue = bMultiValue;
}


property_set::~property_set()
{
}

id property_set::get_new_id()
{
   index iMax = -1;
   index idx;
   ::property_pair pair(*this);
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
   string strName;
   strName.Format("%d", iMax + 1);
   return strName;
}






property & property_set::defer_auto_add(id idName)
{
   if(m_bAutoAdd)
   {
      property * pproperty = add(idName);
      if(pproperty != NULL)
         return *pproperty;
   }
   throw simple_exception(get_app(), "property with specified name - and specified case sensitivity - does not exist and Auto add Flag is not set");
}

bool property_set::is_set_empty(::count countMinimum) const
{
   return get_count() < countMinimum;
}

bool property_set::has_properties(::count countMinimum) const
{
   return get_count() >= countMinimum;
}


index property_set::find_var_ci(const var & var) const
{
   for(index find = 0; find < m_propertya.get_count(); find++)
   {
      if(m_propertya[find]->get_value().compare_ci(var) == 0)
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
      if(m_propertya[find]->get_value() == var)
         return find;
   }
   return -1;
}

index property_set::find_value(var var) const
{
   return find_var(var);
}

bool property_set::contains_var_ci(const var & var, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find_var_ci(var)) >= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}

bool property_set::contains_value_ci(var var, ::count countMin, ::count countMax) const
{
   return contains_var_ci(var, countMin, countMax);
}

bool property_set::contains_value_ci(const char * psz, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find_value_ci(psz)) >= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}


bool property_set::contains_var(const var & var, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find_var(var)) >= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}

bool property_set::contains_value(var var, ::count countMin, ::count countMax) const
{
   return contains_var(var, countMin, countMax);
}

bool property_set::contains_value(const char * psz, ::count countMin, ::count countMax) const
{
   ::count count = 0;
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


::count property_set::remove_var_ci(const var & var, ::count countMin, ::count countMax)
{
   ::count count = 0;
   if(contains_var_ci(var, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax)
         && (remove_first_var_ci(var)) >= 0)
         count++;
   return count;
}

::count property_set::remove_value_ci(var var, ::count countMin, ::count countMax)
{
   return remove_var_ci(var, countMin, countMax);
}

::count property_set::remove_value_ci(const char * psz, ::count countMin, ::count countMax)
{
   ::count count = 0;
   if(contains_value_ci(psz, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax)
         && (remove_first_value_ci(psz)) >= 0)
         count++;
   return count;
}

::count property_set::remove_var(const var & var, ::count countMin, ::count countMax)
{
   ::count count = 0;
   if(contains_var(var, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax)
         && (remove_first_var(var)) >= 0)
         count++;
   return count;
}

::count property_set::remove_value(var var, ::count countMin, ::count countMax)
{
   return remove_var(var, countMin, countMax);
}

::count property_set::remove_value(const char * psz, ::count countMin, ::count countMax)
{
   ::count count = 0;
   if(contains_value(psz, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax)
         && (remove_first_value(psz)) >= 0)
         count++;
   return count;
}


::count property_set::unset(id idName)
{
   property_map::pair * ppair = m_map.PLookup(idName);
   if(ppair == NULL)
      return 0;
   m_propertya.remove_at(ppair->m_element2);
   m_map.remove_key(ppair->m_element1);
   return 1;
}



bool property_set::is_new(id idName) const
{
   const property * pproperty = find(idName);
   if(pproperty == NULL)
      return true;
   return pproperty->is_new();
}

bool property_set::is_new(string_interface & str) const
{
   return is_new((const char *) string(str));
}

bool property_set::is_null(id idName) const
{
   const property * pproperty = find(idName);
   if(pproperty == NULL)
      return true;
   return pproperty->is_null();
}

bool property_set::is_null(string_interface & str) const
{
   return is_null((const char *) string(str));
}

bool property_set::is_new_or_null(id idName) const
{
   const property * pproperty = find(idName);
   if(pproperty == NULL)
      return true;
   return pproperty->is_new_or_null();
}

bool property_set::is_new_or_null(string_interface & str) const
{
   return is_new_or_null((const char *) string(str));
}


bool property_set::is_empty(id idName) const
{
   const property * pproperty = find(idName);
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
   PropertySignalObject signal_details(&m_signal);
   signal_details.m_etype = PropertySignalObject::TypeBeforeChange;
   signal_details.m_pproperty = pproperty;
   signal_details.m_pset = this;
   m_signal.emit(&signal_details);
}


void property_set::OnAfterPropertyChange(const var & variableOld, property * pproperty)
{
   UNREFERENCED_PARAMETER(variableOld);
   PropertySignalObject signal_details(&m_signal);
   signal_details.m_etype = PropertySignalObject::TypeAfterChange;
   signal_details.m_pproperty = pproperty;
   signal_details.m_pset = this;
   m_signal.emit(&signal_details);
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
   
   if(straKey.get_count() <= 0)
      return;
   
   property_set * pset = this;
   
   int32_t i = 0;

   while(i  < straKey.get_upper_bound())
   {
      pset = &(*pset)[straKey[i]].propset();
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

void property_set::_008Parse(bool bApp, const char * pszCmdLine, var & varFile, string & strApp)
{

   if(pszCmdLine == NULL)
      return;

   enum e_state
   {
      state_key,
      state_equal,
      state_value
   };
   
   
   ::str::parse parse(pszCmdLine, "= ");
   
   parse.EnableQuote(true);
   
   if(bApp && parse.getrestlen())
   {
      parse.getword(strApp);
   }

   string strFile;
   
   
   while(parse.getrestlen())
   {
   
      parse.getword(strFile);
      
      if(strFile == ":")
         break;

      strFile.trim("\"'");
      
      if(varFile.is_empty())
      {
         varFile = strFile;
      }
      else if(varFile.get_type() == var::type_string)
      {
         varFile.stra().add(strFile);
      }
      else if(varFile.get_type() == var::type_stra)
      {
         varFile.stra().add(strFile);
      }
      else if(varFile.get_type() == var::type_propset)
      {
         varFile.propset()["stra"].stra().add(strFile);
      }
      else
      {
         varFile.propset()["varFile"] = varFile;
         varFile.propset()["stra"].stra().add(strFile);
      }
      
   
   }


   string str;
   string strKey;
   

   e_state state = state_key;
   
   int iEnd = 0;

   while(iEnd <= 1)
   {
      
      if(parse.getrestlen() <= 0)
      {
         iEnd++;
      }
      
      if(iEnd <= 0)
      {
         parse.getsplitword(str);
      }

      str.trim("\"'");
      
      switch(state)
      {
      case state_key:
         {
            strKey = str;
            state = state_equal;
         }
         break;
      case state_equal:
         {
            if(str == '=')
            {
               state = state_value;
            }
            else
            {
               _008Add(strKey, "");
               strKey = str;
               state = state_equal;
            }
         }
         break;
      case state_value:
         {
      
            _008Add(strKey, str);
            strKey.Empty();
            str.Empty();
            state = state_key;

         }
         break;
      }
      
   }

}

void property_set::parse_json(const char * & pszJson)
{
   parse_json(pszJson, pszJson + strlen(pszJson) - 1);
}

void property_set::parse_json(const char * & pszJson, const char * pszEnd)
{
   ::str::consume_spaces(pszJson, 0, pszEnd);
   ::str::consume(pszJson, "{", 1, pszEnd);
   ::str::consume_spaces(pszJson, 0, pszEnd);
   while(true)
   {
      m_propertya.add(canew(property));
      m_propertya.last_element()->parse_json(pszJson, pszEnd);
      m_map.set_at(m_propertya.last_element()->name(), m_propertya.get_upper_bound());
      ::str::consume_spaces(pszJson, 0, pszEnd);
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

string property_set::get_json()
{

   string str;

   str = "{";

   for (int i = 0; i < m_propertya.get_count(); i++)
   {
      
      if (i > 0)
      {
         str += ", \r\n";
      }
      
      str += "\"";
      str += m_propertya.element_at(i)->name();
      str += "\"";
      str += ":";
      str += m_propertya.element_at(i)->m_var.get_json();

   }


   str += "}";


   return str;

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
            strKey = url_decode_dup(pszParam, strlen(pszUrlQuery) - (pszParam - pszUrlQuery));
            _008Add(strKey, "");
         }
         else
         {
            string strKey = url_decode_dup(pszParam, pszKeyEnd - pszParam);
            string strValue = url_decode_dup(pszKeyEnd + 1, strlen(pszUrlQuery) - (pszKeyEnd + 1 - pszUrlQuery));
            _008Add(strKey, strValue);
         }
         return;
      }
      else
      {
         if(pszKeyEnd == NULL || pszKeyEnd > pszParamEnd)
         {
            strKey = url_decode_dup(pszParam, pszParamEnd - pszParam);
            _008Add(strKey, "");
         }
         else
         {
            string strKey = url_decode_dup(pszParam, pszKeyEnd - pszParam);
            string strValue = url_decode_dup(pszKeyEnd + 1, pszParamEnd - (pszKeyEnd + 1));
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
         strName = stra[i].make_lower();
         add(strName, var(""));
      }
      else
      {
         strName = stra[i].Left(iPos).make_lower();
         add(strName, var(stra[i].Mid(iPos + 2)));
      }
   }
}


::count property_set::remove_by_name(id idName)
{
   return unset(idName);
}

::count property_set::remove_by_name(stringa & stra)
{
   ::count count = 0;
   for(int32_t i = 0; i < stra.get_count(); i++)
   {
      count += remove(stra[i]);
   }
   return count;
}




void property_set::replace_gen(string & str)
{

   strsize iPos;

   char ch;

   char chNext;

   for (iPos = 0; iPos < str.get_length(); iPos++)
   {
      ch = str[iPos];
      if (iPos + 1 < str.get_length())
         chNext = str[iPos + 1];
      else
         chNext = '\0';
      if (ch == '\\')
      {
         iPos++;
         continue;
      }
      else if (ch == '{' && chNext == '$')
      {
         strsize iEnd = str.find('}', iPos + 1);
         if (iEnd < 0)
         {
            //error
            break;
         }
         string strEval = gen_eval(str.Mid(iPos + 1, iEnd - iPos - 1));
         str = str.Left(iPos) + strEval + str.Mid(iEnd + 1);
         iPos += strEval.get_length() - 1;
      }
      else if (ch == '$')
      {
         if (!(isalpha_dup(chNext) || chNext == '_'))
         {
            // error
            break;
         }
         strsize iStart = iPos;
         strsize iEnd = iStart + 2;
         for (; iEnd < str.get_length(); iEnd++)
         {
            ch = str[iEnd];
            if (!(isalpha_dup(ch) || ch == '_' || isdigit_dup(ch)))
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

   str = &psz[1];
   
   return operator[](str);

}


void property_set::clear()
{
   m_propertya.remove_all();
   m_map.remove_all();
}

void property_set::write(::file::output_stream & ostream)
{
   ostream << m_bAutoAdd;
   ostream << m_bMultiValue;
   //ostream << m_bKeyCaseInsensitive;
   ostream << m_propertya;
}

void property_set::read(::file::input_stream & istream)
{
   istream >> m_bAutoAdd;
   istream >> m_bMultiValue;
   //istream >> m_bKeyCaseInsensitive;
   istream >> m_propertya;
   for (int32_t i = 0; i < m_propertya.get_count(); i++)
   {
      //if(m_bKeyCaseInsensitive)
      /*{
      m_map.set_at(m_propertya[i]->lowname(), i);
      }
      else
      {*/
      m_map.set_at(m_propertya[i]->name(), i);
      //}
   }
}

string property_set::implode(const char * pszGlue) const
{
   string str;
   if (m_propertya.get_count() > 0)
   {
      str = m_propertya[0]->get_value().get_string();
   }
   for (int32_t i = 1; i < m_propertya.get_count(); i++)
   {
      str += pszGlue;
      str += m_propertya[i]->get_value().get_string();
   }
   return str;
}

index property_set::find_value(const char * psz) const
{
   for (index find = 0; find < m_propertya.get_count(); find++)
   {
      if (m_propertya[find]->get_string() == psz)
         return find;
   }
   return -1;
}

index property_set::find_value_ci(const char * psz) const
{
   for (index find = 0; find < m_propertya.get_count(); find++)
   {
      if (m_propertya[find]->get_string().CompareNoCase(psz) == 0)
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
   if (iIndex >= m_propertya.get_size())
   {
      m_propertya.set_size(iIndex + 1);
   }
   return m_propertya(iIndex);
}

property property_set::at(index iIndex) const
{
   if (iIndex >= m_propertya.get_size())
   {
      const_cast < property_set * > (this)->m_propertya.set_size(iIndex + 1);
   }
   return const_cast<property_set*>(this)->m_propertya[iIndex];
}

property_set & property_set::operator = (const property_set & set)
{
   if (&set != this)
   {
      ::lemon::copy(m_propertya, set.m_propertya);
      m_bAutoAdd = set.m_bAutoAdd;
      m_bMultiValue = set.m_bMultiValue;
      m_map = set.m_map;
   }
   return *this;
}

property_set & property_set::add(const property_set & set)
{
   if (&set != this)
   {
      for (int32_t i = 0; i < set.m_propertya.get_count(); i++)
      {
         ((property &)operator[](set.m_propertya[i]->name())).m_var = set.m_propertya[i]->get_value();
      }
   }
   return *this;
}

property_set & property_set::merge(const property_set & set)
{
   if (&set != this)
   {
      for (int32_t i = 0; i < set.m_propertya.get_count(); i++)
      {
         const property * pproperty = set.m_propertya[i];
         property * ppropertyThis = find(set.m_propertya[i]->name());
         if (ppropertyThis != NULL)
         {
            if (ppropertyThis->m_var.get_type() == ::var::type_element ||
               pproperty->m_var.get_type() == ::var::type_element)
            {
               ((property &)operator[](set.m_propertya[i]->name())).m_var = set.m_propertya[i]->m_var;
            }
            else if (ppropertyThis->m_var.get_type() == ::var::type_propset)
            {
               if (pproperty->m_var.get_type() == ::var::type_propset)
               {
                  ppropertyThis->propset().merge(pproperty->propset());
               }
               else
               {
                  index i = 0;
                  while (true)
                  {
                     if (!has_property(str::from(i)))
                     {
                        operator[](str::from(i)).m_var = set.m_propertya[i]->m_var;
                        break;
                     }
                     i++;
                  }
                  
               }

            }
            else if(((property &)operator[](set.m_propertya[i]->name())).is_empty())
            {
               ((property &)operator[](set.m_propertya[i]->name())) = set.m_propertya(i);
            }
            else
            {
               try {
                  
               if(((property &)operator[](set.m_propertya[i]->name())) == set.m_propertya(i))
               {
                  continue;
               }
               } catch(...){
               }
               ((property &)operator[](set.m_propertya[i]->name())).stra().add_unique(set.m_propertya[i]->m_var.stra());
               if (((property &)operator[](set.m_propertya[i]->name())).stra().get_size() == 1)
               {
                  ((property &)operator[](set.m_propertya[i]->name())) = ((property &)operator[](set.m_propertya[i]->name())).stra()[0];
               }
            }
         }
         else
         {
            ((property &)operator[](set.m_propertya[i]->name())).m_var = set.m_propertya[i]->m_var;
         }

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
      for (int32_t i = 0; i < iCount; i++)
      {
         string strKey = set.pair_set_interface_get_key(i);
         class var var = set.pair_set_interface_get_value(i);
         m_propertya.add(canew(property(strKey, var)));
      }
      // WOULD ANALYZE each of the following members parameters for
      // auto discovery, calculation or leave as set.
      m_bAutoAdd = set.get_auto_add();
   }
   return *this;
}








property_set & property_set::operator = (const str_str_interface & set)
{
   //   if(&set != this)
   {
      m_propertya.remove_all();
      int32_t iCount = set.str_str_interface_get_count();
      for (int32_t i = 0; i < iCount; i++)
      {
         string strKey = set.str_str_interface_get_key(i);
         class var var = set.str_str_interface_get_value(i);
         m_propertya.add(canew(property(strKey, var)));
      }
      // WOULD ANALYZE each of the following members parameters for
      // auto discovery, calculation or leave as set.
      m_bAutoAdd = set.get_auto_add();
   }
   return *this;
}




index property_set::str_find(const property & property, index find) const
{
   if (find < 0)
      find = 0;
   for (; find < this->get_count(); find++)
   {
      if (m_propertya[find]->str_compare(property) == 0)
         return find;
   }
   return -1;
}



bool property_set::str_contains(const property_set & set) const
{

   for (index i = 0; i < set.m_propertya.get_count(); i++)
   {
      if (str_find(set.m_propertya(i)) < 0)
         return false;
   }
   return true;

}





string property_set::get_http_post()
{
   string strPost;
   for (int32_t i = 0; i < m_propertya.get_size(); i++)
   {
      strPost += m_propertya.element_at(i)->name();
      strPost += "=";
      strPost += url_encode_dup(m_propertya.element_at(i)->get_value().get_string());
      if (i < m_propertya.get_size() - 1)
         strPost += "&";
   }
   return strPost;
}














