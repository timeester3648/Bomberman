#pragma once

#include <EOUL-OpenAL\exception\Exception.h>

namespace EOUL {

	namespace OpenAL {

		class NoDeviceException : public Exception {

			public:

				NoDeviceException(std::string msg);
				NoDeviceException(const NoDeviceException& exception);

				virtual ~NoDeviceException() throw();

		};

	}

}