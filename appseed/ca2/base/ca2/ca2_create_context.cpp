#include "framework.h"


namespace ca2
{


   create_context::create_context(sp(::ca2::application) papp) :
      ca2(papp),
      ::ca2::command(papp),
      m_spApplicationBias(allocer()),
      m_spCommandLine(allocer())
   {

      m_bMakeVisible                      = true;
      m_bTransparentBackground            = true;
      m_bClientOnly                       = false;
      m_bOuterPopupAlertLike              = false;
      m_bHold                             = true;
      m_pviewAlloc                        = NULL;
      m_puiParent                         = NULL;
      m_pthreadParent                     = Application.creation();

   }

   create_context::create_context(sp(::ca2::command_thread) pthreadParent) :
      ca2(pthreadParent->get_app()),
      ::ca2::command(pthreadParent->get_app()),
      m_spApplicationBias(allocer()),
      m_spCommandLine(allocer()),
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

   create_context::create_context(sp(::ca2::command_thread) pthreadParent, var varFile, bool bMakeVisible, sp(::user::interaction) puiParent) :
      ca2(pthreadParent->get_app()),
      ::ca2::command(pthreadParent->get_app()),
      m_spApplicationBias(allocer()),
      m_spCommandLine(allocer()),
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
      ca2(createcontext.get_app()),
      ::ca2::command(createcontext.get_app()),
      m_spApplicationBias(allocer()),
      m_spCommandLine(allocer())
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

      m_pthreadParent->consolidate((sp(::ca2::create_context)) this);

      return *this;

   }








} // namespace ca2






