#pragma once

class SampleService : public Kerr::ServiceBase
{
public:

    SampleService() :
        m_stopping(false)
    {
        // Do nothing
    }

    virtual void Start(DWORD)
    {
        Kerr::ThreadPool::QueueUserWorkItem(ServiceThread, 
                                            this);
    }

    virtual void Stop(DWORD)
    {
        m_stopping = true;
        m_stopped.Wait();
    }

private:

    void ServiceThread()
    {
        while (!m_stopping)
        {
            // Simulate waiting for client connection...
            ::Sleep(2000);
        }

        m_stopped.Signal();
    }

    Kerr::ManualResetEvent m_stopped;
    bool m_stopping;

};
