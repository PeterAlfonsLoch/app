#pragma once


namespace alatel
{

   class CLASS_DECL_CA2_ALARM main_document :
      public ::userbase::document
   {
   public:

      
      main_document(::ca::application * papp);
	   virtual ~main_document();
	   

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context& dc) const;
   #endif

	   virtual BOOL on_new_document();
      bool on_open_document(var varFile);

   };


} // namespace alatel


