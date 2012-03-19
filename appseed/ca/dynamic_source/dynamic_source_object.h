#pragma once


namespace dynamic_source
{

   template < class DST, class SRC >
   DST fn_cast(SRC src)
   {
      DST dst;
      memset(&dst, 0, sizeof(dst));
      memcpy(&dst, &src, min(sizeof(dst), sizeof(src)));
      return dst;
   }


   class CLASS_DECL_ca object_base :
      public ptr
   {
   public:
      gen::property_set m_propertyset;


      virtual object_base * create_object() = 0;
      virtual ::ca::ca * clone();

      var call(const char * pszName,
         var var01 = ::var(::var::e_type::type_empty_argument),
         var var02 = ::var(::var::e_type::type_empty_argument),
         var var03 = ::var(::var::e_type::type_empty_argument),
         var var04 = ::var(::var::e_type::type_empty_argument),
         var var05 = ::var(::var::e_type::type_empty_argument),
         var var06 = ::var(::var::e_type::type_empty_argument),
         var var07 = ::var(::var::e_type::type_empty_argument),
         var var08 = ::var(::var::e_type::type_empty_argument),
         var var09 = ::var(::var::e_type::type_empty_argument),
         var var10 = ::var(::var::e_type::type_empty_argument),
         var var11 = ::var(::var::e_type::type_empty_argument),
         var var12 = ::var(::var::e_type::type_empty_argument),
         var var13 = ::var(::var::e_type::type_empty_argument),
         var var14 = ::var(::var::e_type::type_empty_argument),
         var var15 = ::var(::var::e_type::type_empty_argument),
         var var16 = ::var(::var::e_type::type_empty_argument),
         var var17 = ::var(::var::e_type::type_empty_argument),
         var var18 = ::var(::var::e_type::type_empty_argument),
         var var19 = ::var(::var::e_type::type_empty_argument),
         var var20 = ::var(::var::e_type::type_empty_argument),
         var var21 = ::var(::var::e_type::type_empty_argument),
         var var22 = ::var(::var::e_type::type_empty_argument),
         var var23 = ::var(::var::e_type::type_empty_argument),
         var var24 = ::var(::var::e_type::type_empty_argument),
         var var25 = ::var(::var::e_type::type_empty_argument));

      var function_example0();
      var function_example1(var var1);
      var function_example2(var var1, var var2);

      virtual string get_base_classes_name();
      virtual object_base * offset_cast(const char * psz);
      virtual var this_call(const char * psz, FARPROC farproc);
      virtual var this_call(const char * psz, FARPROC farproc, var & var01);
      virtual var this_call(const char * psz, FARPROC farproc, var & var01, var & var02);
   };


   template < class DSO, class DSOBASE >
   class object :
      public DSOBASE
   {
   public:

      virtual object_base * create_object()
      {
         return new DSO();
      }

      virtual string get_base_classes_name()
      {
#ifdef WINDOWS
         return string(typeid(DSO).raw_name()) + ";" + DSOBASE::get_base_classes_name();
#else
         return string(typeid(DSO).name()) + ";" + DSOBASE::get_base_classes_name();
#endif
      }

      bool dso_matches(const char * psz)
      {
#ifdef WINDOWS
         return string(psz) == string(typeid(DSO).raw_name());
#else
         return string(psz) == string(typeid(DSO).name());
#endif
      }

      DSO * _dso()
      {
         return dynamic_cast < DSO * > (this);
      }

      virtual object_base * offset_cast(const char * psz)
      {
        if(dso_matches(psz))
        {
           return (object_base *) ((void *) this);
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


} // namespace dynamic_source
