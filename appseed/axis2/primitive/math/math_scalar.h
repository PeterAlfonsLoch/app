#pragma once



class CLASS_DECL_AXIS double_scalar_source :
   virtual public object
{
public:


   class CLASS_DECL_AXIS listener :
      virtual public object
   {
   public:


      virtual void on_set_scalar(double_scalar_source * psource, e_scalar escalar, double d);


   };


   listener *        m_plistener;

   double_scalar_source();


   bool set_scalar(e_scalar escalar, double d, bool bForce = false);
   bool constrain_scalar(e_scalar escalar, double & d);
   double get_rate(e_scalar escalar, double dDefault = 0.0);
   bool constrain(e_scalar escalar, double & d);
   bool contains(e_scalar escalar, double d);


   virtual void on_set_scalar(e_scalar escalar, double d);
   virtual void get_scalar_minimum(e_scalar escalar, double & d);
   virtual void get_scalar(e_scalar escalar, double & d);
   virtual void get_scalar_maximum(e_scalar escalar, double & d);

};


class CLASS_DECL_AXIS int_scalar_source :
   virtual public object
{
public:


   class CLASS_DECL_AXIS listener :
      virtual public object
   {
   public:


      virtual void on_set_scalar(int_scalar_source * psource, e_scalar escalar, int64_t i);


   };


   listener *        m_plistener;


   int_scalar_source();


   bool set_scalar(e_scalar escalar, int64_t iValue, bool bForce = false);
   bool constrain_scalar(e_scalar escalar, int64_t & iValue);
   void increment_scalar(e_scalar  escalar, int64_t iIncrement);
   double get_rate(e_scalar escalar, double dDefault = 0.0);
   bool constrain(e_scalar escalar, int64_t & i);
   bool contains(e_scalar escalar, int64_t i);


   virtual void on_set_scalar(e_scalar escalar, int64_t iValue);
   virtual void get_scalar_minimum(e_scalar escalar, int64_t & i);
   virtual void get_scalar(e_scalar escalar, int64_t & i);
   virtual void get_scalar_maximum(e_scalar escalar, int64_t & i);

};



class CLASS_DECL_AXIS double_scalar
{
public:

   
   double_scalar();
   double_scalar(double_scalar_source * psource, e_scalar escalar);

   
   double_scalar_source *     m_psource;
   e_scalar                   m_escalar;

   void set(double dValue);
   double get();
   double rate(double dDefault = 0.0);

   double maximum();
   double minimum();


   bool is_null() const { return m_psource == NULL || m_escalar == scalar_none; }
   bool is_setl() const { return !is_null(); }


   operator double () { return get(); }

   double_scalar & operator = (double dValue) { set(dValue); return *this; }



};



class CLASS_DECL_AXIS int_scalar
{
public:


   int_scalar();
   int_scalar(int_scalar_source * psource, e_scalar escalar);


   int_scalar_source *        m_psource;
   e_scalar                   m_escalar;



   void set(int64_t iValue);
   int64_t get();
   void increment(int64_t iValue = 1) { set(get() + iValue); }
   void decrement(int64_t iValue = 1) { set(get() - iValue); }
   double rate(double dDefault = 0.0);

   int64_t maximum();
   int64_t minimum();


   bool is_null() const { return m_psource == NULL || m_escalar == scalar_none; }
   bool is_setl() const { return !is_null(); }

   operator int64_t () { return get();  }

   int_scalar & operator = (int64_t iValue) { set(iValue); return *this; }

   int_scalar & operator ++(int) { increment(); return *this; }
   int_scalar & operator --(int) { decrement(); return *this; }

};


