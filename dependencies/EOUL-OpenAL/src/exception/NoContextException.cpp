#include <EOUL-OpenAL\exception\NoContextException.h>

namespace EOUL {

	namespace OpenAL {

		NoContextException::NoContextException(std::string msg) : Exception(std::move(msg)) {

		}

		NoContextException::NoContextException(const NoContextException& exception) : Exception(exception) {

		}

		NoContextException::~NoContextException() throw() {

		}

	}

}