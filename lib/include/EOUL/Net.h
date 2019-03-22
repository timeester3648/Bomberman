#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN

#include <string>
#include <vector>
#include <thread>

namespace EOUL {

	namespace Net {

		/* downloads a file from the given url to the given path. path needs to contain the file name. */
		HRESULT download(std::string url, std::string path);

		/* returns if the current pc has a internet connection */
		bool hasInternet();

		/* performs a http get request */
		std::string httpGetRequest(std::string url);

	}

}