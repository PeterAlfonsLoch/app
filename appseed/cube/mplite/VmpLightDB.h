// VmpLightDB.h: interface for the CVmpLightDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMPLIGHTDB_H__4F836913_B853_4853_B90E_E2A82752A6B9__INCLUDED_)
#define AFX_VMPLIGHTDB_H__4F836913_B853_4853_B90E_E2A82752A6B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class MusicalPlayerLightDB  :
   public VmsDataServerInterface
{
public:
	MusicalPlayerLightDB();
	virtual ~MusicalPlayerLightDB();
   
   virtual bool OnSetData(
      const VmsDataKeyInterface & key, 
      int iLine, 
      int iColumn, 
      ex1::BaseSerializable & var, VmsDataUpdateHint * puh);

   virtual bool OnSetData(
      const VmsDataKeyInterface & key, 
      int iLine, 
      int iColumn, 
      gen::Variable & var, VmsDataUpdateHint * puh);

   virtual bool GetData(
      const VmsDataKeyInterface & key, 
      int iLine, 
      int iColumn, 
      ex1::BaseSerializable & var);

   virtual bool GetData(
      const VmsDataKeyInterface & key, 
      int iLine, 
      int iColumn, 
      gen::Variable & var);

};

#endif // !defined(AFX_VMPLIGHTDB_H__4F836913_B853_4853_B90E_E2A82752A6B9__INCLUDED_)
