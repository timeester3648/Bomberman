#pragma once

#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

namespace EOUL {

	namespace Util {

		/* returns if the given string starts with the given prefix */
		bool startsWith(const std::string& str, const std::string& prefix);
		/* returns if the given string ends with the given suffix */
		bool endsWith(const std::string& str, const std::string& suffix);
		/* returns if the given string contains a string */
		bool contains(const std::string& str, const std::string& part);

		/* returns if the given string starts with the given prefix */
		bool startsWith(const std::wstring& str, const std::wstring& prefix);
		/* returns if the given string ends with the given suffix */
		bool endsWith(const std::wstring& str, const std::wstring& suffix);
		/* returns if the given string contains a string */
		bool contains(const std::wstring& str, const std::wstring& part);

		/* converts a std::string to a std::wstring */
		std::wstring toWString(const std::string& str);
		/* converts a std::string to a std::wstring */
		std::string toString(const std::wstring& str);

		/* replaces a sequense of characters in a string */
		void replace(std::string& str, const std::string& toReplace, const std::string& toReplaceWith);
		/* replaces a sequense of characters in a string */
		void replace(std::wstring& str, const std::wstring& toReplace, const std::wstring& toReplaceWith);

		/* returns a vector of strings splitted by the delimiter */
		std::vector<std::string> splitString(const std::string& str, char delim = ' ');
		/* returns a vector of strings splitted by the delimiter */
		std::vector<std::wstring> splitString(const std::wstring& str, wchar_t delim = ' ');

		/* fills a container with strings of the splitted string parts, based on the delimiter */
		template <class Container>
		void splitString(const std::string& str, Container& cont, char delim = ' ') {

			std::stringstream ss(str);
			std::string token;

			while (std::getline(ss, token, delim)) {

				cont.push_back(token);

			}

		}

		/* fills a container with strings of the splitted string parts, based on the delimiter */
		template <class Container>
		void splitString(const std::wstring& str, Container& cont, wchar_t delim = ' ') {

			std::wstringstream ss(str);
			std::wstring token;

			while (std::getline(ss, token, delim)) {

				cont.push_back(token);

			}

		}

	}

}