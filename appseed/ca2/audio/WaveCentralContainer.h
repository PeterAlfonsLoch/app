#pragma once

class audWaveCentral;

class CLASS_DECL_ca audWaveCentralContainer :
   virtual public ::radix::object
{
public:


   audWaveCentral *   m_pwavecentral;


   audWaveCentralContainer();
   virtual ~audWaveCentralContainer();

   audWaveCentral & GetAudioWaveCentral();

};
