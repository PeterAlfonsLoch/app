
#include "StdAfx.h"
#include "FolderSong.h"


CFolderSongBase::CFolderSongBase()
{
	//	int i = sizeof(*this);
	//	memset( (void*)this, 0, sizeof(*this) );
	Construct();
};

CFolderSongBase::~CFolderSongBase()
{
	//	int i = sizeof(*this);
	//	memset( (void*)this, 0, sizeof(*this) );
	Destruct();
};

void CFolderSongBase::Destruct()
{
}

void CFolderSongBase::Construct()
{
}


CFolderSongBase & CFolderSongBase::operator =(CFolderSongBase *pSrc)
{
	m_iKey		= pSrc->m_iKey;
	m_iParentKey= pSrc->m_iParentKey;
//	CBSTR::Copy(m_bstrName,		pSrc->m_bstrName);

	return *this;
}


