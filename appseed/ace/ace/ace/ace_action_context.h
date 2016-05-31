#pragma once


namespace action
{


   enum e_context
   {

      context_this_set_text,
      context_this_on_after_set_text

   };
   

   class CLASS_DECL_ACE context :
      public cflag < e_source > 
   {
   public:

      spa(object)       m_spa;



      context() { }
      context(e_source esource) : cflag < e_source >(esource){  }
      context(const cflag<e_source> & esource) : cflag < e_source >(esource) {  }
      context(const context & context) : cflag < e_source >(context) , m_spa(context.m_spa){}
      ~context() {}


      virtual void add(object * pobject);
      virtual index find(object * pobject);
      virtual bool contains(object * pobject);


      inline bool is_source(e_source esource) { return is(esource); }
      inline bool is_user_source() { return is_source(source_user);  }

      context & operator = (const context & context)
      {
         if (this != &context)
         {
            cflag < e_source >::operator=(context);
            m_spa = context.m_spa;
         }
         return *this;
      }

   };


   CLASS_DECL_ACE e_source translation_source(e_source esource, e_context econtextDst, e_context econtextSrc);

   namespace source
   {
      
      static inline context add(e_source esourceAdd, e_source esource){ context ctx(esource); return ctx + esourceAdd; }
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
      static inline context system_default(context ctx, e_source esourceRemove = source_none) { return system(add(ctx, source_default), esourceRemove); }
      static inline context database_default(context ctx, e_source esourceRemove = source_none) { return database(add(ctx, source_default), esourceRemove); }

   }



} // namespace action




