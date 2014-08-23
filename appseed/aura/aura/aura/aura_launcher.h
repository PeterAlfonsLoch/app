#pragma once


class CLASS_DECL_AURA launcher :
   virtual public object
{
public:


   int m_iStart;

   launcher(int iStart = 11) { m_iStart = iStart;  }


   virtual bool ensure_executable() = 0;

   virtual string get_executable_path() = 0;

   virtual string get_params() { return ""; }

   virtual bool start();

};


