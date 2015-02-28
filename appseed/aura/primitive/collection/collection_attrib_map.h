#pragma once


//template <class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class HASH = ::comparison::hash < ARG_KEY >,class EQUALS = ::comparison::equals_type_arg_type < KEY,ARG_KEY > >
//map < KEY,ARG_KEY, VALUE,ARG_VALUE,HASH,EQUALS > & copy(map < KEY,ARG_KEY, VALUE,ARG_VALUE,HASH,EQUALS > & m,const map < KEY,ARG_KEY, VALUE,ARG_VALUE,HASH,EQUALS > & attribmap)
//{
//   if(&m != &attribmap)
//   {
//      m.remove_all();
//      type_map::m_nBlockSize = attribmap.type_map::m_nBlockSize;
//      const typename type_map::pair * ppair = attribmap.PGetFirstAssoc();
//      while(ppair != NULL)
//      {
//         m.set_at(ppair->m_element1,ppair->m_element2);
//         ppair  = attribmap.PGetNextAssoc(ppair);
//      }
//   }
//   return m;
//}


namespace lemon
{

   namespace map
   {
      template <class MAP >
      MAP & copy(MAP & m,const MAP & attribmap)
      {
         if(&m != &attribmap)
         {
            m.remove_all();
            m.m_nBlockSize = attribmap.m_nBlockSize;
            const typename MAP::pair * ppair = attribmap.PGetFirstAssoc();
            while(ppair != NULL)
            {
               m.set_at(ppair->m_element1,ppair->m_element2);
               ppair  = attribmap.PGetNextAssoc(ppair);
            }
         }
         return m;
      }

   } // namespace map

} // namespace lemon

template < typename TYPE,typename ARG_TYPE = const TYPE &, class HASH =::comparison::hash < const id & >,class EQUALS =::comparison::equals_type_arg_type < id, const id & >, class PAIR = pair < id, TYPE > >
using id_map = ::map < id,const id &, TYPE, ARG_TYPE, HASH, EQUALS, PAIR > ;

template < class HASH =::comparison::hash < const id & >,class EQUALS =::comparison::equals_type_arg_type < id, const id & >  >
using id_to_id = id_map < id,const id &,HASH,EQUALS > ;

template < class HASH =::comparison::hash < const id & >,class EQUALS =::comparison::equals_type_arg_type < id, const id & >  >
using id_to_index = id_map < index,index,HASH,EQUALS > ;