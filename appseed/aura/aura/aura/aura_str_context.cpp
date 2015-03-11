//#include "framework.h" // from "base/user/user.h"


namespace aura
{


   str_context::str_context(::aura::application * papp) :
      object(papp)
   {


      m_plocaleschema = canew(::str::international::locale_schema(papp));


      m_pstr = NULL;


   }

   str_context::~str_context()
   {

   }


   void str_context::prepare()
   {

      static ::id idEn("en");
      static ::id idStd("_std");





      m_plocale               = NULL;

      m_pschema               = NULL;
      m_pschemaLocale         = NULL;
      m_pschemaSchemaEn       = NULL;
      m_pschemaSchemaStd      = NULL;


      m_schemaptra.remove_all();


      if(m_plocaleschema != NULL)
      {

         if(!m_plocaleschema->m_idLocale.is_empty())
         {

            m_plocale = m_pstr->get_locale(m_plocaleschema->m_idLocale);

            if(m_plocale != NULL)
            {

               if(!m_plocaleschema->m_idSchema.is_empty() && m_plocaleschema->m_idSchema != m_plocaleschema->m_idLocale)
               {
                  m_pschema = m_plocale->get_schema(m_plocaleschema->m_idSchema);
               }
               m_pschemaLocale = m_plocale->get_schema(m_plocaleschema->m_idSchema);
            }
         }

         if(!m_plocaleschema->m_idSchema.is_empty())
         {

            str_locale * plocale = m_pstr->get_locale(m_plocaleschema->m_idSchema);

            if(plocale != NULL)
            {

               m_pschemaSchemaEn = plocale->get_schema(idEn);

               m_pschemaSchemaStd = plocale->get_schema(idStd);

            }

         }

         strid_array stridaFailedLocale(false);

         for(int32_t i = 0; i < m_plocaleschema->m_idaLocale.get_count(); i++)
         {

            ::id & idLocale = m_plocaleschema->m_idaLocale[i];


            if(stridaFailedLocale.contains(idLocale))
               continue;

            str_locale * plocale = m_pstr->get_locale(idLocale);

            if(plocale == NULL)
            {
               stridaFailedLocale.add(idLocale);
               continue;
            }

            ::id & idSchema = m_plocaleschema->m_idaSchema[i];


            str_schema * pschema = plocale->get_schema(idSchema);

            if(pschema != NULL)
            {

               m_schemaptra.add(pschema);

            }

            if(idLocale != idSchema)
            {

               str_schema * pschema = plocale->get_schema(idLocale);

               if(pschema != NULL)
               {

                  m_schemaptra.add(pschema);

               }

            }

            if(__id(std) != idSchema)
            {

               str_schema * pschema = plocale->get_schema(__id(std));

               if(pschema != NULL)
               {

                  m_schemaptra.add(pschema);

               }

            }

         }

      }

   }

   str::str(::aura::application * papp) :
      object(papp)
   {

      InitHashTable(64);

      operator[]("en")["en"]     =  *(m_pschemaEn    =  canew(str_schema));
      operator[]("_std")["_std"] =  *(m_pschemaStd   =  canew(str_schema));


   }

   bool str::initialize()
   {
#ifdef METROWIN
      return true;
#endif
      auto strMain = System.dir().element() / "app\\appmatter\\main";
      if(!load(strMain))
         return false;
      return true;
   }

   bool str::load(const char * pszBaseDir)
   {
      string strMain = pszBaseDir;
      ::file::patha straLangPath;
      ::file::patha straLang;
      Application.dir().ls_dir(strMain, &straLangPath, &straLang);
      for(int32_t iLang = 0; iLang < straLang.get_count(); iLang++)
      {
         string strLang = straLang[iLang];
         if(strLang.CompareNoCase(".svn") == 0)
            continue;
         ::file::patha straStylePath;
         ::file::patha straStyle;
         Application.dir().ls_dir(straLangPath[iLang], &straStylePath, &straStyle);
         for(int32_t iStyle = 0; iStyle < straStyle.get_count(); iStyle++)
         {
            string idStyle = straStyle[iStyle];
            if(idStyle.CompareNoCase(".svn") == 0)
               continue;
            ::file::patha patha;
            Application.dir().rls(straStylePath[iStyle] / "uistr", &patha);
            for(int32_t iPath = 0; iPath < patha.get_count(); iPath++)
            {
               string strPath = patha[iPath];
               if(::str::ends_ci(strPath, "\\.svn"))
                  continue;
               if(::str::find_ci("\\.svn\\", strPath) >= 0)
                  continue;
               if(Application.dir().is(strPath))
                  continue;
               load_uistr_file(strLang, idStyle, strPath);
            }
         }
      }

      return true;

   }


