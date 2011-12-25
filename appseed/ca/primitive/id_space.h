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


   sort_array < id, const id & > * m_pida;


public:

   
   mutex * m_pmutex;
   

   id_space();
   virtual ~id_space();

   
   id operator()(const char * psz);
   id operator()(index i);

   
};




