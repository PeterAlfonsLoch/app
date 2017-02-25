#pragma once


#include "aura/primitive/collection/collection_string_to_string_map.h"


namespace aura
{


   class CLASS_DECL_AURA application_heap
   {
   public:


      string_to_ptr                                   m_appmap;
      ::file::patha                                   m_straMatterLocator;
      string_table                                    m_stringtable;
      string_table                                    m_stringtableStd;
      map < id, id, string, string >                  m_stringmap;


      application_heap(::aura::application * papp)
      {

      }


   };



} // namespace aura



