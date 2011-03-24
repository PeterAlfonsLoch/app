#pragma once

template < class DST, class SRC >
DST fn_cast(SRC src)
{
   DST dst;
   memset(&dst, 0, sizeof(dst));
   memcpy(&dst, &src, min(sizeof(dst), sizeof(src)));
   return dst;
}


class CLASS_DECL_CA2_CUBE dso_base :
   public ptr
{
public:
   gen::property_set m_propertyset;


   virtual dso_base * create_object() = 0;
   virtual ::ca::ca * clone();

   var call(const char * pszName,
      var var01 = gen::g_emptyargumentconst,
      var var02 = gen::g_emptyargumentconst,
      var var03 = gen::g_emptyargumentconst,
      var var04 = gen::g_emptyargumentconst,
      var var05 = gen::g_emptyargumentconst,
      var var06 = gen::g_emptyargumentconst,
      var var07 = gen::g_emptyargumentconst,
      var var08 = gen::g_emptyargumentconst,
      var var09 = gen::g_emptyargumentconst,
      var var10 = gen::g_emptyargumentconst,
      var var11 = gen::g_emptyargumentconst,
      var var12 = gen::g_emptyargumentconst,
      var var13 = gen::g_emptyargumentconst,
      var var14 = gen::g_emptyargumentconst,
      var var15 = gen::g_emptyargumentconst,
      var var16 = gen::g_emptyargumentconst,
      var var17 = gen::g_emptyargumentconst,
      var var18 = gen::g_emptyargumentconst,
      var var19 = gen::g_emptyargumentconst,
      var var20 = gen::g_emptyargumentconst,
      var var21 = gen::g_emptyargumentconst,
      var var22 = gen::g_emptyargumentconst,
      var var23 = gen::g_emptyargumentconst,
      var var24 = gen::g_emptyargumentconst,
      var var25 = gen::g_emptyargumentconst);

   var function_example0();
   var function_example1(var var1);
   var function_example2(var var1, var var2);

   virtual string get_base_classes_name();
   virtual dso_base * offset_cast(const char * psz);
   virtual var this_call(const char * psz, FARPROC farproc);
   virtual var this_call(const char * psz, FARPROC farproc, var & var01);
   virtual var this_call(const char * psz, FARPROC farproc, var & var01, var & var02);
};


template < class DSO, class DSOBASE >
class dso :
   public DSOBASE
{
public:
   virtual dso_base * create_object()
   {
      return new DSO();
   }
   virtual string get_base_classes_name()
   {
      return string(typeid(DSO).raw_name()) + ";" + DSOBASE::get_base_classes_name();
   }

   bool dso_matches(const char * psz)
   {
      return string(psz) == string(typeid(DSO).raw_name());
   }

   DSO * _dso()
   {
      return dynamic_cast < DSO * > (this);
   }

   virtual dso_base * offset_cast(const char * psz)
   {
     if(dso_matches(psz))
     {
        return (::dso_base *) ((void *) this);
     }
     else
     {
        return DSOBASE::offset_cast(psz);
     }
   }

   virtual var this_call(const char * psz, FARPROC farproc)
   {
      if(dso_matches(psz))
      {
         DSO * pdso = _dso();
         var(DSO::*pfn)() =  fn_cast < var(DSO::*)(), FARPROC > (farproc);
         return (pdso->*pfn)();
      }
      else
      {
         return DSOBASE::this_call(psz, farproc);
      }
   }
   virtual var this_call(const char * psz, FARPROC farproc, var & var01)
   {
      if(dso_matches(psz))
      {
         DSO * pdso = _dso();
         var(DSO::*pfn)(var) =  fn_cast < var(DSO::*)(var), FARPROC > (farproc);
         return (pdso->*pfn)(var01);
      }
      else
      {
         return DSOBASE::this_call(psz, farproc, var01);
      }
   }
   virtual var this_call(const char * psz, FARPROC farproc, var & var01, var & var02)
   {
      if(dso_matches(psz))
      {
         DSO * pdso = _dso();
         var(DSO::*pfn)(var,var) =  fn_cast < var(DSO::*)(var,var), FARPROC > (farproc);
         return (pdso->*pfn)(var01, var02);
      }
      else
      {
         return DSOBASE::this_call(psz, farproc, var01, var02);
      }
   }

};