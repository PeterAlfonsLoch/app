#pragma once


class CLASS_DECL_AXIS object :
   virtual public waitable
{
public:


   property_set *     m_psetObject;


   object();
   object(const object & objectSrc);              // no implementation
   virtual ~object();  // virtual destructors are necessary


   void common_construct();

   bool IsSerializable() const;



   object & operator = (const object & objectSrc);       // no implementation

   virtual void assert_valid() const;

   DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION

};







