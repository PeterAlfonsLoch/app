#pragma once


class CLASS_DECL_CA2_CUBE VmpPlusThread :
   public ::radix::thread
{
   // // DECLARE_DYNCREATE(VmpPlusThread)
// Attributes
protected:
   bool               m_bEnableWaveInMessageTranslation;
   base_array <int, int >  m_iaNotes;

// Attributes
public:
   void EnableWaveInMessageTranslation(bool bEnable = true);
public:
   VmpPlusThread(::ca::application * papp);           // protected constructor used by dynamic creation
// Operations
public:

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(VmpPlusThread)
   public:
   virtual bool initialize_instance();
   virtual int exit_instance();
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual ~VmpPlusThread();

   
};

