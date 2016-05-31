#pragma once




inline index BaseSortCompare(const id & id1, const id & id2)
{


   return (index) (id1.m_psz - id2.m_psz);


}


class mutex;


class CLASS_DECL_ACE id_space
{
protected:


   raw_array < char *  >      m_psza; 
   critical_section *         m_pcs;


   bool find(const char * pszFind,index & iIndex);

   void free_all();

   

public:

   
   id_space();
   virtual ~id_space();

   
   id operator()(const char * psz);
   id operator()(int64_t i);

   static id_space *                            s_pidspace;

};




class CLASS_DECL_ACE strid_array :
   virtual public object
{
protected:


   index_array                      stackLowerBound;
   index_array                      stackUpperBound;
   raw_array < char * >             m_idptra; // ordered as added
   index_array                      m_iaId; // ordered by id_cmp

   

   void sort();
   bool find(const char * psz, index & iIndex) const;
   

public:

   
   sp(mutex) m_pmutex;
   

   strid_array(bool bSynch);
   virtual ~strid_array();

   void add(const id & id);

   
   bool find(const id & id, index & iIndex) const;

   bool contains(const id & id) const { index iIndex; return find(id, iIndex); }

   
};




CLASS_DECL_ACE ::id_space & get_id_space();
