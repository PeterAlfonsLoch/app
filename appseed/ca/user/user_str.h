#pragma once


namespace ca
{


   namespace international
   {


      class locale_schema;


   } // namespace international


} // namespace ca



namespace user
{


   class str_context;


   class CLASS_DECL_ca str_schema : 
      public map < id, const ::id &, string, const string & >
   {
   public:

      
      id m_idSchema;

      
      str_schema() { InitHashTable(4 * 1024); };


   };

   class CLASS_DECL_ca str_locale : 
      public map < id, const ::id &, str_schema, const str_schema & >
   {
   public:
      
      
      id       m_idLang;

      inline str_schema * get_schema(const ::id & idSchema)
      {
         map < id, const ::id &, str_schema, const str_schema & >::pair * ppair = PLookup(idSchema);
         if(ppair == ::null())
            return ::null();
         return &ppair->m_element2;
      }


      str_locale() { InitHashTable(256); };


   };


   class CLASS_DECL_ca str : 
      public map < id, const ::id &, str_locale, const str_locale & >
   {
   public:


      str_schema *                           m_pschemaEn;
      str_schema *                           m_pschemaStd;
      


      str(::ca::applicationsp papp);


      inline str_locale * get_locale(const ::id & idLocale)
      {
         map < id, const ::id &, str_locale, const str_locale & >::pair * ppair = PLookup(idLocale);
         if(ppair == ::null())
            return ::null();
         return &ppair->m_element2;
      }


      bool initialize();


      void set(const ::id & id, const ::id & idLocale, const ::id & idSchema, const char * psz);
      string get(str_context * pcontext, const ::id & id);
      string get(str_context * pcontext, const ::id & id, const ::id & idLocale, const ::id & idSchema);
      void get(stringa & stra, str_context * pcontext, const ::id & id);

      bool load(const char * pszBaseDir);
      bool load_uistr_file(const ::id & idLocale, const ::id & idSchema, const char * pszFile);

      string body(const char * psz);

      bool matches(str_context * pcontext, const ::id & id, const char * psz);
      bool begins(str_context * pcontext, const char * psz, const ::id & id);
      bool begins_eat(str_context * pcontext, string & str, const ::id & id);
   
   
   };



   class CLASS_DECL_ca str_context :
      virtual public ::ca::object
   {
   public:
      
      
      str *                                  m_pstr;

      
      ::ca::international::locale_schema *    m_plocaleschema;

      str_locale *                           m_plocale;
      
      str_schema *                           m_pschema;
      str_schema *                           m_pschemaLocale;
      str_schema *                           m_pschemaSchemaEn;
      str_schema *                           m_pschemaSchemaStd;

      

      comparable_array < str_schema * >      m_schemaptra;
      


      str_context(::ca::applicationsp papp);
      virtual ~str_context();


      inline void defer_ok(str * pstr)
      {
         if(pstr != m_pstr)
         {
            m_pstr = pstr;
            prepare();
         }
      }
      
      void prepare();

      inline ::ca::international::locale_schema & localeschema()
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

         return m_pstr->get(this, id);

      }


   };




} // namespace user




