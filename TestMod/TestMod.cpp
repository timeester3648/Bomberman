#include "TestMod.h"

MOD_API void registerMod() {

	MessageBoxA(NULL, "register", "Message", MB_OK);

}

MOD_API void unregisterMod() {

	MessageBoxA(NULL, "unregister", "Message", MB_OK);

}