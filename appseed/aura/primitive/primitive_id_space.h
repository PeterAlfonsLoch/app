#pragma once




inline index BaseSortCompare(const id & id1, const id & id2)
{


   return (index) (id1.m_psz - id2.m_psz);


}


class mutex;


class CLASS_DECL_AURA id_space
{
protected:


  // index_array                      stackLowerBound;
   //index_array                      stackUpperBound;
   ptr_array < const char  >        m_psza; 

//   void sort();
   bool find(const char * pszFind,index & iIndex);


public:

   
   critical_section * m_pcs;
   

   id_space();
   virtual ~id_space();

   
   id operator()(const char * psz);
   id operator()(int64_t i);

   
};




class CLASS_DECL_AURA strid_array :
   virtual public object
{
protected:


   index_array                      stackLowerBound;
   index_array                      stackUpperBound;
   ptr_array < const char >         m_idptra; // ordered as added
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




