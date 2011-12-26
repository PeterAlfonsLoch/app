#pragma once


#include "template/template.h"
#include "collection/sort_array.h"


inline index BaseSortCompare(const id & id1, const id & id2)
{


   return id_cmp(&id1, &id2);


}


class mutex;


class CLASS_DECL_ca id_space
{
protected:


   index_array                      stackLowerBound;
   index_array                      stackUpperBound;
   raw_array < id, const id & >     m_ida; // ordered as added
   index_array                      m_iaStr; // ordered by chType and strcmp

   void sort();
   bool find(const id & id, index & iIndex);


public:

   
   mutex * m_pmutex;
   

   id_space();
   virtual ~id_space();

   
   id operator()(const char * psz);
   id operator()(index i);

   
};




class CLASS_DECL_ca strid_array
{
protected:


   index_array                      stackLowerBound;
   index_array                      stackUpperBound;
   raw_array < const char * >       m_idptra; // ordered as added
   index_array                      m_iaId; // ordered by id_cmp

   

   void sort();
   bool find(const char * psz, index & iIndex) const;
   

public:

   
   mutex * m_pmutex;
   

   strid_array();
   virtual ~strid_array();

   void add(const id & id);

   
   bool find(const id & id, index & iIndex) const;

   
};




