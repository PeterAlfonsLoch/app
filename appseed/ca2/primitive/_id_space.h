#pragma once


#if !core_level_1 && !core_level_2
#include "template/_template.h"
#include "collection/_sort_array.h"
#endif

inline index BaseSortCompare(id f1, id f2)
{
   return id_cmp(&f1, &f2);
}

class mutex;

class CLASS_DECL_ca2 id_space :
   virtual protected BaseSortArray < id, const id & >
{
public:
   id_space();
   virtual ~id_space();
   id operator()(const char * psz);
   id operator()(index i);
   mutex * m_pmutex;
};
