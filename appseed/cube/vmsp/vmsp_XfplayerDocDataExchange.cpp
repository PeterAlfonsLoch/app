#include "StdAfx.h"
#include "XfplayerDocDataExchange.h"
#include "XfplayerDoc.h"

XfplayerDocDataExchange::XfplayerDocDataExchange(vmsp::DocumentInterface * pdoc)
:
DocumentDataExchange(pdoc)
{

}

XfplayerDocDataExchange::~XfplayerDocDataExchange()
{

}

XfplayerDoc * XfplayerDocDataExchange::get_document()
{
   return (XfplayerDoc *) m_pdocument;
}


int XfplayerDocDataExchange::GetSongEncoding()
{
   return get_document()->GetSongEncoding();
}
