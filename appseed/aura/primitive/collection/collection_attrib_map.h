#pragma once


template <class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class HASH = ::comparison::hash < ARG_KEY >,class EQUALS = ::comparison::equals_type_arg_type < KEY,ARG_KEY > >
map < KEY,ARG_KEY, VALUE,ARG_VALUE,HASH,EQUALS > & copy(map < KEY,ARG_KEY, VALUE,ARG_VALUE,HASH,EQUALS > & m,const map < KEY,ARG_KEY, VALUE,ARG_VALUE,HASH,EQUALS > & attribmap)
{
   if(&m != &attribmap)
   {
      m.remove_all();
      type_map::m_nBlockSize = attribmap.type_map::m_nBlockSize;
      const typename type_map::pair * ppair = attribmap.PGetFirstAssoc();
      while(ppair != NULL)
      {
         m.set_at(ppair->m_element1,ppair->m_element2);
         ppair  = attribmap.PGetNextAssoc(ppair);
      }
   }
   return m;
}



using id_to_index = ::map < id,id,index,index > ;