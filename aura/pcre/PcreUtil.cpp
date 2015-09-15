#include "app/aura/pcre/src/pcre2.h"
#include "PcreUtil.h"

pcre_util::pcre_util(::aura::application * papp) :
   object(papp)
{

}

pcre_util::~pcre_util()
{

}


class CLASS_DECL_AURA_PCRE pcre_util_impl :
   virtual public pcre_util
{
public:


   pcre2_general_context * m_pgc;
   pcre2_compile_context * m_pcc;
   pcre2_code * m_pc;

   pcre2_match_data * m_pmd;

   pcre_util_impl(::aura::application * papp) :
      object(papp),
      pcre_util(papp)
   {

      m_pgc = pcre2_general_context_create(NULL,NULL,NULL);

      m_pcc = pcre2_compile_context_create(m_pgc);


   }
   virtual ~pcre_util_impl()
   {


   }


   bool compile(const string &str)
   {


      int e;

      PCRE2_SIZE eo;
      m_pc = pcre2_compile((PCRE2_SPTR)(const char *)str,str.get_length(),0,&e,&eo,m_pcc);

      if(m_pc == NULL)
         return false;

      m_pmd = pcre2_match_data_create_from_pattern(m_pc,m_pgc);

      if(m_pmd == NULL)
         return false;

      return true;

   }


   int matches(const string & str)
   {

      int c = pcre2_match(m_pc,(PCRE2_SPTR)(const char *)str,str.get_length(),0,0,m_pmd,NULL);

      return c;
   }

};



pcre_util * pcre_util::compile(::aura::application * papp, const string & str)
{

   pcre_util_impl * putil = new pcre_util_impl(papp);

   putil->compile(str);


   return putil;

}