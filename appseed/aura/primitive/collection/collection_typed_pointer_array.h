#pragma once


template<class AXIS_CLASS, class TYPE>
class typed_pointer_array :
   public ptr_array < TYPE, AXIS_CLASS >
{
public:

};
