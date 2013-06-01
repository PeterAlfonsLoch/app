#include "framework.h"


namespace ca
{

   property_set::property_set(::ca::application * papp, bool bAutoAdd, bool bMultiValue) :
      ca(papp),
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
      ::ca::property_pair pair(*this);
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
         ::ca::property * pproperty = add(idName);
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
      ::ca::property_map::pair * ppair = m_map.PLookup(idName);
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

      ::ca::property_set * pset = this;

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
         if(!bStarted && !bQuote && *pszCmdLine != '\0' && ::ca::ch::is_space_char(pszCmdLine))
         {
            pszStart = ::ca::str::utf8_inc(pszCmdLine);
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
      ::ca::str::consume_spaces(pszJson, 0, pszEnd);
      ::ca::str::consume(pszJson, "{", 1, pszEnd);
      ::ca::str::consume_spaces(pszJson, 0, pszEnd);
      while(true)
      {
         m_propertya.add(canew(::ca::property));
         m_propertya.last_element()->parse_json(pszJson, pszEnd);
         m_map.set_at(m_propertya.last_element()->name(), m_propertya.get_upper_bound());
         ::ca::str::consume_spaces(pszJson, 0, pszEnd);
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


   } 