   void str::set(const ::id & id, const ::id & idLocale, const ::id & idSchema, const char * psz)
   {


      (*this)[idLocale][idSchema][id] = psz;


   }



   string str::get(str_context * pcontext,const ::id & id, bool bIdAsDefaultValue)
   {

      static ::id idEn("en");
      static ::id idStd("_std");

      string str;
      if(pcontext != NULL)
      {

         pcontext->defer_ok(this);

         if(pcontext->m_pschema != NULL)
         {

            str = (*pcontext->m_pschema)[id];
            if(str.has_char())
               return str;

         }

         if(pcontext->m_pschemaLocale != NULL)
         {
            str = (*pcontext->m_pschemaLocale)[id];
            if(str.has_char())
               return str;
         }

         for(int32_t i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            str = (*pcontext->m_schemaptra[i])[id];
            if(str.has_char())
               return str;

         }

      }
      if(pcontext != NULL && pcontext->m_pschemaSchemaEn != NULL)
      {
         str = (*pcontext->m_pschemaSchemaEn)[id];// lang=pszStyle style=en
         if(str.has_char())
            return str;
      }
      str = (*m_pschemaEn)[id]; // lang=en style=en
      if(str.has_char())
         return str;
      if(pcontext != NULL && pcontext->m_pschemaSchemaStd != NULL)
      {
         str = (*pcontext->m_pschemaSchemaStd)[id];// lang=pszStyle style=en
         if(str.has_char())
            return str;
      }
      
      str = (*m_pschemaStd)[id]; // lang=_std style=_std

      if(str.has_char())
      {

         return str;

      }
      
      if(bIdAsDefaultValue)
      {

         return id;

      }
      else
      {

         return "";

      }

   }

   string str::get(str_context * pcontext,const ::id & id,const ::id & idLocale,const ::id & idSchema,bool bIdAsDefaultValue)
   {

      if(!idLocale.is_empty())
      {
         string str;
         str_locale * plocale = get_locale(idLocale);
         if(plocale != NULL)
         {

            if(!idSchema.is_empty() && idSchema != idLocale)
            {
               str_schema * pschema = plocale->get_schema(idSchema);
               if(pschema != NULL)
               {
                  str = (*pschema)[id];
                  if(str.has_char())
                     return str;
               }
            }

            str_schema * pschema = plocale->get_schema(idLocale);
            if(pschema != NULL)
            {
               str = (*pschema)[id];
               if(str.has_char())
                  return str;
            }
         }
      }
      return get(pcontext,id,bIdAsDefaultValue);
   }

   void str::get(stringa & stra, str_context * pcontext, const ::id & id)
   {

      _get(stra, pcontext, id);

      ::id id2;

      index i = 0;

      stringa stra2;

      do
      {

         stra2.remove_all();

         id2 = string(id.m_psz) + "[" + ::str::from(i) + "]";

         _get(stra2, pcontext, id2);

         stra.add(stra2);

         i++;

      } while (stra2.get_count() > 0);

      
   }


