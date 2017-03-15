#pragma once

namespace ftp
{

   class CLASS_DECL_AURA file :
      virtual public itransfer_notification
   {
   public:

      ::file::file_sp          m_file;
      string                     m_strFileName;

      //enum TOriginEnum { orBegin = SEEK_SET, orEnd = SEEK_END, orCurrent = SEEK_CUR };

      file(::aura::application * papp);
      virtual ~file();

      bool Open( const string& strFileName, UINT uiMode);

      bool close();

      bool Seek(long lOffset, ::file::e_seek enOrigin);

      long Tell();

      size_t write(const void* pBuffer, size_t itemSize, size_t itemCount);

      size_t Read(void* pBuffer, size_t itemSize, size_t itemCount);

      virtual string GetLocalStreamName() const override;

      virtual UINT GetLocalStreamSize() const override;

      virtual void SetLocalStreamOffset(DWORD dwOffsetFromBeginOfStream) override;

      virtual void OnBytesReceived(const memory & vBuffer, long lReceivedBytes) override;

      virtual void OnPreBytesSend(byte* pszBuffer, size_t bufferSize, size_t& bytesToSend) override;

   };

} // namespace ftp

