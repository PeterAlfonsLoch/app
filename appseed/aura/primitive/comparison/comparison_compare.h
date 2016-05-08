#pragma once


template < typename ARG_KEY >
inline int_ptr CompareElements(ARG_KEY element1, ARG_KEY element2)
{

   return element2 - element1;
}



template <  >
inline int_ptr CompareElements<string>(string element1,string  element2)
{

   return element1.Compare(element2);

}

template <  >
inline int_ptr CompareElements<void *>(void * element1, void *  element2)
{

   return (byte *) element2 - (byte *) element1;

}

