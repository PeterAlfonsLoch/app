#include "framework.h"



index_array::index_array(::ca::application * papp) :
   ca(papp)
{
}

index_array::index_array(const index_array & array) :
   numeric_array < index >(array)
{
   operator = (array);
}

index_array::~index_array()
{
}

index_array index_array::operator - (const index_array & indexa) const
{
   index_array iaRet(*this);
   iaRet.remove(indexa);
   return iaRet;
}

index_array index_array::operator + (const index_array & indexa) const
{
   index_array iaRet(*this);
   iaRet.add(indexa);
   return iaRet;
}




count_array::count_array(::ca::application * papp) :
   ca(papp)
{
}

count_array::count_array(const count_array & array) :
   numeric_array < ::count >(array)
{
   operator = (array);
}

count_array::~count_array()
{
}

count_array count_array::operator - (const count_array & counta) const
{
   count_array iaRet(*this);
   iaRet.remove(counta);
   return iaRet;
}

count_array count_array::operator + (const count_array & counta) const
{
   count_array iaRet(*this);
   iaRet.add(counta);
   return iaRet;
}


int_array::int_array(::ca::application * papp) :
   ca(papp)
{
}

int_array::int_array(const int_array & array) :
   numeric_array < int32_t >(array)
{
   operator = (array);
}

int_array::~int_array()
{
}

int_array int_array::operator - (const int_array & inta) const
{
   int_array iaRet(*this);
   iaRet.remove(inta);
   return iaRet;
}

int_array int_array::operator + (const int_array & inta) const
{
   int_array iaRet(*this);
   iaRet.add(inta);
   return iaRet;
}








int64_array::int64_array(::ca::application * papp) :
   ca(papp)
{
}

int64_array::int64_array(const int64_array & array) :
   numeric_array < int64_t >(array)
{
   operator = (array);
}

int64_array::~int64_array()
{
}

int64_array int64_array::operator - (const int64_array & inta) const
{
   int64_array iaRet(*this);
   iaRet.remove(inta);
   return iaRet;
}

int64_array int64_array::operator + (const int64_array & inta) const
{
   int64_array iaRet(*this);
   iaRet.add(inta);
   return iaRet;
}



























uint64_array::uint64_array(::ca::application * papp) :
   ca(papp)
{
}

uint64_array::uint64_array(const uint64_array & array) :
   numeric_array < uint64_t >(array)
{
   operator = (array);
}

uint64_array::~uint64_array()
{
}

uint64_array uint64_array::operator - (const uint64_array & inta) const
{
   uint64_array iaRet(*this);
   iaRet.remove(inta);
   return iaRet;
}

uint64_array uint64_array::operator + (const uint64_array & inta) const
{
   uint64_array iaRet(*this);
   iaRet.add(inta);
   return iaRet;
}











































unique_int_sort_array::unique_int_sort_array(::ca::application * papp) :
   ca(papp)
{
}

unique_int_sort_array::unique_int_sort_array(const unique_int_sort_array & array) :
   ::ca::ca(array.get_app())
{
   operator = (array);
}

unique_int_sort_array::~unique_int_sort_array()
{
}

unique_int_sort_array unique_int_sort_array::operator - (const unique_int_sort_array & inta) const
{
   unique_int_sort_array iaRet(*this);
   iaRet.remove(inta);
   return iaRet;
}

unique_int_sort_array unique_int_sort_array::operator + (const unique_int_sort_array & inta) const
{
   unique_int_sort_array iaRet(*this);
   for(int32_t i = 0; i < inta.get_count(); i++)
   {
      iaRet.add(inta[i]);
   }
   return iaRet;
}

















































unique_index_sort_array::unique_index_sort_array(::ca::application * papp) :
   ca(papp)
{
}

unique_index_sort_array::unique_index_sort_array(const unique_index_sort_array & array) :
   ::ca::ca(array.get_app())
{
   operator = (array);
}

unique_index_sort_array::~unique_index_sort_array()
{
}

unique_index_sort_array unique_index_sort_array::operator - (const unique_index_sort_array & indexa) const
{
   unique_index_sort_array iaRet(*this);
   iaRet.remove(indexa);
   return iaRet;
}

unique_index_sort_array unique_index_sort_array::operator + (const unique_index_sort_array & indexa) const
{
   unique_index_sort_array iaRet(*this);
   for(index i = 0; i < indexa.get_count(); i++)
   {
      iaRet.add(indexa[i]);
   }
   return iaRet;
}
































































float_array::float_array()
{
}

float_array::float_array(const float_array & array) :
   numeric_array < float >(array)
{
   operator = (array);
}


float_array::~float_array()
{
}


double_array::double_array()
{
}

double_array::~double_array()
{
}

double_array::double_array(const double_array & array) :
   numeric_array < double >(array)
{
   operator = (array);
}


byte_array::byte_array()
{
}

/*byte_array::~byte_array()
{
}*/

uint16_array::uint16_array()
{
}

/*uint16_array::~uint16_array()
{
}*/

uint32_array::uint32_array()
{
}

uint32_array::uint32_array(const uint32_array & array) :
   numeric_array < dword >(array)
{
   operator = (array);
}


uint32_array::~uint32_array()
{
}








uint_ptr_array::uint_ptr_array()
{
}

uint_ptr_array::uint_ptr_array(const uint_ptr_array & array) :
   numeric_array < uint_ptr >(array)
{
   operator = (array);
}


uint_ptr_array::~uint_ptr_array()
{
}







uint_array::uint_array()
{
}

uint_array::uint_array(const uint_array & array) :
   numeric_array < uint32_t > (array)
{
}

uint_array::~uint_array()
{
}
