#pragma once


#include "core/core/core.h"


#ifdef _ESTAMIRA_LIBRARY
#define CLASS_DECL_ESTAMIRA  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ESTAMIRA  CLASS_DECL_IMPORT
#endif

#define _ESTAMIRA_DEBUG 1

#include "estamira_tileset.h"

#include "estamira_character.h"

#include "estamira_game.h"




