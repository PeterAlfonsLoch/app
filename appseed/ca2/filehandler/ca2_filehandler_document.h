#pragma once


namespace ca2
{


   namespace filehandler
   {


      class CLASS_DECL_ca2 document:
         virtual public ::userbase::document
      {
      public:
         document(::ca::application * papp);

         virtual BOOL on_new_document();
      public:
         virtual ~document();
      #ifdef _DEBUG
         virtual void assert_valid() const;
         virtual void dump(dump_context & dumpcontext) const;
      #endif

         virtual bool on_open_document(var varFile);

      };



   } // namespace filehandler


} // namespace mail


