// Tune1000Info.h: interface for the CTune1000Info class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TUNE1000INFO_H__5151BE4C_FA83_4D11_8DCB_CD0DEA3E29BB__INCLUDED_)
#define AFX_TUNE1000INFO_H__5151BE4C_FA83_4D11_8DCB_CD0DEA3E29BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLASS_DECL_ca CTune1000Info  
{
public:
   CTune1000Info();
   virtual ~CTune1000Info();
   bool is_empty();
   void Empty();
   void Prepare();

   stringa   m_straOther;
   string     m_strSongName;

};

#endif // !defined(AFX_TUNE1000INFO_H__5151BE4C_FA83_4D11_8DCB_CD0DEA3E29BB__INCLUDED_)
