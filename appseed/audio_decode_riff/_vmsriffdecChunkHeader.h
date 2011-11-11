// _vmsriffdecChunkHeader.h: interface for the CChunkHeader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSRIFFDECCHUNKHEADER_H__90A43AB8_7DC2_484A_9A28_4283730A416C__INCLUDED_)
#define AFX__VMSRIFFDECCHUNKHEADER_H__90A43AB8_7DC2_484A_9A28_4283730A416C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace _vmsriffdec
{


class CChunkHeader  
{
public:
   union
   {
      struct
      {
         char     m_szId4[4];	   // identifier, e.g. "fmt " or "data"
	      DWORD    m_dwLength4; 	// remaining chunk length after header
      };
      struct
      {
         char     m_szId3[3];	   // identifier, e.g. "fmt " or "data"
	      DWORD    m_dwLength3; 	// remaining chunk length after header
      };
   };

public:
	bool Is_data();
	bool Is_fmt();
	DWORD GetLength();
	CChunkHeader();
	~CChunkHeader();

};

///////////////////////////////////////
} // namespace _vmsriffdec
///////////////////////////////////////

#endif // !defined(AFX__VMSRIFFDECCHUNKHEADER_H__90A43AB8_7DC2_484A_9A28_4283730A416C__INCLUDED_)
