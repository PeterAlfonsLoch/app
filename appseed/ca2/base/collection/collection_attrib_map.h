#pragma once



template < class type_map >
class attrib_map :
   virtual public type_map
{
public:


   attrib_map(int_ptr nBlockSize = 10);
   attrib_map(const attrib_map & map);

   attrib_map & operator = (const attrib_map & map);


};


template < class type_map >
attrib_map < type_map >::attrib_map(int_ptr nBlockSize) :
   type_map(nBlockSize)
{
}

template < class type_map >
attrib_map < type_map >::attrib_map(const attrib_map & attribmap)
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
      while(ppair != ::null())
      {
         this->set_at(ppair->m_element1, ppair->m_element2);
         ppair  = attribmap.PGetNextAssoc(ppair);
      }
   }

   return *this;

}




