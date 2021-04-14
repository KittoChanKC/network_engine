#include "Utility/Common.h"
#include "TypeDef.h"
#include "Serializer/Serializer.h"
#include "Serializer/Deserializer.h"

namespace _network::_packet {

class Packet
{
public:
    //Type GetType() const { return OnType(); }

protected:
    //virtual Type OnType() const = 0;
    
    // Todo: Serializer
    virtual void OnWrite(_serializer::Serializer& se) = 0;
    virtual void OnRead(_serializer::Deserializer& se)  = 0;

    // TODO: Json Obj
    //virtual void OnToJson(Serializer& se) = 0;
    //virtual void OnFromJson(Deserializer& se) = 0;
};
}   // namespace _network