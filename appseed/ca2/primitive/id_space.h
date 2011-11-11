#pragma once

#include "template/template.h"
#include "collection/sort_array.h"


inline index BaseSortCompare(id f1, id f2)
{
   return id_cmp(&f1, &f2);
}

class mutex;

class CLASS_DECL_ca id_space
{
protected:


   sort_array < id, const id & > * m_pida;


public:
   

   id_space();
   virtual ~id_space();
   id operator()(const char * psz);
   id operator()(index i);
   mutex * m_pmutex;
};