   void str::_get(stringa & stra, str_context * pcontext, const ::id & id)
   {

      static ::id idEn("en");
      static ::id idStd("_std");

      string str;
      if(pcontext != NULL)
      {

         pcontext->defer_ok(this);

         if(pcontext->m_pschema != NULL)
         {

            str = (*pcontext->m_pschema)[id];
            if(str.has_char())
               stra.add(str);

         }

         if(pcontext->m_pschemaLocale != NULL)
         {
            str = (*pcontext->m_pschemaLocale)[id];
            if(str.has_char())
               stra.add(str);
         }

         for(int32_t i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            str = (*pcontext->m_schemaptra[i])[id];
            if(str.has_char())
               stra.add(str);

         }

      }

      if(pcontext != NULL && pcontext->m_pschemaSchemaEn != NULL)
      {

         str = (*pcontext->m_pschemaSchemaEn)[id];// lang=pszStyle style=en
         if(str.has_char())
            stra.add(str);

      }

      str = (*m_pschemaEn)[id]; // lang=en style=en
      if(str.has_char())
         stra.add(str);

      if(pcontext != NULL && pcontext->m_pschemaSchemaStd != NULL)
      {

         str = (*pcontext->m_pschemaSchemaStd)[id];// lang=pszStyle style=en
         if(str.has_char())
            stra.add(str);

      }

      str = (*m_pschemaStd)[id]; // lang=_std style=_std
      if(str.has_char())
         stra.add(str);

   }

   struct range_sz_item
   {
      strsize s;
      strsize e;
   };

   struct range_sz
   {

      range_sz_item stack[8];
      int m_pos = 0;

      char m_szAlloca[8 * 1024];
      char * m_szMerge = m_szAlloca;
      int m_iSize =0;
      int m_iMaxSize=sizeof(m_szAlloca);
      bool m_bOwn = false;


      ~range_sz()
      {
         if(m_szMerge != NULL && m_szMerge != m_szAlloca && m_bOwn)
         {
            memory_free(m_szMerge);
         }
      }

      void append(strsize start,strsize end,char * pszTopic)
      {
         stack[m_pos].s = start;
         stack[m_pos].e = end;
         m_pos++;
         if(m_pos >= 8)
         {
            merge(pszTopic);
         }
      }

      void merge(char * pszTopic)
      {

         if(m_pos <= 0)
            return;
         
         strsize oldlen = m_iSize;

         strsize newlen;
         
         if(oldlen == 0 && m_pos == 1)
         {

            newlen = stack[0].e - stack[0].s;

            m_szMerge = &pszTopic[stack[0].s];

         }
         else
         {

            newlen = m_iSize + calc_merge_len();

            if(oldlen == newlen)
            {

               m_pos = 0;

               return;

            }

            if(newlen >= m_iMaxSize) // extra 1 byte
            {
               m_iMaxSize = newlen + 1024; // extra 1 byte plus 1023
               if(m_iMaxSize > sizeof(m_szAlloca))
               {
                  if(m_szMerge == m_szAlloca || !m_bOwn)
                  {
                     m_szMerge = (char *)memory_alloc(m_iMaxSize);
                     memcpy(m_szMerge,m_szAlloca,oldlen);
                  }
                  else
                  {
                     m_szMerge = (char *)memory_realloc(m_szMerge,m_iMaxSize);
                  }
                  m_bOwn = true;
               }
            }

            strsize pos = 0;
            strsize len;
            for(index i = 0; i < m_pos; i++)
            {
               len = stack[i].e - stack[i].s;
               memcpy(&m_szMerge[oldlen + pos],&pszTopic[stack[i].s],len);
               pos+=len;
            }

         }

         m_iSize = newlen;
         
         //m_szMerge[m_iSize] = '\0'; // for optmization purposes, m_szMerge is not forced to be 0 finished, so CHECK m_iSize!!

         m_pos = 0;

      }

      int calc_merge_len()
      {
         if(m_pos <= 0)
            return 0;
         if(m_pos == 1)
            return stack[0].e - stack[0].s;
         strsize len = 0;
         for(index i = 0; i < m_pos; i++)
         {
            len += stack[i].e - stack[i].s;
         }
         return len;
      }

      //char * get_string(char string & strTopic)
      //{
      //   merge(strTopic);
      //   if(m_iSize == 0)
      //      return NULL;
      //   return m_szMerge;
      //}
      void clear()
      {
         m_iSize = 0;
         m_pos = 0;
      }
   };

