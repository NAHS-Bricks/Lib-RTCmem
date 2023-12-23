#include <nahs-Bricks-Lib-RTCmem.h>

NahsBricksLibRtcMem::NahsBricksLibRtcMem() {
    read();
    reCalculateCrc();
}

/*
reads RTCmem and caches data in struct
*/
bool NahsBricksLibRtcMem::read() {
    if (ESP.rtcUserMemoryRead(0, (uint32_t*) &_rtcData, sizeof(_rtcData))) return true;
    else return false;
}

/*
calculates crc and writes all data to RTCmem
*/
bool NahsBricksLibRtcMem::write() {
    //update the crc32
    _rtcData.crc32 = calculateCRC32(((uint8_t*) &_rtcData) + 4, RTC_DATA_LENGTH);

    if(ESP.rtcUserMemoryWrite(0, (uint32_t*) &_rtcData, sizeof(_rtcData))) return true;
    else return false;
}

/*
writes an invalid crc to RTCmem, to mark it as invalid
*/
bool NahsBricksLibRtcMem::destroy() {
    _rtcData.crc32 = calculateCRC32(((uint8_t*) &_rtcData) + 4, RTC_DATA_LENGTH);
    _rtcData.crc32++;

    if(ESP.rtcUserMemoryWrite(0, (uint32_t*) &_rtcData, sizeof(_rtcData))) return true;
    else return false;
}

/*
checks if actual crc and stored crc match
*/
bool NahsBricksLibRtcMem::isValid() {
    return (_rtcData.crc32 == _crcCalculated);
}

uint32_t NahsBricksLibRtcMem::crcStored() {
    return _rtcData.crc32;
}

uint32_t NahsBricksLibRtcMem::crcCalculated() {
    return _crcCalculated;
}

void NahsBricksLibRtcMem::reCalculateCrc() {
    _crcCalculated = calculateCRC32(((uint8_t*) &_rtcData) + 4, RTC_DATA_LENGTH);
}

uint16_t NahsBricksLibRtcMem::getSpaceTotal() {
    return RTC_DATA_LENGTH;
}

uint16_t NahsBricksLibRtcMem::getSpaceUsed() {
    return _next_struct_start;
}

uint16_t NahsBricksLibRtcMem::getSpaceLeft() {
    return RTC_DATA_LENGTH - _next_struct_start;
}

uint32_t NahsBricksLibRtcMem::calculateCRC32(const uint8_t *data, size_t length) const {
    uint32_t crc = 0xffffffff;
    while (length--) {
        uint8_t c = *data++;
        for (uint32_t i = 0x80; i > 0; i >>= 1) {
            bool bit = crc & 0x80000000;
            if (c & i) {
                bit = !bit;
            }
            crc <<= 1;
            if (bit) {
                crc ^= 0x04c11db7;
            }
        }
    }
    return crc;
}


//------------------------------------------
// globally predefined variable
#if !defined(NO_GLOBAL_INSTANCES)
NahsBricksLibRtcMem RTCmem;
#endif
