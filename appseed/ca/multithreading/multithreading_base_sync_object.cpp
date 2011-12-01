#include "StdAfx.h"

base_sync_object::base_sync_object(LPCTSTR pstrName) :
   sync_object < HANDLE > (pstrName)
{
}