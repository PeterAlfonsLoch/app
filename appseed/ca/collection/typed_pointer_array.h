#pragma once


template<class BASE_CLASS, class TYPE>
class typed_pointer_array : 
   public typed_ptr_array < TYPE, BASE_CLASS >
{
public:

};
