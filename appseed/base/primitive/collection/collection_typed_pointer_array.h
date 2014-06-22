#pragma once


template<class BASE_CLASS, class TYPE>
class typed_pointer_array :
   public ptr_array < TYPE, BASE_CLASS >
{
public:

};
