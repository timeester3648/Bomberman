#include "game\BuildType.h"
#include "Main.h"

#ifdef BUILD_EXE		
	#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")
#endif

int main() {

	start();

}