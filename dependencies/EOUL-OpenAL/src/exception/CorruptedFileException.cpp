#include <EOUL-OpenAL\exception\CorruptedFileException.h>

namespace EOUL {

	namespace OpenAL {

		CorruptedFileException::CorruptedFileException(std::string msg) : Exception(std::move(msg)) {

		}

		CorruptedFileException::CorruptedFileException(const CorruptedFileException& exception) : Exception(exception) {

		}

		CorruptedFileException::~CorruptedFileException() throw() {

		}

	}

}