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


#define CaSys(pca) (*pca->m_papp->m_psystem)
#define Sys(papp) (*papp->m_psystem)
#define System (Sys(this->m_papp))
#define Mathematics(papp) (Sys(papp).math())
#define Math (Mathematics(this->m_papp))

#define Sess(papp) (*papp->m_psession)
#define Session (Sess(this->m_papp))


class fixed_alloc_no_sync;


namespace ca2
{


   class bergedge;
   class system;


   class CLASS_DECL_ca2 ca2 :
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

      uint32_t                m_ulFlags;
      sp(::ca2::application)     m_papp;
      //::ca2::ptra *            m_pptraListener;
      //::ca2::ptra *            m_pptraListened;
      factory_item_base *     m_pfactoryitembase;
      void *                  m_pthis;


      ca2();
      ca2(const ca2 & o);
      ca2(sp(::ca2::application) papp);
      virtual ~ca2();

      virtual void delete_this();


      virtual sp(::ca2::ca2) clone();


      static void system(const char * pszProjectName);

      inline allocatorsp allocer();

      virtual ::ca2::application * get_app() const;
      virtual void set_app(::ca2::application * papp);

      inline bool is_set_ca_flag(::ca2::ca2::flag eflag)
      {
         return (m_ulFlags & ((uint32_t) eflag)) == (uint32_t) eflag;
      }

      inline void clear_ca_flag(::ca2::ca2::flag eflag)
      {
         m_ulFlags &= ~eflag;
      }

      inline void set_ca_flag(::ca2::ca2::flag eflag)
      {
         m_ulFlags |= eflag;
      }


      ca2 & operator = (const ca2 & o);

   };


   class CLASS_DECL_ca2 allocator :
      virtual public ::ca2::ca2
   {
   public:
      

      virtual ~allocator();


   };


   class CLASS_DECL_ca2 allocatorsp :
      public sp(allocator)
   {
   public:


      allocatorsp(sp(application) papp);


   };



} // namespace ca2



