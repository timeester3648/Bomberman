#include <EOUL-OpenAL\exception\NoDeviceException.h>

namespace EOUL {

	namespace OpenAL {

		NoDeviceException::NoDeviceException(std::string msg) : Exception(std::move(msg)) {

		}

		NoDeviceException::NoDeviceException(const NoDeviceException& exception) : Exception(exception) {

		}

		NoDeviceException::~NoDeviceException() throw() {

		}

	}

}