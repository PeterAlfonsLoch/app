#pragma once

   class audWaveOut;
   class audWavePreBuffer;

   enum EaudCommand
   {
      audCommandOpenAiffFile,
      audCommandOpenCdaFile,
      audCommandOpenRtpFile, // currently a non seekable mp3 file stream
      audCommandOpenMp3File,
      audCommandOpenVqfFile,
      audCommandOpenWmFile,
      audCommandOpenWavFile,
      audCommandOpenFile,
      audCommandOpenDevice,
      audCommandExecutePlay,
      audCommandExecuteRecord,
      audCommandExecuteStop,
      audCommandExecutePause,
      audCommandExecuteRestart,
      audCommandCloseDevice,
   };

