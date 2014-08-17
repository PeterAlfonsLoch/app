#pragma once


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
index sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::add_pair(ARG_KEY key, ARG_VALUE newValue)
{

   index i;

   if(!find_key(key, i))
   {

      m_ptra.insert_at(i, new pair(key));

   }

   m_ptra[i]->m_element2 = newValue;

   return i;

}

template < class type_map >
sort_attrib_map < type_map > & sort_attrib_map < type_map >::operator = (const sort_attrib_map & attribmap)
{

   if(this != &attribmap)
   {

      this->remove_all();

      typename type_map::pair * ppair;

      for(index i = 0; i < attribmap.m_ptra.get_count(); i++)
      {

         ppair      = new typename type_map::pair(attribmap.m_ptra[i]->m_element1);

         ppair->m_element2    = attribmap.m_ptra[i]->m_element2;

         this->m_ptra.add(ppair);

      }

   }

   return *this;

}
