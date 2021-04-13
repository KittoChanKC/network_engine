#include "Utility/Common.h"
#include "TypeDef.h"

namespace _network::_packet {

enum class PacketType : u16
{
    None,
    Version,
};

class Packet
{
public:
    using Type = PacketType;
    Type GetType() const { return OnType(); }

protected:
    virtual Type OnType() const = 0;
    
    // Todo: Serializer
    //virtual void OnToBuffer(Serializer& se) = 0;
    //virtual void OnFromBuffer(Deserializer& se) = 0;

    // TODO: Json Obj
    //virtual void OnToJson(Serializer& se) = 0;
    //virtual void OnFromJson(Deserializer& se) = 0;
};
}   // namespace _network