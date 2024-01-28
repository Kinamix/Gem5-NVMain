#ifndef __NVMAIN_FLIPNWRITE_H__
#define __NVMAIN_FLIPNWRITE_H__

#include "..\src/DataEncoder.h"
#include <set>

namespace NVM {

class FlipNWrite : public DataEncoder
{
  public:
    FlipNWrite( );
    ~FlipNWrite( );

    void SetConfig( Config *config, bool createChildren = true );

    ncycle_t Read( NVMainRequest *request );
    ncycle_t Write( NVMainRequest *request );

    void RegisterStats( );
    void CalculateStats( );

  private:
    std::set< uint64_t > flippedAddresses;
  
    uint64_t bitsFlipped;
    uint64_t bitCompareSwapWrites;
    double flipNWriteReduction;
    int fpSize;

    void InvertData( NVMDataBlock &data, uint64_t startBit, uint64_t endBit );
};

};

#endif