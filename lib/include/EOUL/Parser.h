#pragma once

#include <unordered_map>
#include <string>

namespace EOUL {

	namespace IO {

		class File;

	}

	namespace Parser {

		enum class ParseResult {

			ParseUnknownError = 0,
			ParseFileStreamNotOpen = 1,
			ParseSyntaxError = 2,
			ParseKeyDuplicate = 3,
			ParseSuccessful = 4

		};

		class BaseParser {

			private:

				bool ownsFile;

			protected:

				const IO::File* file = nullptr;
				bool parsed = false;

			public:

				BaseParser(std::string path);
				BaseParser(const IO::File* file);

				virtual ~BaseParser();

			public:

				/* parses the file content */
				virtual ParseResult parse() = 0;

				/* returns if the file has been parsed */
				bool isParsed() const;

		};

		class PropertiesParser : public BaseParser {

			protected:

				std::unordered_map<std::string, std::string> values;

			public:

				PropertiesParser(std::string path);
				PropertiesParser(const IO::File* file);

			public:

				/* parses the file content */
				virtual ParseResult parse() override;

				/* returns the parsed values as a const unordered_map reference */
				const std::unordered_map<std::string, std::string>& getParsedValues() const;
				/* returns the value of the key if it exists */
				const std::string& getValue(std::string key) const;

				/* returns if the given key is parsed from the file */
				bool hasKey(std::string key) const;

		};

		class ConfigParser : public BaseParser {

			protected:

				std::unordered_map<std::string, std::string> values;

			public:

				ConfigParser(std::string path);
				ConfigParser(const IO::File* file);

			public:

				/* parses the file content */
				virtual ParseResult parse() override;

				/* returns the parsed values as a const unordered_map reference */
				const std::unordered_map<std::string, std::string>& getParsedValues() const;
				/* returns the value of the key if it exists */
				const std::string& getValue(std::string key) const;

				/* returns if the given key is parsed from the file */
				bool hasKey(std::string key) const;

		};

		class IniParser : public BaseParser {

			protected:

				std::unordered_map<std::string, std::unordered_map<std::string, std::string>> values;

			public:

				IniParser(std::string path);
				IniParser(const IO::File* file);

			public:

				/* parses the file content */
				virtual ParseResult parse() override;

				/* returns the parsed values as a const unordered_map reference */
				const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& getParsedValues() const;
				/* returns the value of the key if it exists */
				const std::string& getValue(std::string key) const;
				/* returns a whole section as a const unordered_map reference */
				const std::unordered_map<std::string, std::string>& getSection(std::string section) const;


				/* returns if the given key is parsed from the file */
				bool hasKey(std::string key, std::string section = "") const;
				/* returns if the given section is parsed from the file */
				bool hasSection(std::string section) const;

		};

	}

}

std::ostream& operator<<(std::ostream& os, const EOUL::Parser::ParseResult& result);