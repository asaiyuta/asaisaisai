#ifndef PORT_REG_ARRAY
#define PORT_REG_ARRAY
#include <Array>

namespace asl{
    class PortRegArray{
    public:
        PortRegArray();
        ~PortRegArray();
        std::array<uint8_t*, 34> mapPinToReg;
        std::array<uint32_t*,34> gpioBitBand;
        std::array<uint32_t*,34> pinConfig;
        uint32_t pullUp;
    };
}
#endif
