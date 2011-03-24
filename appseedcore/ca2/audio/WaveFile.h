#pragma once

class WaveFile
{
public:
   WaveFile(ex1::filesp * pfile);
public:
   ~WaveFile(void);

protected:
   ex1::filesp * m_pfile;
};
