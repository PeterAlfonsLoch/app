#pragma once

namespace netshareclient
{

   class CLASS_DECL_CA2_NETSHARECLIENT application :
      public ::cube::application
   {
   public:


      bergedge *                                   m_pclient;
      ::userbase::single_document_template *       m_pdoctemplate;
      list *                                       m_pnetshareclientlist;
      tree *                                       m_pnetshareclienttree;

      
      application(void);
      virtual ~application(void);

      virtual bool initialize_instance();

      virtual void on_request(::ca::create_context * pcreatecontext);


   };

} // namespace netshareclient