   bool str::load_uistr_file(const ::id & pszLang, const ::id & pszStyle, const char * pszFilePath)
   {

      ::primitive::memory mem;

      Application.file().as_memory(pszFilePath,mem);


      strsize len;

      char * pszFile = mem.get_psz(len);

      ::str::parse parse(pszFile, len);

      string str;
      
      int32_t i = 0;

      strsize start;

      strsize end;

      char q;

      ::str::utf8_char c;

      bool bFinal;

      bool bEof = false;

      const char * s;

      char * wr;

      const char * rd;

      strsize l;

      range_sz rstr;

      const char * pszEnd;

      string strRoot;

      string strBody;

      while(parse.has_char())
      {

         rstr.clear();

         bFinal = false;
         
         while(!bFinal)
         {
         
            parse._get_expandable_line(start,end,bFinal);

            rstr.append(start,end,pszFile);

         }

         rstr.merge(pszFile);

         char * psz = rstr.m_szMerge;

         pszEnd = psz + rstr.m_iSize;

         while(::str::ch::is_whitespace(psz))
         {
            psz += str_uni_len(psz);
            if(psz >= pszEnd)
               goto cont;
         }

         // going to consume a quoted value

         q = *psz;

         if(q != '\'' && q != '\"') 
         {
            goto cont;
         }

         psz++;
         s = psz;
         
         while(*psz != q)
         {
            psz += str_uni_len(psz);
            if(psz >= pszEnd)
               goto cont;
         }
         strRoot.SetString(s, psz - s);
         psz++;

         while(::str::ch::is_whitespace(psz))
         {
            psz += str_uni_len(psz);
            if(psz >= pszEnd)
               goto end;
         }

         if(*psz != '=') 
            continue;

         psz++;

         while(::str::ch::is_whitespace(psz))
         {
            psz += str_uni_len(psz);
            if(psz >= pszEnd)
               goto end;
         }

         // going to consume another quoted value

         q = *psz;

         if(q != '\'' && q != '\"')
         {
            goto cont;
         }

         psz++;
         s = psz;
         wr = psz;
         rd = psz;
         while(*rd != q)
         {
            if(*rd == '\\')
            {
               if(*(rd + 1) == 'r')
               {
                  *wr = '\r';
                  wr++;
                  rd+=2;
                  goto cont2;
               }
               else if(*(rd + 1) == 'n')
               {
                  *wr = '\n';
                  wr++;
                  rd+=2;
                  goto cont2;
               }
               else
               {
                  *wr = '\\';
                  wr++;
                  rd++;
                  goto cont2;
               }
            }
            l = str_uni_len(psz);
            if(wr != rd)
            {
               while(l > 0)
               {
                  *wr=*rd;
                  wr++;
                  rd++;
                  l--;
               }
            }
            else
            {
               wr+=l;
               rd+=l;
            }
            cont2:
            if(rd >= pszEnd)
               goto cont;
         }
         strBody.SetString(s,wr - s);
         //psz++;

         

         //body(strBody)
         //strBody.replace("\\r","\r");

         //strBody.replace("\\n","\n"); already done

         set(strRoot, pszLang, pszStyle, strBody);

      cont:;
      }
      end:

      return true;
   }

   string str::body(const char * psz)
   {
      string str(psz);
      str.replace("\\r", "\r");
      str.replace("\\n", "\n");
      return str;
   }

   bool str::matches(str_context * pcontext, const ::id & id, const char * psz)
   {

      static ::id idEn("en");
      static ::id idStd("_std");

      string str;
      if(pcontext != NULL)
      {

         pcontext->defer_ok(this);

         if(pcontext->m_pschema != NULL)
         {

            str = (*pcontext->m_pschema)[id];
            if(!str.CompareNoCase(psz))
               return true;

         }

         if(pcontext->m_pschemaLocale != NULL)
         {
            str = (*pcontext->m_pschemaLocale)[id];
            if(!str.CompareNoCase(psz))
               return true;
         }

         for(int32_t i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            str = (*pcontext->m_schemaptra[i])[id];
            if(!str.CompareNoCase(psz))
               return true;

         }

      }

      if(pcontext != NULL && pcontext->m_pschemaSchemaEn != NULL)
      {

         str = (*pcontext->m_pschemaSchemaEn)[id];// lang=pszStyle style=en
         if(!str.CompareNoCase(psz))
            return true;

      }

      str = (*m_pschemaEn)[id]; // lang=en style=en
      if(!str.CompareNoCase(psz))
         return true;

      if(pcontext != NULL && pcontext->m_pschemaSchemaStd != NULL)
      {

         str = (*pcontext->m_pschemaSchemaStd)[id];// lang=pszStyle style=en
         if(!str.CompareNoCase(psz))
            return true;

      }



      return false;


   }

