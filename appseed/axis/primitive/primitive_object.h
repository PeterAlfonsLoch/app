#pragma once


class CLASS_DECL_BASE object :
   virtual public waitable
{
public:


   property_set *     m_psetObject;


   object();
   object(const object & objectSrc);              // no implementation
   virtual ~object();  // virtual destructors are necessary


   void common_construct();

   bool IsSerializable() const;


   virtual property & oprop(const char * psz);
   virtual property & oprop(const char * psz) const;
   virtual property_set & propset();


   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;

   object & operator = (const object & objectSrc);       // no implementation


   inline sp(::command_thread) command_thread();


   DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION

};







