#ifndef NAHS_BRICKS_LIB_RTCMEM_H
#define NAHS_BRICKS_LIB_RTCMEM_H

#include <Arduino.h>

// Total size of memory is 128 Words (a 32 bit) * 4 = 512 Byte - 4 Byte (for saving CRC)
const unsigned int RTC_DATA_LENGTH = 508;

class NahsBricksLibRtcMem {
    private:
        struct RtcData {
            uint32_t crc32;
            byte data[RTC_DATA_LENGTH];
        } _rtcData;
        bool _valid;
        uint16_t _next_struct_start = 0;
        uint32_t _crcCalculated;

    public:
        NahsBricksLibRtcMem();

        /* reads RTCmem and caches data in struct */
        bool read();

        /* calculates crc and writes all data to RTCmem */
        bool write();

        /* writes an invalid crc to RTCmem, to mark it as invalid */
        bool destroy();

        /* checks if actual crc and stored crc match */
        bool isValid();
        
        uint32_t crcStored();
        uint32_t crcCalculated();
        void reCalculateCrc();
        uint16_t getSpaceTotal();
        uint16_t getSpaceUsed();
        uint16_t getSpaceLeft();

        template<typename T>
        T* registerData() {
            uint16_t this_start = _next_struct_start;
            _next_struct_start += sizeof(T);
            return reinterpret_cast<T*>((uint16_t*) &_rtcData.data + this_start);
        };

    private:
        uint32_t calculateCRC32(const uint8_t *data, size_t length) const;
};

#if !defined(NO_GLOBAL_INSTANCES)
extern NahsBricksLibRtcMem RTCmem;
#endif

#endif // NAHS_BRICKS_LIB_RTCMEM_H
