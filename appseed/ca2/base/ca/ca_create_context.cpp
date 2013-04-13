#include "framework.h"


namespace ca
{


   create_context::create_context(sp(::ca::application) papp) :
      ca(papp),
      ::ca::command(papp),
      m_spApplicationBias(allocer()),
      m_spCommandLine(allocer())
   {

      m_bMakeVisible                      = true;
      m_bTransparentBackground            = true;
      m_bClientOnly                       = false;
      m_bOuterPopupAlertLike              = false;
      m_bHold                             = true;
      m_pviewAlloc                        = ::null();
      m_puiParent                         = ::null();
      m_pthreadParent                     = Application.creation();

   }

   create_context::create_context(sp(::ca::command_thread) pthreadParent) :
      ca(pthreadParent->get_app()),
      ::ca::command(pthreadParent->get_app()),
      m_spApplicationBias(allocer()),
      m_spCommandLine(allocer()),
      m_pthreadParent(pthreadParent)
   {

      m_bMakeVisible                      = true;
      m_bTransparentBackground            = true;
      m_bClientOnly                       = false;
      m_bOuterPopupAlertLike              = false;
      m_bHold                             = true;
      m_pviewAlloc                        = ::null();
      m_puiParent                         = ::null();
      common_construct();

   }

   create_context::create_context(sp(::ca::command_thread) pthreadParent, var varFile, bool bMakeVisible, sp(::user::interaction) puiParent) :
      ca(pthreadParent->get_app()),
      ::ca::command(pthreadParent->get_app()),
      m_spApplicationBias(allocer()),
      m_spCommandLine(allocer()),
      m_pthreadParent(pthreadParent)
   {

      m_pviewAlloc                        = ::null();
      m_puiParent                         = ::null();
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
      m_spApplicationBias(allocer()),
      m_spCommandLine(allocer())
   {
      m_pviewAlloc                        = ::null();
      m_puiParent                         = ::null();
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

      m_pthreadParent->consolidate((sp(::ca::create_context)) this);

      return *this;

   }








} // namespace ca






