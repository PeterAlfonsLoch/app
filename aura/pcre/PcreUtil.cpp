#include "app/aura/pcre/src/pcre2.h"
#include "PcreUtil.h"


#define PC() (*((pcre_context_impl *)pcreContext->m_pthis))

pcre_context::pcre_context(::aura::application * papp) :
   object(papp)
{

}

pcre_context::~pcre_context()
{

}


pcre_util::pcre_util(::aura::application * papp):
   object(papp)
{

}


pcre_util::~pcre_util()
{

}


pcre_code::pcre_code(::aura::application * papp):
   object(papp),
   pcre_util(papp)
{

}


pcre_code::~pcre_code()
{

}


class CLASS_DECL_AURA_PCRE pcre_context_impl:
   virtual public pcre_context
{
public:


   pcre2_general_context * m_pgc;
   pcre2_compile_context * m_pcc;
   pcre2_match_data *      m_pmd;
   int                     m_iSizeData;


   pcre_context_impl(::aura::application * papp, int iSizeData):
      object(papp),
      pcre_context(papp)
   {

      m_pthis = (void *) this;

      m_pgc = pcre2_general_context_create(NULL,NULL,NULL);

      m_pcc = pcre2_compile_context_create(m_pgc);

      m_iSizeData = iSizeData;

      if(m_iSizeData <= 0)
      {

         m_pmd = NULL;

      }
      else
      {

         m_pmd = pcre2_match_data_create(m_iSizeData,m_pgc);

      }


   }
   
   
   virtual ~pcre_context_impl()
   {

      if(m_pmd != NULL)
      {

         pcre2_match_data_free(m_pmd);

         m_pmd = NULL;

      }


      if(m_pcc != NULL)
      {

         pcre2_compile_context_free(m_pcc);

         m_pcc = NULL;

      }


      if(m_pgc != NULL)
      {

         pcre2_general_context_free(m_pgc);

         m_pgc = NULL;

      }


   }

   
};



class CLASS_DECL_AURA_PCRE pcre_code_impl :
   virtual public pcre_code
{
public:


   pcre2_code *            m_pc;
 

   pcre_code_impl(pcre_context_impl * pcreContext) :
      object(pcreContext->get_app()),
      pcre_util(pcreContext->get_app()),
      pcre_code(pcreContext->get_app())
   {

      m_pc = NULL;

   }

   virtual ~pcre_code_impl()
   {

      if(m_pc != NULL)
      {

         pcre2_code_free(m_pc);

         m_pc = NULL;

      }

   }


   bool compile(pcre_context_impl * pcreContext, const string &str)
   {

      int e;

      PCRE2_SIZE eo;

      m_pc = pcre2_compile((PCRE2_SPTR)(const char *)str,str.get_length(),0,&e,&eo,pcreContext->m_pcc);

      if(m_pc == NULL)
         return false;

      return true;

   }


   virtual int matches(const string & str,pcre_context * pcreContext)
   {

      int c = pcre2_match(m_pc,(PCRE2_SPTR)(const char *)str,str.get_length(),0,0,PC().m_pmd,NULL);

      return c;
   }

   virtual int matches(const char * psz, strsize len, pcre_context * pcreContext)
   {

      int c = pcre2_match(m_pc,(PCRE2_SPTR)psz,len,0,0,PC().m_pmd,NULL);

      return c;
   }


   virtual void matches(int_array & ia, const string & str, pcre_context * pcreContext)
   {

      int c = matches(str, pcreContext);

      if(c == 0)
         return;

      PCRE2_SIZE * ovector = pcre2_get_ovector_pointer(PC().m_pmd);

      for(strsize i = 0; i < c; i++)
      {

         ia.add(ovector[2 * i]);

         ia.add(ovector[2 * i + 1]);

      }

   }

   virtual void matches(int_array & ia,const char * psz, strsize len,pcre_context * pcreContext)
   {

      int c = matches(psz, len,pcreContext);

      if(c == 0)
         return;

      PCRE2_SIZE * ovector = pcre2_get_ovector_pointer(PC().m_pmd);

      for(strsize i = 0; i < c; i++)
      {

         ia.add(ovector[2 * i]);

         ia.add(ovector[2 * i + 1]);

      }

   }

   virtual bool replace(string & str,const string & strPrefix,byte * pd,size_t * ps,pcre_context * pcreContext)
   {

      if(pcre2_substitute(
         m_pc,
         (PCRE2_SPTR8)str.c_str(),
         str.get_length(),
         0,
         PCRE2_SUBSTITUTE_GLOBAL,PC().m_pmd,NULL,(PCRE2_SPTR8)strPrefix.c_str(),strPrefix.get_length(),pd,ps) > 0)
      {

         return true;

      }

      return false;

   }


};


class CLASS_DECL_AURA_PCRE pcre_util_impl:
   virtual public pcre_code_impl
{
public:


   sp(pcre_context_impl) m_pcre;


   pcre_util_impl(pcre_context_impl * pcreContext):
      object(pcreContext->get_app()),
      pcre_util(pcreContext->get_app()),
      pcre_code(pcreContext->get_app()),
      pcre_code_impl(pcreContext)
   {
      
      m_pcre = pcreContext;

   }


   virtual ~pcre_util_impl()
   {


   }

   bool compile(pcre_context_impl * pcreContext,const string &str)
   {

      
      if(!pcre_code_impl::compile(pcreContext,str))
         return false;


      if(m_pcre->m_pmd != NULL)
      {
         
         pcre2_match_data_free(m_pcre->m_pmd);
         
         m_pcre->m_pmd = NULL;

      }

      m_pcre->m_pmd = pcre2_match_data_create_from_pattern(m_pc,m_pcre->m_pgc);

      if(m_pcre->m_pmd == NULL)
         return false;

      return true;

   }



   virtual int matches(const string & str, pcre_context *)
   {

      return pcre_code_impl::matches(str,m_pcre);

   }

   virtual int matches(const char * psz, strsize len,pcre_context *)
   {

      return pcre_code_impl::matches(psz, len,m_pcre);

   }

   virtual void matches(int_array & ia,const string & str,pcre_context * pcreContext)
   {

      return pcre_code_impl::matches(ia, str,m_pcre);

   }

   virtual void matches(int_array & ia,const char * psz,strsize len,pcre_context * pcreContext)
   {

      return pcre_code_impl::matches(ia,psz, len,m_pcre);

   }

};


pcre_context * pcre_context::create_context(::aura::application * papp, int iSizeData)
{

   return canew(pcre_context_impl(papp, iSizeData));

}


pcre_util * pcre_util::compile(::aura::application * papp, const string & str)
{

   pcre_context * pcreContext = pcre_context::create_context(papp, 0);

   pcre_util_impl * putil = canew(pcre_util_impl(dynamic_cast < pcre_context_impl *>(pcreContext)));

   putil->compile(dynamic_cast < pcre_context_impl *>(pcreContext), str);


   return putil;

}


pcre_code * pcre_code::compile(pcre_context * pcreContext,const string & str)
{

   pcre_code_impl * pcode = canew(pcre_code_impl(dynamic_cast < pcre_context_impl *>(pcreContext)));

   pcode->compile(dynamic_cast < pcre_context_impl *>(pcreContext), str);


   return pcode;

}