#include "StdAfx.h"


namespace dynamic_source
{


   var object_base::call(const char * pszName, 
      var var01,
      var var02,
      var var03,
      var var04,
      var var05,
      var var06,
      var var07,
      var var08,
      var var09,
      var var10,
      var var11,
      var var12,
      var var13,
      var var14,
      var var15,
      var var16,
      var var17,
      var var18,
      var var19,
      var var20,
      var var21,
      var var22,
      var var23,
      var var24,
      var var25)
   {
      //   ::ca::ca * pca = this;
      string strClassesName = get_base_classes_name();
      stringa straClasses;
      straClasses.explode(";", strClassesName);

      for(int iClass = 0; iClass < straClasses.get_upper_bound(); iClass++)
      {
         string strClassName = straClasses[iClass];
         string strVarName = ::ca::get_type_info < var > ().raw_name();

         int iVCount = 0;
         int iLen = strClassName.get_length() - 2;
         for(int i = 0; i < iLen; i++)
         {
            if(strClassName[i] == '@')
            {
               iVCount++;
            }
         }
         iVCount += 2;

         int iCount = 0;
         string strName(pszName);
         string strTemplate;
         strTemplate += "?";
         strTemplate += strName;
         strTemplate += "@";
         strTemplate += strClassName.Mid(4);
#ifdef _X86_
         strTemplate += "QAE";
#else
         strTemplate += "QEAA";
#endif
         //strTemplate += "UAE";
         strTemplate += strVarName.Mid(1);


         if(var04.get_type() == var::type_empty_argument)
         {
            if(var03.get_type() == var::type_empty_argument)
            {
               if(var02.get_type() == var::type_empty_argument)
               {
                  if(var01.get_type() == var::type_empty_argument)
                  {
                     iCount = 0;
                  }
                  else
                  {
                     iCount = 1;
                  }
               }
               else
               {
                  iCount = 2;
               }
            }
            else
            {
               iCount = 3;
            }
         }
         else
         {
            iCount = 4;
         }
         //   ?function_example0@dynamic_source::object@@QAE?AVvar@@XZ
         //   ?function_example1@dynamic_source::object@@QAE?AVvar@@V2@@Z
         //?function_example2@dynamic_source::object@@QAE?AVvar@@V2@0@Z

         //      object_base * pdsoThis = this;
         //      object_base * pdso = offset_cast(strClassName);

         for(int iFunc = iCount; iFunc <= 2; iFunc++)
         {
            string strFunction = strTemplate;
            if(iFunc == 0)
            {
               strFunction += "XZ";
            }
            else if(iFunc == 1)
            {
               strFunction += "V" + gen::str::itoa(iVCount) + "@@Z";
            }
            else if(iFunc == 2)
            {
               strFunction += "V" + gen::str::itoa(iVCount) + "@0@Z";
            }
            FARPROC farproc = ::GetProcAddress(::GetModuleHandleA("cube.dll"), strFunction);
            if(farproc != NULL)
            {
               if(iFunc == 0)
               {
                  return this_call(strClassName, farproc);
               }
               else if(iFunc == 1)
               {
                  return this_call(strClassName, farproc, var01);
               }
               else
               {
                  return this_call(strClassName, farproc, var01, var02);
               }
            }
         }
      }
      return gen::g_newconst;
   }

   var object_base::function_example0()
   {
      return gen::g_emptyconst;
   }
   var object_base::function_example1(var var1)
   {
      return gen::g_emptyconst;
   }
   var object_base::function_example2(var var1, var var2)
   {
      return gen::g_emptyconst;
   }

   ::ca::ca * object_base::clone()
   {
      object_base * pdso = create_object();
      if(pdso == NULL)
         return NULL;
      pdso->m_bUnkeep      = m_bUnkeep;
      pdso->m_ulFlags      = m_ulFlags;
      pdso->m_propertyset  = m_propertyset;
      return pdso;
   }


   string object_base::get_base_classes_name()
   {
      return typeid(*this).raw_name();
   }

   object_base * object_base::offset_cast(const char * psz)
   {
      if(string(psz) == string(::ca::get_type_info < object_base > ().raw_name()))
      {
         return (object_base *) ((void *) this);
      }
      else
      {
         return NULL;
      }
   }

   var object_base::this_call(const char * psz, FARPROC farproc)
   {
      UNREFERENCED_PARAMETER(psz);
      UNREFERENCED_PARAMETER(farproc);
      return gen::g_emptyconst;
   }

   var object_base::this_call(const char * psz, FARPROC farproc, var & var01)
   {
      UNREFERENCED_PARAMETER(psz);
      UNREFERENCED_PARAMETER(farproc);
      UNREFERENCED_PARAMETER(var01);
      return gen::g_emptyconst;
   }

   var object_base::this_call(const char * psz, FARPROC farproc, var & var01, var & var02)
   {
      UNREFERENCED_PARAMETER(psz);
      UNREFERENCED_PARAMETER(farproc);
      UNREFERENCED_PARAMETER(var01);
      UNREFERENCED_PARAMETER(var02);
      return gen::g_emptyconst;
   }


} // namespace dynamic_source


