#include "StdAfx.h"
#include "FileManagerViewUpdateHint.h"


FileManagerViewUpdateHint::FileManagerViewUpdateHint()
{
   m_pview = NULL;
}

FileManagerViewUpdateHint::~FileManagerViewUpdateHint()
{

}

bool FileManagerViewUpdateHint::is_type_of(e_type e_type)
{
   return m_etype == e_type;
}

void FileManagerViewUpdateHint::set_type(e_type e_type)
{
   m_etype = e_type;
}
