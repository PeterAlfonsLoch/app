#pragma once

namespace netshareclient
{

   class CLASS_DECL_CA2_NETSHARECLIENT document:
      public ::userbase::document
   {
   public:

      ::user::place_holder * m_pholderNetshareclientList;

      enum ehint
      {
         hint_netshare = 100,
      };


      string      m_strAddress;
      
      
      document(::ca::application * papp);
	   virtual ~document();


	   virtual BOOL on_new_document();

      virtual bool netshare(const char * psz);

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

   };

} // namespace netshareclient 