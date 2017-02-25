#pragma once


#include "aura/primitive/map.h"
#include "aura/primitive/collection/collection_strid_map.h"


namespace aura
{


   class CLASS_DECL_AURA system_heap
   {
   public:


      stridsp(type)                                m_typemap;
      ::string_to_string                           m_mapAppLibrary;
      string_to_int_to_string                      m_mapEnumToName;
      string_to_string_to_int                      m_mapNameToEnum;
      stringa                                      m_straCityLo;
      stringa                                      m_straCity;
      int64_array                                  m_iaIds;
      double_array                                 m_daLon;
      double_array                                 m_daLat;

      string_map < sp(::aura::library) >           m_mapLibrary;

      string_map < openweather_city * >            m_mapCity;


      system_heap(::aura::application * papp)
      {

      }

   };



} // namespace aura



