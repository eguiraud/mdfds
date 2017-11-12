#ifndef BANKTYPES
#define BANKTYPES

enum class EBankType {
   L0Calo = 0,       //  0
   L0DU,             //  1
   PrsE,             //  2
   EcalE,            //  3
   HcalE,            //  4
   PrsTrig,          //  5
   EcalTrig,         //  6
   HcalTrig,         //  7
   Velo,             //  8
   Rich,             //  9
   TT,               // 10
   IT,               // 11
   OT,               // 12
   Muon,             // 13
   L0PU,             // 14
   DAQ,              // 15
   ODIN,             // 16
   HltDecReports,    // 17
   VeloFull,         // 18
   TTFull,           // 19
   ITFull,           // 20
   EcalPacked,       // 21
   HcalPacked,       // 22
   PrsPacked,        // 23
   L0Muon,           // 24
   ITError,          // 25
   TTError,          // 26
   ITPedestal,       // 27
   TTPedestal,       // 28
   VeloError,        // 29
   VeloPedestal,     // 30
   VeloProcFull,     // 31
   OTRaw,            // 32
   OTError,          // 33
   EcalPackedError,  // 34
   HcalPackedError,  // 35
   PrsPackedError,   // 36
   L0CaloFull,       // 37
   L0CaloError,      // 38
   L0MuonCtrlAll,    // 39
   L0MuonProcCand,   // 40
   L0MuonProcData,   // 41
   L0MuonRaw,        // 42
   L0MuonError,      // 43
   GaudiSerialize,   // 44
   GaudiHeader,      // 45
   TTProcFull,       // 46
   ITProcFull,       // 47
   TAEHeader,        // 48
   MuonFull,         // 49
   MuonError,        // 50
   TestDet,          // 51
   L0DUError,        // 52
   HltRoutingBits,   // 53
   HltSelReports,    // 54
   HltVertexReports, // 55
   HltLumiSummary,   // 56
   L0PUFull,         // 57
   L0PUError,        // 58
   DstBank,          // 59
   DstData,          // 60
   DstAddress,       // 61
   FileID,           // 62
   VP,               // 63
   FTCluster,        // 64
   VL,               // 65
   UT,               // 66
   UTFull,           // 67
   UTError,          // 68
   UTPedestal,       // 69
   HC,               // 70
   HltTrackReports,  // 71
   HCError,          // 72
   // Add new types here. Don't forget to update also RawBank.cpp
   LastType // LOOP Marker; add new bank types ONLY before!
};

#endif // BANKTYPES