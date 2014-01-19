// PropID.h
// from 7-zip
#pragma once

struct CUInt32PCharPair
{
  uint32 Value;
  const char *Name;
};


namespace libcompress
{

   enum
   {
     kpidNoProperty = 0,
     kpidMainSubfile = 1,
     kpidHandlerItemIndex = 2,
     kpidPath,
     kpidName,
     kpidExtension,
     kpidIsDir,
     kpidSize,
     kpidPackSize,
     kpidAttrib,
     kpidCTime,
     kpidATime,
     kpidMTime,
     kpidSolid,
     kpidCommented,
     kpidEncrypted,
     kpidSplitBefore,
     kpidSplitAfter,
     kpidDictionarySize,
     kpidCRC,
     kpidType,
     kpidIsAnti,
     kpidMethod,
     kpidHostOS,
     kpidFileSystem,
     kpidUser,
     kpidGroup,
     kpidBlock,
     kpidComment,
     kpidPosition,
     kpidPrefix,
     kpidNumSubDirs,
     kpidNumSubFiles,
     kpidUnpackVer,
     kpidVolume,
     kpidIsVolume,
     kpidOffset,
     kpidLinks,
     kpidNumBlocks,
     kpidNumVolumes,
     kpidTimeType,
     kpidBit64,
     kpidBigEndian,
     kpidCpu,
     kpidPhySize,
     kpidHeadersSize,
     kpidChecksum,
     kpidCharacts,
     kpidVa,
     kpidId,
     kpidShortName,
     kpidCreatorApp,
     kpidSectorSize,
     kpidPosixAttrib,
     kpidLink,
     kpidError,

     kpidTotalSize = 0x1100,
     kpidFreeSpace,
     kpidClusterSize,
     kpidVolumeName,

     kpidLocalName = 0x1200,
     kpidProvider,

     kpidUserDefined = 0x10000
   };



} // namespace libcompress

   void FlagsToProp(const CUInt32PCharPair *pairs, unsigned num, uint32 flags, var  * value);

#define FLAGS_TO_PROP(pairs, value, prop) FlagsToProp(pairs, sizeof(pairs) / sizeof(pairs[0]), value, prop)
