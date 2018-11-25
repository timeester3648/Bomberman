#include "../../../header/networking/packet/LevelPacket.h"

LevelPacket::LevelPacket(std::string level_content) : Packet(PacketType::Level, level_content.data(), level_content.length()) {

}