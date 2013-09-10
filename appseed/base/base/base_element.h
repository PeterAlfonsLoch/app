#pragma once


class CLASS_DECL_c base_element :
   virtual public root
{
public:


   enum flag
   {
      flag_auto_clean = 1 << 0,
      flag_discard_to_factory = 1 << 1,
      flag_ready_for_delete = 1 << 2,
      flag_auto_delete = 1 << 3,
      //flag_heap_alloc = 1 << 4,
      flag_locked = 1 << 5,
   };

   uint32_t                   m_ulFlags;
   sp(base_application)      m_pbaseapp;
   //::core::ptra *            m_pptraListener;
   //::core::ptra *            m_pptraListened;
   factory_item_base *        m_pfactoryitembase;
   void *                     m_pthis;


   base_element();
   base_element(const base_element & o);
   base_element(sp(base_application) papp);
   virtual ~base_element();

   virtual void delete_this();


   virtual sp(base_element) clone();


   static void system(const char * pszProjectName);

   inline allocatorsp allocer();

   inline base_application * get_app() const { return m_pbaseapp; }

   virtual void set_app(sp(base_application) papp);

   inline bool is_set_ca_flag(base_element::flag eflag)
   {
      return (m_ulFlags & ((uint32_t) eflag)) == (uint32_t) eflag;
   }

   inline void clear_ca_flag(base_element::flag eflag)
   {
      m_ulFlags &= ~eflag;
   }

   inline void set_ca_flag(base_element::flag eflag)
   {
      m_ulFlags |= eflag;
   }


   base_element & operator = (const base_element & o);


};


class CLASS_DECL_c allocator :
   virtual public base_element
{
public:


   virtual ~allocator();


};


class CLASS_DECL_c allocatorsp :
   public sp(allocator)
{
public:


   allocatorsp(sp(base_application) papp);


};


