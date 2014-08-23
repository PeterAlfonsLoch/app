#pragma once


// Memory state for snapshots/leak detection
struct CLASS_DECL_AURA memory_state
{
// Attributes
   enum blockUsage
   {
      freeBlock,    // primitive::memory not used
      objectBlock,  // contains a object derived class object
      bitBlock,     // contains ::operator new data
      crtBlock,
      ignoredBlock,
      nBlockUseMax  // total number of usages
   };

   _CrtMemState m_memState;
   int_ptr m_lCounts[nBlockUseMax];
   int_ptr m_lSizes[nBlockUseMax];
   int_ptr m_lHighWaterCount;
   int_ptr m_lTotalCount;

   memory_state();

// Operations
   void Checkpoint();  // fill with current state
   bool Difference(const memory_state& oldState,
               const memory_state& newState);  // fill with difference
   void update_data();

   // Output to g_dumpcontext
   void dumpStatistics() const;
   void dumpAllObjectsSince() const;
};
