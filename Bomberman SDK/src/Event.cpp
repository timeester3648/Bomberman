#include "Event.h"
#include "SDK.h"

#include <mod\ModAPI.h>

namespace BombermanSDK {

	SDK_API void registerGameEvent(EventType type, ::std::function<void ()> callback) {

		ModAPI::registerGameEvent(static_cast<::EventType>(type), callback);

	}

	SDK_API void registerPlayerEvent(EventType type, ::std::function<void (Player*)> callback) {

		ModAPI::registerPlayerEvent(static_cast<::EventType>(type), callback);

	}

	SDK_API void registerWorldEvent(EventType type, ::std::function<void (Level*)> callback) {

		ModAPI::registerWorldEvent(static_cast<::EventType>(type), callback);

	}

}