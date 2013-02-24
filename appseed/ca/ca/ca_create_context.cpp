#include "framework.h"


namespace ca
{


   create_context::create_context(::ca::application * papp) :
      ca(papp),
      ::ca::command(papp),
      m_spApplicationBias(papp),
      m_spCommandLine(papp)
   {

      m_bMakeVisible                      = true;
      m_bTransparentBackground            = true;
      m_bClientOnly                       = false;
      m_bOuterPopupAlertLike              = false;
      m_bHold                             = true;
      m_pviewAlloc                        = NULL;
      m_puiParent                         = NULL;
      m_pthreadParent                     = &Application.creation();

   }

   create_context::create_context(::ca::command_thread * pthreadParent) :
      ca(pthreadParent->get_app()),
      ::ca::command(pthreadParent->get_app()),
      m_spApplicationBias(pthreadParent->get_app()),
      m_spCommandLine(pthreadParent->get_app()),
      m_pthreadParent(pthreadParent)
   {

      m_bMakeVisible                      = true;
      m_bTransparentBackground            = true;
      m_bClientOnly                       = false;
      m_bOuterPopupAlertLike              = false;
      m_bHold                             = true;
      m_pviewAlloc                        = NULL;
      m_puiParent                         = NULL;
      common_construct();

   }

   create_context::create_context(::ca::command_thread * pthreadParent, var varFile, bool bMakeVisible, ::user::interaction * puiParent) :
      ca(pthreadParent->get_app()),
      ::ca::command(pthreadParent->get_app()),
      m_spApplicationBias(pthreadParent->get_app()),
      m_spCommandLine(pthreadParent->get_app()),
      m_pthreadParent(pthreadParent)
   {

      m_pviewAlloc                        = NULL;
      m_puiParent                         = NULL;
      m_spCommandLine->m_varFile          = varFile;
      m_bMakeVisible                      = bMakeVisible;
      m_bTransparentBackground            = true;
      m_bHold                             = true;
      m_bClientOnly                       = false;
      m_bOuterPopupAlertLike              = false;
      m_puiParent                         = puiParent;

   }

   create_context::create_context(const create_context & createcontext) :
      ca(createcontext.get_app()),
      ::ca::command(createcontext.get_app()),
      m_spApplicationBias(createcontext.get_app()),
      m_spCommandLine(createcontext.get_app())
   {
      m_pviewAlloc                        = NULL;
      m_puiParent                         = NULL;
      m_bHold                             = true;
      operator = (createcontext);
   }

   create_context::~create_context()
   {
   }

   create_context & create_context::operator = (const create_context & createcontext)
   {
      
      m_bMakeVisible             = createcontext.m_bMakeVisible;
      m_bTransparentBackground   = createcontext.m_bTransparentBackground;
      m_bClientOnly              = createcontext.m_bClientOnly;
      m_bOuterPopupAlertLike     = createcontext.m_bOuterPopupAlertLike;
      m_bHold                    = createcontext.m_bHold;
      m_puiParent                = createcontext.m_puiParent;
      m_pviewAlloc               = createcontext.m_pviewAlloc;
      m_spApplicationBias        .oattrib(createcontext.m_spApplicationBias);
      m_spCommandLine            .oattrib(createcontext.m_spCommandLine);

      m_pthreadParent->consolidate(this);

      return *this;

   }






   create_context_sp::create_context_sp()
   {
   }

   create_context_sp::create_context_sp(::ca::command_thread * pthreadParent) :
      ca(pthreadParent->get_app())
   {

      m_p = NULL;
      operator ()(new ::ca::create_context(pthreadParent));

   }

   create_context_sp::create_context_sp(::ca::command_thread * pthreadParent, var varFile, bool bMakeVisible, ::user::interaction * puiParent) :
      ca(pthreadParent->get_app())
   {
      
      m_p = NULL;
      operator ()(new ::ca::create_context(pthreadParent, varFile, bMakeVisible, puiParent));
      
   }



   create_context_sp::create_context_sp(::ca::application * papp) :
      ca(papp),
      ::ca::smart_pointer < create_context > (papp)
   {
   }

    
   create_context_sp::~create_context_sp()
   {
   }



} // namespace ca


