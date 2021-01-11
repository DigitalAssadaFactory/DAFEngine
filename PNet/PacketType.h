#pragma once
#include <stdint.h>


namespace PNet {

	enum class PacketType : uint16_t
	{
		Invalid,
		ChatMessage,
		IntArray,
		Move
	};

}