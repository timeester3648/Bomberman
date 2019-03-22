#pragma once

#include <string>
#include <exception>

namespace EOUL {

	namespace OpenAL {

		class Exception : public std::exception {

			private:

				std::string msg;

			public:

				Exception(std::string msg);
				Exception(const Exception& exception);

				virtual ~Exception() throw();

			public:

				virtual const char* what() const throw();

			public:

				Exception& operator=(const Exception& exception);

		};

	}

}