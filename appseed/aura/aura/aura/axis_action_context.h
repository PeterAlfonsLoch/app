#pragma once


namespace action
{


   enum e_context
   {

      context_this_set_text,
      context_this_on_after_set_text

   };
   

   class CLASS_DECL_AXIS context
   {
   public:



      class CLASS_DECL_AXIS data :
         virtual public root
      {
      public:

         
         
         e_source          m_esource;
         spa(object)       m_spa;


         data(e_source esource) { m_esource = esource; }
         data(const data & data) { m_esource = data.m_esource; m_spa.copy(data.m_spa); }
         virtual ~data() {};

         data & operator = (const data & data)
         {
            if (this != &data)
            {
               m_esource = data.m_esource;
               m_spa.copy(data.m_spa);
            }
            return *this;
         }

      };

      sp(data)       m_spdata;


      context() { m_spdata = canew(data(source_none)); }
      context(e_source esource) { m_spdata = canew(data(esource)); }
      context(const context & context) { m_spdata = canew(data(*context.m_spdata)); }
#ifdef MOVE_SEMANTICS
      context(context && context) { m_spdata.m_p = context.m_spdata.m_p; context.m_spdata.m_p = NULL; }
#endif
      ~context() {}


      virtual void add(object * pobject);
      virtual index find(object * pobject);
      virtual bool contains(object * pobject);


      inline context & operator += (e_source esourceAdd) { m_spdata->m_esource = (e_source)(esourceAdd | m_spdata->m_esource); return *this; }
      inline context & operator -= (e_source esourceRemove)  { m_spdata->m_esource = (e_source)(m_spdata->m_esource & ~(int)(esourceRemove)); return *this; }

      inline context operator + (e_source esourceAdd) { context ctx(*this); ctx += esourceAdd; return ctx; }
      inline context operator - (e_source esourceRemove)  { context ctx(*this); ctx -= esourceRemove; return ctx; }

      inline bool is_source(e_source esource) { return (m_spdata->m_esource & esource) != 0; }
      inline bool is_user_source() { return is_source(source_user);  }

      context & operator = (const context & context)
      {
         if (this != &context)
         {
            m_spdata = canew(data(*context.m_spdata));
         }
         return *this;
      }
#ifdef MOVE_SEMANTICS
      context & operator = (context && context)
      {
         if (this != &context)
         {
            m_spdata.m_p = context.m_spdata.m_p;
            context.m_spdata.m_p = NULL;
         }
         return *this;
      }
#endif

   };


   CLASS_DECL_AXIS e_source translation_source(e_source esource, e_context econtextDst, e_context econtextSrc);

   namespace source
   {
      
      static inline context add(e_source esourceAdd, e_source esource) { context ctx(esource); return ctx + esourceAdd; }
      static inline context remove(e_source esource, e_source esourceRemove)  { context ctx(esource); return ctx - esourceRemove; }
      static inline context add_remove(e_source esource, e_source esourceAdd, e_source esourceRemove)  { context ctx(esource); return ctx + esourceAdd - esourceRemove; }
      static inline context sync(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_remove(source_sync, esourceAdd, esourceRemove); }
      static inline context sel(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_remove(source_selection, esourceAdd, esourceRemove); }
      static inline context user(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_remove(source_user, esourceAdd, esourceRemove); }
      static inline context database(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_remove(source_database, esourceAdd, esourceRemove); }
      static inline context system(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_remove(source_system, esourceAdd, esourceRemove); }
      static inline context data(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_remove(source_data, esourceAdd, esourceRemove); }
      static inline context op(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_remove(source_operator, esourceAdd, esourceRemove); }


      static inline context add(context ctx, e_source esourceAdd) { return ctx + esourceAdd; }
      static inline context remove(context ctx, e_source esourceRemove)  { return ctx - esourceRemove; }
      static inline context add_remove(context ctx, e_source esourceAdd, e_source esourceRemove)  { return ctx + esourceAdd - esourceRemove; }
      static inline context sync(context ctx, e_source esourceRemove = source_none) { return add_remove(ctx, source_sync, esourceRemove); }
      static inline context sel(context ctx, e_source esourceRemove = source_none) { return add_remove(ctx, source_selection, esourceRemove); }
      static inline context user(context ctx, e_source esourceRemove = source_none) { return add_remove(ctx, source_user, esourceRemove); }
      static inline context database(context ctx, e_source esourceRemove = source_none) { return add_remove(ctx, source_database, esourceRemove); }
      static inline context system(context ctx, e_source esourceRemove = source_none) { return add_remove(ctx, source_system, esourceRemove); }
      static inline context data(context ctx, e_source esourceRemove = source_none) { return add_remove(ctx, source_data, esourceRemove); }
      static inline context op(context ctx, e_source esourceRemove = source_none) { return add_remove(ctx, source_operator, esourceRemove); }



      static inline context system_default(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return system(add(source_default, esourceAdd), esourceRemove); }
      static inline context database_default(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return database(add(source_default, esourceAdd), esourceRemove); }
      static inline context system_default(context ctx, e_source esourceRemove = source_none) { return system(ctx + source_default, esourceRemove); }
      static inline context database_default(context ctx, e_source esourceRemove = source_none) { return database(ctx + source_default, esourceRemove); }

   }



} // namespace action




