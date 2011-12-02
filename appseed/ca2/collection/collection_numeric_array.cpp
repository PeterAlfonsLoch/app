#include "StdAfx.h"



index_array::index_array(::ax::application * papp) :
   ax(papp)
{
}

index_array::index_array(const index_array & base_array) :
   numeric_array < index >(base_array)
{
   operator = (base_array);
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




count_array::count_array(::ax::application * papp) :
   ax(papp)
{
}

count_array::count_array(const count_array & base_array) :
   numeric_array < count >(base_array)
{
   operator = (base_array);
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


int_array::int_array(::ax::application * papp) :
   ax(papp)
{
}

int_array::int_array(const int_array & base_array) :
   numeric_array < int >(base_array)
{
   operator = (base_array);
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








int64_array::int64_array(::ax::application * papp) :
   ax(papp)
{
}

int64_array::int64_array(const int64_array & base_array) :
   numeric_array < int64_t >(base_array)
{
   operator = (base_array);
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



























uint64_array::uint64_array(::ax::application * papp) :
   ax(papp)
{
}

uint64_array::uint64_array(const uint64_array & base_array) :
   numeric_array < uint64 >(base_array)
{
   operator = (base_array);
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











































unique_int_sort_array::unique_int_sort_array(::ax::application * papp) :
   ax(papp)
{
}

unique_int_sort_array::unique_int_sort_array(const unique_int_sort_array & base_array) :
   ::ax::ax(base_array.get_app())
{
   operator = (base_array);
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
   for(int i = 0; i < inta.get_count(); i++)
   {
      iaRet.add(inta[i]);
   }
   return iaRet;
}



float_array::float_array()
{
}

float_array::float_array(const float_array & base_array) :
   numeric_array < float >(base_array)
{
   operator = (base_array);
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

double_array::double_array(const double_array & base_array) :
   numeric_array < double >(base_array)
{
   operator = (base_array);
}


byte_array::byte_array()
{
}

/*byte_array::~byte_array()
{
}*/

word_array::word_array()
{
}

/*word_array::~word_array()
{
}*/

dword_array::dword_array()
{
}

dword_array::dword_array(const dword_array & base_array) :
   numeric_array < dword >(base_array)
{
   operator = (base_array);
}


dword_array::~dword_array()
{
}

uint_array::uint_array()
{
}

uint_array::uint_array(const uint_array & base_array) :
   numeric_array < uint > (base_array)
{
}

uint_array::~uint_array()
{
}
