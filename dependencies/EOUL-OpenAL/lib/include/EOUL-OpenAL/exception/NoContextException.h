#pragma once

#include <EOUL-OpenAL\exception\Exception.h>

namespace EOUL {

	namespace OpenAL {

		class NoContextException : public Exception {

			public:

				NoContextException(std::string msg);
				NoContextException(const NoContextException& exception);

				virtual ~NoContextException() throw();

		};

	}

}