#pragma once

#include <EOUL-OpenAL\exception\Exception.h>

namespace EOUL {

	namespace OpenAL {

		class InvalidPathException : public Exception {

			public:

				InvalidPathException(std::string msg);
				InvalidPathException(const InvalidPathException& exception);

				virtual ~InvalidPathException() throw();

		};

	}

}