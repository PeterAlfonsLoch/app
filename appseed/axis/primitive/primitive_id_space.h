#pragma once




inline index BaseSortCompare(const id & id1, const id & id2)
{


   return (index) (id1.m_pstr - id2.m_pstr);


}


class mutex;


class CLASS_DECL_AXIS id_space
{
protected:


   raw_index_array                      stackLowerBound;
   raw_index_array                      stackUpperBound;
   raw_array < id, const id & >         m_ida; // ordered as added
   raw_index_array                      m_iaStr; // ordered by chType and strcmp

   void sort();
   bool find(const id & id, index & iIndex);


public:

   
   mutex * m_pmutex;
   

   id_space();
   virtual ~id_space();

   
   id operator()(const string & str);
   id operator()(int64_t i);

   
};




class CLASS_DECL_AXIS strid_array :
   virtual public root
{
protected:


   raw_index_array                      stackLowerBound;
   raw_index_array                      stackUpperBound;
   raw_array < const char * >           m_idptra; // ordered as added
   raw_index_array                      m_iaId; // ordered by id_cmp

   

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




