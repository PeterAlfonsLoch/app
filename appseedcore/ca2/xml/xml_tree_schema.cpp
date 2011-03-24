#include "StdAfx.h"

namespace xml
{

tree_schema::tree_schema()
{

}

tree_schema::~tree_schema()
{

}

string tree_schema::get_node_name(int iNameIndex)
{
   return m_stra[iNameIndex];
}

void tree_schema::set_node_name(int iNameIndex, const char * lpcszName)
{
   m_stra.set_at_grow(iNameIndex, lpcszName);
}

} // namespace xml