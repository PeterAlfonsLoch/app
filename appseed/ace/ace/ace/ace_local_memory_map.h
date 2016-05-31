#pragma once


// thank you (casey) ; muratori
// old struct beside classy still c spirit/soul // no compositing and also no factoring (so no virtual functions also... )


class CLASS_DECL_ACE local_memory_map :
   virtual public object
{
public:

   string                     m_strName;
   void *                     m_pdata;
#ifdef WINDOWS
   HANDLE                     m_hfile;
   HANDLE                     m_hfilemap;
#else
   int                        m_iFile;
#endif
   bool                       m_bRead;
   bool                       m_bWrite;
   bool                       m_bCreate;
   memory_size_t   m_size;

   local_memory_map();
   local_memory_map(const char * psz,bool bRead,bool bWrite,bool bCreate, memory_size_t size);
   virtual ~local_memory_map();


   void construct();

   bool open();
   bool open(const char * psz,bool bRead,bool bWrite,bool bCreate, memory_size_t size);
   bool close();

   void * get_data();

   bool is_mapped();

   inline string get_name();
   string get_path();

};




inline string local_memory_map::get_name()
{

   return m_strName;

}


inline void * local_memory_map::get_data()
{

   return m_pdata;

}

