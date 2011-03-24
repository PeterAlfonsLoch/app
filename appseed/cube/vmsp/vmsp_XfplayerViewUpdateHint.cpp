#include "StdAfx.h"
#include "XfplayerViewUpdateHint.h"

XfplayerViewUpdateHint::XfplayerViewUpdateHint()
{
   clear();
}

XfplayerViewUpdateHint::~XfplayerViewUpdateHint()
{

}

flags < XfplayerViewUpdateHint::e_type > & 
XfplayerViewUpdateHint::GetTypeFlags()
{
   return m_etypeflags;
}


void XfplayerViewUpdateHint::AddType(e_type e_type)
{
   GetTypeFlags().signalize(e_type);
}

bool XfplayerViewUpdateHint::HasType(e_type e_type)
{
   return GetTypeFlags().is_signalized(e_type);
}

void XfplayerViewUpdateHint::clear()
{
   m_strBeforeOpenDocumentPath.Empty();
   m_bBeforeOpenDocument = true;
   m_iPlayCount = 0;
   m_iWaitPlayCount = 0;
   m_bShowPlayer = false;
   GetTypeFlags().unsignalize_all();
}
