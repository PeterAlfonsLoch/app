#pragma once


class CLASS_DECL_ACE progress_listener :
   virtual public object
{
public:

   virtual void on_progress(double dRate);

};



class CLASS_DECL_ACE int_progress :
   virtual public int_scalar_listener
{
public:


   double               m_dProgressStart;
   double               m_dProgressEnd;
   int_scalar           m_scalar;
   progress_listener *  m_plistener;


   int_progress();
   virtual ~int_progress();

   virtual void trace_progress();

   virtual void trace_progress(int64_t iStep);

   virtual void progress_step();

   virtual void on_set_scalar(int_scalar_source * psource,e_scalar escalar,int64_t iValue,int iFlags);

   int_scalar & operator ()(){ return m_scalar;  }

};
