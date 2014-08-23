#pragma once



template < class type_map >
class attrib_map :
   virtual public type_map
{
public:


   attrib_map(sp(::aura::application) papp = NULL, ::count nBlockSize = 10);
   attrib_map(const attrib_map & map);

   attrib_map & operator = (const attrib_map & map);


};


template < class type_map >
attrib_map < type_map >::attrib_map(sp(::aura::application) papp, ::count nBlockSize) :
   element(papp),
   type_map(papp, nBlockSize)
{
}

template < class type_map >
attrib_map < type_map >::attrib_map(const attrib_map & attribmap) :
   element(attribmap.get_app())
{
   operator = (attribmap);
}

template < class type_map >
attrib_map < type_map > & attrib_map < type_map >::operator = (const attrib_map & attribmap)
{

   if(this != &attribmap)
   {
      this->remove_all();
      type_map::m_nBlockSize = attribmap.type_map::m_nBlockSize;
      const typename type_map::pair * ppair = attribmap.PGetFirstAssoc();
      while(ppair != NULL)
      {
         this->set_at(ppair->first, ppair->second);
         ppair  = attribmap.PGetNextAssoc(ppair);
      }
   }

   return *this;

}




typedef attrib_map < ::map < id, id, index, index > > id_to_index;
