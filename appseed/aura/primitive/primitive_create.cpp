//#include "framework.h"



create::create(::aura::application * papp) :
   object(papp),
   command(papp),
   m_spApplicationBias(allocer()),
   m_spCommandLine(allocer())
{

   m_pthreadParent                     = NULL;
   m_bMakeVisible                      = true;
   m_bTransparentBackground            = true;
   m_bClientOnly                       = false;
   m_bOuterPopupAlertLike              = false;
   m_bHold                             = true;
   m_puiAlloc                          = NULL;
   m_puiParent                         = NULL;
   m_pthreadParent                     = Application.creation();

}

create::create(::command_thread * pthreadParent) :
   object(pthreadParent->get_app()),
   command(pthreadParent->get_app()),
   m_spApplicationBias(allocer()),
   m_spCommandLine(allocer()),
   m_pthreadParent(pthreadParent)
{

   m_bMakeVisible                      = true;
   m_bTransparentBackground            = true;
   m_bClientOnly                       = false;
   m_bOuterPopupAlertLike              = false;
   m_bHold                             = true;
   m_puiAlloc                          = NULL;
   m_puiParent                         = NULL;
   common_construct();

}

create::create(::command_thread * pthreadParent, var varFile, bool bMakeVisible, ::user::primitive * puiParent) :
   object(pthreadParent->get_app()),
   command(pthreadParent->get_app()),
   m_spApplicationBias(allocer()),
   m_spCommandLine(allocer()),
   m_pthreadParent(pthreadParent)
{

   m_puiAlloc                          = NULL;
   m_puiParent                         = NULL;
   m_spCommandLine->m_varFile          = varFile;
   m_bMakeVisible                      = bMakeVisible;
   m_bTransparentBackground            = true;
   m_bHold                             = true;
   m_bClientOnly                       = false;
   m_bOuterPopupAlertLike              = false;
   m_puiParent                         = puiParent;

}

create::create(const create & createcontext) :
   object(createcontext.get_app()),
   command(createcontext.get_app()),
   m_spApplicationBias(allocer()),
   m_spCommandLine(allocer())
{
   m_puiAlloc                          = NULL;
   m_puiParent                         = NULL;
   m_bHold                             = true;
   operator = (createcontext);
}

create::~create()
{
}

create & create::operator = (const create & createcontext)
{

   m_bMakeVisible             = createcontext.m_bMakeVisible;
   m_bTransparentBackground   = createcontext.m_bTransparentBackground;
   m_bClientOnly              = createcontext.m_bClientOnly;
   m_bOuterPopupAlertLike     = createcontext.m_bOuterPopupAlertLike;
   m_bHold                    = createcontext.m_bHold;
   m_puiParent                = createcontext.m_puiParent;
   m_puiAlloc                 = createcontext.m_puiAlloc;
   m_spApplicationBias        .oattrib(createcontext.m_spApplicationBias);
   m_spCommandLine            .oattrib(createcontext.m_spCommandLine);

   m_pthreadParent->consolidate((sp(::create)) this);

   return *this;

}
























