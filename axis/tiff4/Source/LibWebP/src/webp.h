#pragma once

#include "app/appseed/axis/axis/axis/axis.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "utils/utils.h"
#include "utils/thread.h"
#include "utils/rescaler.h"
#include "utils/random.h"
#include "utils/quant_levels_dec.h"
#include "utils/quant_levels.h"
//#include "utils/huffman_encode.h"
//#include "utils/huffman.h"
#include "utils/filters.h"
#include "utils/color_cache.h"
#include "utils/bit_writer.h"
#include "utils/bit_reader.h"
#include "utils/alpha_processing.h"

/*
#include "dec/alphai.h"
#include "dec/decode_vp8.h"
#include "dec/vp8i.h"
#include "dec/vp8li.h"
#include "dec/webpi.h"
*/

/*
#include "dsp/dsp.h"
#include "dsp/lossless.h"
#include "dsp/yuv.h"
*/

/*
#include "enc/backward_references.h"
#include "enc/cost.h"
#include "enc/histogram.h"
#include "enc/vp8enci.h"
#include "enc/vp8li.h"
*/

/*
#include "mux/muxi.h"
*/

#include "webp/decode.h"
#include "webp/demux.h"
#include "webp/encode.h"
#include "webp/format_constants.h"
#include "webp/mux.h"
#include "webp/mux_types.h"
#include "webp/types.h"


