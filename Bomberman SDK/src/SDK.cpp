#include "SDK.h"

#include <mod\ModAPI.h>

namespace BombermanSDK {

	SDK_API void print(const std::string& str) {

		ModAPI::modLog(str);

	}

}