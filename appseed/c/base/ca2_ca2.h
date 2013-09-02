#pragma once




class factory_item_base;


#define SCAST_PTR(TYPE, ptarget, psource) TYPE * ptarget = dynamic_cast < TYPE * > (psource);
#define SCAST_REF(TYPE, rtarget, psource) TYPE & rtarget = *(dynamic_cast < TYPE * > (psource));



namespace ca2
{


   class ca2;
   class ptra;


} // namespace ca2


namespace plane
{


   class session;
   class system;
   //class cube;


} // namespace plane




class fixed_alloc_no_sync;


namespace ca2
{


   class bergedge;
   class system;


   class CLASS_DECL_c ca2 :
      virtual public ::ca::ca
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
      sp(::application)      m_pcaapp;
      sp(::application)     m_papp;
      //::ca2::ptra *            m_pptraListener;
      //::ca2::ptra *            m_pptraListened;
      factory_item_base *        m_pfactoryitembase;
      void *                     m_pthis;


      element();
      element(const ca2 & o);
      element(sp(::application) papp);
      virtual ~element();

      virtual void delete_this();


      virtual sp(element) clone();


      static void system(const char * pszProjectName);

      inline allocatorsp allocer();

      virtual sp(::application) get_app() const;
      virtual void set_app(sp(::application) papp);

      inline bool is_set_ca_flag(element::flag eflag)
      {
         return (m_ulFlags & ((uint32_t) eflag)) == (uint32_t) eflag;
      }

      inline void clear_ca_flag(element::flag eflag)
      {
         m_ulFlags &= ~eflag;
      }

      inline void set_ca_flag(element::flag eflag)
      {
         m_ulFlags |= eflag;
      }


      ca2 & operator = (const ca2 & o);

   };


   class CLASS_DECL_c allocator :
      virtual public element
   {
   public:
      

      virtual ~allocator();


   };


   class CLASS_DECL_c allocatorsp :
      public sp(allocator)
   {
   public:


      allocatorsp(sp(::application) papp);


   };



} // namespace ca2



