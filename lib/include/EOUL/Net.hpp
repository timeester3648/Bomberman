#pragma once

#pragma comment(lib, "urlmon")
#pragma comment(lib, "WinInet")

#define NOMINMAX
#include <Windows.h>
#include <WinInet.h>

#include <string>
#include <vector>
#include <thread>

namespace EOUL::Net {

	/*

		downloads a file from the given url to the given path. path needs to contain the file name.
		it will use the cache if useCache is true.

	*/
	HRESULT download(std::string url, std::string path, bool useCache = false) {

		if (!useCache) {

			DeleteUrlCacheEntry(url.c_str());

		}

		return URLDownloadToFile(NULL, url.c_str(), path.c_str(), 0, NULL);

	}

	/* returns if the current pc has a internet connection */
	bool hasInternet() {

		DWORD check;
		BOOL access = InternetGetConnectedState(&check, 0);

		return !(check == INTERNET_CONNECTION_OFFLINE || access == 0);

	}

}