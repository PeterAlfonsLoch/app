#pragma once


namespace core
{


   namespace international
   {


      class locale_schema;


   } // namespace international


} // namespace core



namespace aura
{


   class str_context;


   class CLASS_DECL_AURA str_schema :
      public strid_map < string >
   {
   public:


      id m_idSchema;


      str_schema() { InitHashTable(4 * 1024); };


   };

   class CLASS_DECL_AURA str_locale :
      public strid_map < str_schema >
   {
   public:


      id       m_idLang;

      inline str_schema * get_schema(const ::id & idSchema)
      {
         strid_map < str_schema > ::pair * ppair = PLookup(idSchema);
         if (ppair == NULL)
            return NULL;
         return &ppair->m_element2;
      }


      str_locale() { InitHashTable(256); };


   };


   class CLASS_DECL_AURA str :
      public strid_map < str_locale >
   {
   public:


      str_schema *                      m_pschemaEn;
      str_schema *                      m_pschemaStd;



      str(::aura::application * papp);
      virtual ~str();

      virtual int64_t add_ref()
      {
      
         return ::object::add_ref(); 
      
      }
      virtual int64_t dec_ref()
      {
      
         return ::object::dec_ref(); 
      
      }

      inline str_locale * get_locale(const ::id & idLocale)
      {
         strid_map < str_locale > ::pair * ppair = PLookup(idLocale);
         if (ppair == NULL)
            return NULL;
         return &ppair->m_element2;
      }


      bool initialize();


      void set(const ::id & id, const ::id & idLocale, const ::id & idSchema, const char * psz);
      string get(str_context * pcontext, const ::id & id, bool bIdAsDefaultValue = true);
      string get(str_context * pcontext,const ::id & id,const ::id & idLocale,const ::id & idSchema,bool bIdAsDefaultValue = true);
      void get(stringa & stra, str_context * pcontext, const ::id & id);
      void _get(stringa & stra, str_context * pcontext, const ::id & id);

      bool load(const char * pszBaseDir);
      bool load_uistr_file(const ::id & idLocale, const ::id & idSchema, const char * pszFile);

      string body(const char * psz);

      bool matches(str_context * pcontext, const ::id & id, const char * psz);
      bool begins(str_context * pcontext, const char * psz, const ::id & id);
      bool begins_eat(str_context * pcontext, string & str, const ::id & id);


   };



   class CLASS_DECL_AURA str_context :
      virtual public ::object
   {
   public:



      ::str::international::locale_schema *     m_plocaleschema;


      str *                                     m_pstr;

      str_locale *                              m_plocale;

      str_schema *                              m_pschema;
      str_schema *                              m_pschemaLocale;
      str_schema *                              m_pschemaSchemaEn;
      str_schema *                              m_pschemaSchemaStd;



      ref_array < str_schema >                  m_schemaptra;



      str_context(::aura::application * papp);
      virtual ~str_context();

      virtual int64_t add_ref()
      {

         return ::object::add_ref();

      }
      virtual int64_t dec_ref()
      {

         return ::object::dec_ref();

      }

      inline void defer_ok(str * pstr)
      {
         if (pstr != m_pstr)
         {
            m_pstr = pstr;
            prepare();
         }
      }

      void prepare();

      inline ::str::international::locale_schema & localeschema()
      {
         return *m_plocaleschema;
      }


      inline bool matches(const ::id & id, const char * psz)
      {

         return m_pstr->matches(this, id, psz);

      }


      inline bool begins(const ::id & id, const char * psz)
      {

         return m_pstr->begins(this, id, psz);

      }


      inline bool begins_eat(string & str, const ::id & id)
      {

         return m_pstr->begins_eat(this, str, id);

      }


      inline void get(stringa & stra, const ::id & id)
      {

         return m_pstr->get(stra, this, id);


      }


      inline string get(const ::id & id)
      {
         if (m_pstr == NULL)
            return id;
         return m_pstr->get(this, id);

      }


      virtual bool match(const cregexp_util & u,stringa & stra,const char * psz,id pszExp,id pszRoot);


   };




} // namespace aura




