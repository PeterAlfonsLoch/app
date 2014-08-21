#pragma once


#include <assert.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <cmath>
#include <sstream>

#include <zlib.h>


#pragma warning (disable : 4305)
#pragma warning (disable : 4018)
#pragma warning (disable : 4244)
#pragma warning (disable : 4800)
#if (defined _WIN32 || defined _WIN64) && defined _MSC_VER
// suppress exception specification warnings
#pragma warning(disable:4290)
#endif


#include  "Iex.h"


#include  "Half/half.h"


#include "Iex/Iex.h"

#include "IlmThread/IlmThreadMutex.h"
#include "IlmThread/IlmThreadPool.h"
#include "IlmThread/IlmThreadSemaphore.h"
#include "IlmThread/IlmThread.h"


#include "Imath/ImathHalfLimits.h"
#include "Imath/ImathInt64.h"
#include "Imath/ImathInterval.h"
#include "Imath/ImathLimits.h"
#include "Imath/ImathLine.h"
#include "Imath/ImathLineAlgo.h"
#include "Imath/ImathMath.h"
#include "Imath/ImathMatrix.h"
#include "Imath/ImathMatrixAlgo.h"
#include "Imath/ImathPlane.h"
#include "Imath/ImathPlatform.h"
#include "Imath/ImathQuat.h"
#include "Imath/ImathRandom.h"
#include "Imath/ImathRoots.h"
#include "Imath/ImathShear.h"
#include "Imath/ImathSphere.h"
#include "Imath/ImathVec.h"
#include "Imath/ImathVecAlgo.h"
#include "Imath/ImathBox.h"
#include "Imath/ImathBoxAlgo.h"
#include "Imath/ImathColor.h"
#include "Imath/ImathColorAlgo.h"
#include "Imath/ImathEuler.h"
#include "Imath/ImathExc.h"
#include "Imath/ImathFrame.h"
#include "Imath/ImathFrustum.h"
#include "Imath/ImathFrustumTest.h"
#include "Imath/ImathFun.h"
//#include "Imath/ImathGL.h"
#include "Imath/ImathGLU.h"


#include "IlmImf/ImfTiledMisc.h"
#include "IlmImf/ImfTiledOutputFile.h"
#include "IlmImf/ImfTiledRgbaFile.h"
#include "IlmImf/ImfTileOffsets.h"
#include "IlmImf/ImfTimeCode.h"
#include "IlmImf/ImfTimeCodeAttribute.h"
#include "IlmImf/ImfVecAttribute.h"
#include "IlmImf/ImfVersion.h"
#include "IlmImf/ImfWav.h"
#include "IlmImf/ImfXdr.h"
#include "IlmImf/ImfZipCompressor.h"
#include "IlmImf/b44ExpLogTable.h"
#include "IlmImf/ImfAcesFile.h"
#include "IlmImf/ImfArray.h"
#include "IlmImf/ImfAttribute.h"
#include "IlmImf/ImfAutoArray.h"
#include "IlmImf/ImfB44Compressor.h"
#include "IlmImf/ImfBoxAttribute.h"
#include "IlmImf/ImfChannelList.h"
#include "IlmImf/ImfChannelListAttribute.h"
#include "IlmImf/ImfCheckedArithmetic.h"
#include "IlmImf/ImfChromaticities.h"
#include "IlmImf/ImfChromaticitiesAttribute.h"
#include "IlmImf/ImfCompression.h"
#include "IlmImf/ImfCompressionAttribute.h"
#include "IlmImf/ImfCompressor.h"
#include "IlmImf/ImfConvert.h"
#include "IlmImf/ImfCRgbaFile.h"
#include "IlmImf/ImfDoubleAttribute.h"
#include "IlmImf/ImfEnvmap.h"
#include "IlmImf/ImfEnvmapAttribute.h"
#include "IlmImf/ImfFloatAttribute.h"
#include "IlmImf/ImfFrameBuffer.h"
#include "IlmImf/ImfFramesPerSecond.h"
#include "IlmImf/ImfHeader.h"
#include "IlmImf/ImfHuf.h"
#include "IlmImf/ImfInputFile.h"
#include "IlmImf/ImfInt64.h"
#include "IlmImf/ImfIntAttribute.h"
#include "IlmImf/ImfIO.h"
#include "IlmImf/ImfKeyCode.h"
#include "IlmImf/ImfKeyCodeAttribute.h"
#include "IlmImf/ImfLineOrder.h"
#include "IlmImf/ImfLineOrderAttribute.h"
#include "IlmImf/ImfLut.h"
#include "IlmImf/ImfMatrixAttribute.h"
#include "IlmImf/ImfMisc.h"
#include "IlmImf/ImfMultiView.h"
#include "IlmImf/ImfName.h"
#include "IlmImf/ImfOpaqueAttribute.h"
#include "IlmImf/ImfOutputFile.h"
#include "IlmImf/ImfPixelType.h"
#include "IlmImf/ImfPizCompressor.h"
#include "IlmImf/ImfPreviewImage.h"
#include "IlmImf/ImfPreviewImageAttribute.h"
#include "IlmImf/ImfPxr24Compressor.h"
#include "IlmImf/ImfRational.h"
#include "IlmImf/ImfRationalAttribute.h"
#include "IlmImf/ImfRgba.h"
#include "IlmImf/ImfRgbaFile.h"
#include "IlmImf/ImfRgbaYca.h"
#include "IlmImf/ImfRleCompressor.h"
#include "IlmImf/ImfScanLineInputFile.h"
#include "IlmImf/ImfStandardAttributes.h"
#include "IlmImf/ImfStdIO.h"
#include "IlmImf/ImfStringAttribute.h"
#include "IlmImf/ImfStringVectorAttribute.h"
#include "IlmImf/ImfTestFile.h"
#include "IlmImf/ImfThreading.h"
#include "IlmImf/ImfTileDescription.h"
#include "IlmImf/ImfTileDescriptionAttribute.h"
#include "IlmImf/ImfTiledInputFile.h"

