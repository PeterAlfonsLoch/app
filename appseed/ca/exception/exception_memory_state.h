#pragma once


// Memory state for snapshots/leak detection
struct CLASS_DECL_ca memory_state
{
// Attributes
   enum blockUsage
   {
      freeBlock,    // primitive::memory not used
      objectBlock,  // contains a ::radix::object derived class object
      bitBlock,     // contains ::operator new data
      crtBlock,
      ignoredBlock,
      nBlockUseMax  // total number of usages
   };

   _CrtMemState m_memState;
   LONG_PTR m_lCounts[nBlockUseMax];
   LONG_PTR m_lSizes[nBlockUseMax];
   LONG_PTR m_lHighWaterCount;
   LONG_PTR m_lTotalCount;

   memory_state();

// Operations
   void Checkpoint();  // fill with current state
   BOOL Difference(const memory_state& oldState,
               const memory_state& newState);  // fill with difference
   void UpdateData();

   // Output to g_dumpcontext
   void dumpStatistics() const;
   void dumpAllObjectsSince() const;
};
