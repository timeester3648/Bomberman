#include <EOUL-OpenAL\exception\InvalidPathException.h>

namespace EOUL {

	namespace OpenAL {

		InvalidPathException::InvalidPathException(std::string msg) : Exception(std::move(msg)) {

		}

		InvalidPathException::InvalidPathException(const InvalidPathException& exception) : Exception(exception) {

		}

		InvalidPathException::~InvalidPathException() throw() {

		}

	}

}