#include <EOUL-OpenAL\exception\Exception.h>

namespace EOUL {

	namespace OpenAL {

		Exception::Exception(std::string msg) : msg(std::move(msg)) {

		}

		Exception::Exception(const Exception& exception) : msg(exception.msg) {

		}

		Exception::~Exception() throw() {

		}

		const char* Exception::what() const throw() {

			return this->msg.c_str();

		}

		Exception& Exception::operator=(const Exception& exception) {

			this->msg = exception.msg;

			return *this;

		}

	}

}