   bool str::begins(str_context * pcontext, const char * pszTopic, const ::id & id)
   {

      static ::id idEn("en");
      static ::id idStd("_std");

      string str;
      if(pcontext != NULL)
      {

         pcontext->defer_ok(this);

         if(pcontext->m_pschema != NULL)
         {

            str = (*pcontext->m_pschema)[id];
            if(str.has_char() && ::str::begins_ci(pszTopic, str))
               return true;

         }

         if(pcontext->m_pschemaLocale != NULL)
         {
            str = (*pcontext->m_pschemaLocale)[id];
            if(str.has_char() && ::str::begins_ci(pszTopic, str))
               return true;
         }

         for(int32_t i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            str = (*pcontext->m_schemaptra[i])[id];
            if(str.has_char() && ::str::begins_ci(pszTopic, str))
               return true;

         }

      }

      if(pcontext != NULL && pcontext->m_pschemaSchemaEn != NULL)
      {

         str = (*pcontext->m_pschemaSchemaEn)[id];// lang=pszStyle style=en
         if(str.has_char() && ::str::begins_ci(pszTopic, str))
            return true;

      }

      str = (*m_pschemaEn)[id]; // lang=en style=en
      if(str.has_char() && ::str::begins_ci(pszTopic, str))
         return true;

      if(pcontext != NULL && pcontext->m_pschemaSchemaStd != NULL)
      {

         str = (*pcontext->m_pschemaSchemaStd)[id];// lang=pszStyle style=en
         if(str.has_char() && ::str::begins_ci(pszTopic, str))
            return true;

      }



      return false;


   }

   bool str::begins_eat(str_context * pcontext, string & strTopic, const ::id & id)
   {

      static ::id idEn("en");
      static ::id idStd("_std");

      string str;
      if(pcontext != NULL)
      {

         pcontext->defer_ok(this);

         if(pcontext->m_pschema != NULL)
         {

            str = (*pcontext->m_pschema)[id];
            if(str.has_char() && ::str::begins_eat_ci(strTopic, str))
               return true;

         }

         if(pcontext->m_pschemaLocale != NULL)
         {
            str = (*pcontext->m_pschemaLocale)[id];
            if(str.has_char() && ::str::begins_eat_ci(strTopic, str))
               return true;
         }

         for(int32_t i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            str = (*pcontext->m_schemaptra[i])[id];
            if(str.has_char() && ::str::begins_eat_ci(strTopic, str))
               return true;

         }

      }

      if(pcontext != NULL && pcontext->m_pschemaSchemaEn != NULL)
      {

         str = (*pcontext->m_pschemaSchemaEn)[id];// lang=pszStyle style=en
            if(str.has_char() && ::str::begins_eat_ci(strTopic, str))
               return true;

      }

      str = (*m_pschemaEn)[id]; // lang=en style=en
      if(str.has_char() && ::str::begins_eat_ci(strTopic, str))
         return true;

      if(pcontext != NULL && pcontext->m_pschemaSchemaStd != NULL)
      {

         str = (*pcontext->m_pschemaSchemaStd)[id];// lang=pszStyle style=en
         if(str.has_char() && ::str::begins_eat_ci(strTopic, str))
            return true;

      }


      return false;


   }



   bool str_context::match(const cregexp_util & u,stringa & stra,const char * psz,id pszExp,id pszRoot)
   {

      stringa straCandidate;

      get(straCandidate,pszRoot);

      for(int32_t i = 0; i < straCandidate.get_count(); i++)
      {

         string strCandidate = straCandidate[i];
         strCandidate.replace("-","\\-");
         string strExp(pszExp);
         strExp.replace("%1",strCandidate);
         stringa straResult;
         if(u.match(straResult,psz,strExp,true,2) > 0)
         {
            stra = straResult;
            return true;
         }
      }
      return false;
   }


} // namespace user


