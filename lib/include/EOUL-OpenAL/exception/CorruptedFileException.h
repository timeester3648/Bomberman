#pragma once

#include <EOUL-OpenAL\exception\Exception.h>

namespace EOUL {

	namespace OpenAL {

		class CorruptedFileException : public Exception {

			public:

				CorruptedFileException(std::string msg);
				CorruptedFileException(const CorruptedFileException& exception);

				virtual ~CorruptedFileException() throw();

		};

	}

}