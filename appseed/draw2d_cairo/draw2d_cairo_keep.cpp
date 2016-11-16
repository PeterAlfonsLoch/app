#include "framework.h"


cairo_keep::cairo_keep(cairo_t * pgraphics, bool bSave)
{

   m_bSave = false;

   if (pgraphics == NULL)
   {

      m_pdc = NULL;

      return;

   }

   m_pdc = pgraphics;

   if (bSave)
   {

      save();

   }

}


cairo_keep::~cairo_keep()
{

   if(m_bSave)
   {

      restore();

   }

}



void cairo_keep::save()
{

   if(m_pdc == NULL)
      return;

   if(m_bSave)
      return;

   synch_lock sl(cairo_mutex());

   cairo_save(m_pdc);

   m_bSave = true;

}


void cairo_keep::restore()
{

   if(m_pdc == NULL)
      return;

   if(!m_bSave)
      return;

   synch_lock sl(cairo_mutex());

   cairo_restore(m_pdc);

   m_bSave = false;

}


void cairo_keep::pulse()
{

   restore();

   save();

}