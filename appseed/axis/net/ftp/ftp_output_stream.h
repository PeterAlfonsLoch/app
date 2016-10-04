#pragma once


namespace ftp
{


   class CLASS_DECL_AXIS output_stream :
      virtual public itransfer_notification
   {
   public:
      
      
      class implementation;


      sp(implementation)      m_pimpl;


      output_stream(const string& strEolCharacterSequence, const string& strStreamName);
      virtual ~output_stream();

      void SetBuffer(const string& strBuffer);
      const string& GetBuffer();
      void SetStartPosition();
      bool GetNextLine(string& strLine);

      virtual string GetLocalStreamName() const override;
      virtual UINT GetLocalStreamSize() const override;
      virtual void SetLocalStreamOffset(DWORD dwOffsetFromBeginOfStream) override;
      virtual void OnBytesReceived(const memory& vBuffer, long lReceivedBytes) override;
      virtual void OnPreBytesSend(byte* pszBuffer, size_t bufferSize, size_t& bytesToSend) override;
   };



   class CLASS_DECL_AXIS output_stream::implementation:
      virtual public ::object
   {
   public:


      const string mc_strEolCharacterSequence;
      string      m_vBuffer;
      strsize     m_iCurrentPos;
      string      m_strStreamName;


      implementation(const string& strEolCharacterSequence, const string& strStreamName);

      virtual bool GetNextLine(string& strLine);
      virtual void OnPreBytesSend(byte * pszBuffer, size_t bufferSize, size_t& bytesToSend);


   private:

      implementation& operator=(const implementation&); // no implementation for assignment operator

   };


} // namespace ftp


