/**
 * Furnace Tracker - multi-system chiptune tracker
 * Copyright (C) 2021-2022 tildearrow and contributors
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _SYSMD_H
#define _SYSMD_H
#include "fmshared_OPN.h"
#include "../macroInt.h"
#include "../../../extern/Nuked-OPF2/ym5173.h"
//#include "../../../extern/Nuked-OPN2/ym3438.h"
//#include "sound/ymfm/ymfm_opn.h"


//class DivYM2612Interface: public ymfm::ymfm_interface {
//
//};

class DivPlatformSysMD: public DivPlatformOPN {
  protected:
    const unsigned short chanOffs[6]={
      0x00, 0x01, 0x02, 0x100, 0x101, 0x102
    };

    const unsigned char konOffs[6]={
      0, 1, 2, 4, 5, 6
    };

    struct Channel {
      DivInstrumentFM state;
      DivMacroInt std;
      unsigned char freqH, freqL;
      int freq, baseFreq, pitch, pitch2, portaPauseFreq, note;
      int ins;
      bool active, insChanged, freqChanged, keyOn, keyOff, portaPause, furnaceDac, inPorta, hardReset, opMaskChanged;
      int vol, outVol;
      unsigned char pan, opMask;

      bool dacMode;
      int dacPeriod;
      int dacRate;
      unsigned int dacPos;
      int dacSample;
      int dacDelay;
      bool dacReady;
      bool dacDirection;
      unsigned char sampleBank;
      signed char dacOutput;
      void macroInit(DivInstrument* which) {
        std.init(which);
        pitch2=0;
      }
      Channel():
        freqH(0),
        freqL(0),
        freq(0),
        baseFreq(0),
        pitch(0),
        pitch2(0),
        portaPauseFreq(0),
        note(0),
        ins(-1),
        active(false),
        insChanged(true),
        freqChanged(false),
        keyOn(false),
        keyOff(false),
        portaPause(false),
        furnaceDac(false),
        inPorta(false),
        hardReset(false),
        opMaskChanged(false),
        vol(0),
        outVol(0),
        pan(3),
        opMask(15),
        dacMode(false),
        dacPeriod(0),
        dacRate(0),
        dacPos(0),
        dacSample(-1),
        dacDelay(0),
        dacReady(true),
        dacDirection(false),
        sampleBank(0),
        dacOutput(0) {}
    };
    Channel chan[10];
    DivDispatchOscBuffer* oscBuf[10];
    bool isMuted[10];
    ym5173_t fm;

    //ymfm::ym2612* fm_ymfm;
    //ymfm::ym2612::output_data out_ymfm;
    //DivYM2612Interface iface;
  
    unsigned char lfoValue;

    int softPCMTimer;

    bool extMode, softPCM/*, useYMFM*/;
    bool ladder;
  
    unsigned char dacVolTable[128];
  
    friend void putDispatchChip(void*,int);
    friend void putDispatchChan(void*,int,int);

    inline void processDAC();
    void acquire_nuked(short* bufL, short* bufR, size_t start, size_t len);
    //void acquire_ymfm(short* bufL, short* bufR, size_t start, size_t len);
  
  public:
    void acquire(short* bufL, short* bufR, size_t start, size_t len);
    int dispatch(DivCommand c);
    void* getChanState(int chan);
    DivMacroInt* getChanMacroInt(int ch);
    DivDispatchOscBuffer* getOscBuffer(int chan);
    unsigned char* getRegisterPool();
    int getRegisterPoolSize();
    void reset();
    void forceIns();
    void tick(bool sysTick=true);
    void muteChannel(int ch, bool mute);
    bool isStereo();
    //void setYMFM(bool use);
    bool keyOffAffectsArp(int ch);
    bool keyOffAffectsPorta(int ch);
    void toggleRegisterDump(bool enable);
    void setFlags(const DivConfig& flags);
    void notifyInsChange(int ins);
    void notifyInsDeletion(void* ins);
    void setSoftPCM(bool value);
    int getPortaFloor(int ch);
    void poke(unsigned int addr, unsigned short val);
    void poke(std::vector<DivRegWrite>& wlist);
    int init(DivEngine* parent, int channels, int sugRate, const DivConfig& flags);
    void quit();
    DivPlatformSysMD():
      DivPlatformOPN(9440540.0, 72, 32) {}
    ~DivPlatformSysMD();
};
#endif
