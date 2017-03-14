#pragma once


#include "core/core/core.h"
#include "app-core/appseed/hellomultiverse/hellomultiverse.h"
#include "app-core/appseed/multimedia/multimedia/multimedia.h"


#ifdef _ESTAMIRA_LIBRARY
#define CLASS_DECL_ESTAMIRA  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ESTAMIRA  CLASS_DECL_IMPORT
#endif


namespace estamira
{




   class character;
   class tileset;
   class game;


   class application;



} // namespace flag

#undef App
#define App(pbaseapp) (pbaseapp->m_pcoreapp->cast_app < ::estamira::application > ())
#undef Gam
#define Gam(pbaseapp) (*App(pbaseapp).m_pgame.cast < ::estamira::game >())
#undef Game
#define Game (Gam(get_app()))

#define _ESTAMIRA_DEBUG 1

#include "estamira_tileset.h"

#include "estamira_character.h"

#include "estamira_game.h"

#include "estamira_main_frame.h"




#include "estamira_application.h"








