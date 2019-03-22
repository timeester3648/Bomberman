#pragma once

#include <EOUL\Parser.h>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <filesystem>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN

namespace EOUL {

	namespace IO {

		class FileBase {

			friend std::ostream& operator<<(std::ostream& os, const FileBase& file);

			private:

				class Properties {

					friend class FileBase;

					private:

						DWORD props;

				};

			protected:

				std::string path = "", absolute_path = "";
				Properties properties;

			public:

				FileBase() = default;
				FileBase(std::string path);

				virtual ~FileBase() = default;

			public:

				bool operator==(const FileBase& other) const;
				bool operator==(FileBase& other) const;

				bool operator!=(const FileBase& other) const;
				bool operator!=(FileBase& other) const;

				FileBase& operator=(const FileBase& other);

			public:

				/* creates a new file from the given path, or recreates the existing one */
				static void createNewFile(const std::string& path);

				/* returns if the given file exists */
				static bool exists(const std::string& path);
				/* returns if the given path is a file */
				static bool isFile(const std::string& path);
				/* returns if the given path is a directory */
				static bool isDirectory(const std::string& path);
				/* returns if the given path is succesfully removed */
				static bool remove(const std::string& path);
				/* returns if the given path successfully created */
				static bool mkdirs(const std::string& path);
				/* returns if the given path is successfully moved */
				static bool move(const std::string& path, const std::string& destination);

				/* returns the file/folder name from the given path */
				static std::string getFileName(std::string path);
				/* returns the absolute version of the given path */
				static std::string absolute(const std::string& path);
				/* returns the relative version of the given path, the origin is by default the running executable */
				static std::string relative(const std::string& path, const std::string& origin = std::filesystem::current_path().u8string());
				/* returns the extension of the given path, empty string returned when given a directory */
				static std::string extension(const std::string& path);
				/* returns the parent path of the given path */
				static std::string parent(const std::string& path);
				/* returns the current working directory */
				static std::string currentPath();

				/* returns the size of the given path, it will return 0 if the file doesn't exist */
				static unsigned long long size(const std::string& path);

			public:

				/* creates a new file, or recreates the existing one */
				void createNewFile() const;
				/* renames the file */
				void rename(const std::string& name);
				
				/* returns the path that this file is created with */
				const std::string& getPath() const;
				/* returns the absolute path */
				const std::string& getAbsolutePath() const;
				/* returns the file's extension, empty string returned file is a directory */
				const std::string extension() const;
				/* returns the parent path */
				const std::string parent() const;

				/* returns the file/folder name */
				std::string getFileName() const;

				/* returns if the file path exists */
				bool exists() const;
				/* returns if this is a file */
				bool isFile() const;
				/* returns if the path is a directory */
				bool isDirectory() const;
				/* returns if the file is succesfully removed */
				bool remove() const;
				/* returns if the file path successfully created */
				bool mkdirs() const;
				/* returns if the file path is successfully moved */
				bool move(const std::string& destination) const;

				/*

					A file or directory that is an archive file or directory. 
					Applications typically use this attribute to mark files for backup or removal. 

				*/
				bool isArchive() const;
				/* 

					A file or directory that is compressed. 
					For a file, all of the data in the file is compressed. For a directory, compression is the default for newly created files and subdirectories. 

				*/
				bool isCompressed() const;
				/*

					A file or directory that is encrypted. For a file, all data streams in the file are encrypted. 
					For a directory, encryption is the default for newly created files and subdirectories. 

				*/
				bool isEncrypted() const;
				/* 
				
					The file or directory is hidden. 
					It is not included in an ordinary directory listing. 
				
				*/
				bool isHidden() const;
				/* 
				
					A file that does not have other attributes set. 
					This attribute is valid only when used alone. 
				
				*/
				bool isNormal() const;
				/* 

					A file that is read-only. 
					Applications can read the file, but cannot write to it or delete it. 
					This attribute is not honored on directories. 

				*/
				bool isReadonly() const;
				/* 
				
					A file or directory that the operating system uses a part of, or uses exclusively. 
				
				*/
				bool isSystemFile() const;
				/* 
				
					A file that is being used for temporary storage. 
					File systems avoid writing data back to mass storage if sufficient cache memory is available, because typically, an application deletes a temporary file after the handle is closed. 
					In that scenario, the system can entirely avoid writing the data. 
					Otherwise, the data is written after the handle is closed. 

				*/
				bool isTemporary() const;

				/* returns the Windows file properties represented as a DWORD */
				const DWORD& getProperies() const;

				/* returns the file size, it will return 0 if the file doesn't exist */
				unsigned long long size() const;
				
		};

		class File : public FileBase {

			friend std::ostream& operator<<(std::ostream& os, const File& file);

			public:

				File() = default;
				File(std::string path);

				virtual ~File() = default;

			public:

				/* 

					returns a vector of all files in the directory if it is a directory.
					if includeSubDirectories is set to true, the subdirectories as folders will also get added to the std::vector 

				*/
				std::vector<File> listFiles(bool recursive = false, bool includeSubDirectories = false) const;
				/* 

					returns a vector of all files in the directory if it is a directory and has the given extension.
					if includeSubDirectories is set to true, the subdirectories as folders will also get added to the std::vector 

				*/
				std::vector<File> listFiles(std::string suffix, bool recursive = false, bool includeSubDirectories = false) const;
				/* 

					returns a vector of all files in the directory if it is a directory and has one of the given extensions. 
					if includeSubDirectories is set to true, the subdirectories as folders will also get added to the std::vector 

				*/
				std::vector<File> listFiles(std::vector<std::string> suffixes, bool recursive = false, bool includeSubDirectories = false) const;

				/* writes bytes to the file */
				void write(char* bytes, unsigned long long size, bool addToFile = false) const;
				/* reads all the bytes from the file to a buffer */
				void read(char* buffer) const;
				/* reads a given amount of bytes from the file to a buffer, the offset is the byte to start reading the data */
				void read(char* buffer, unsigned long long size, unsigned long long offset = 0ull) const;
				/* reads all lines into a vector */
				std::vector<std::string> readLines() const;

		};

		class TemporaryFile : public File {

			public:

				TemporaryFile() = default;
				TemporaryFile(std::string path);

				virtual ~TemporaryFile();

		};

		class ZipFile : public FileBase {

			friend std::ostream& operator<<(std::ostream& os, const ZipFile& file);

			public:

				ZipFile() = default;
				ZipFile(std::string path);

			public:

				/* adds a file/folder to the zip file */
				void add(std::string path) const;
				/* adds a file/folder to the zip file */
				void add(File file) const;

				/* extracts all the files/folders to the given destination, the default destination is the same directory as the zip file itself */
				void extractAll(std::string destination = "") const;
				/* extracts all the files/folders to the given destination, the default destination is the same directory as the zip file itself */
				void extractAll(File destination) const;

				/* extracts a file/folder with the given name to the given destination, the default destination is the same directory as the zip file itself */
				void extract(std::string fileName, std::string destination = "") const;
				/* extracts a file/folder with the given name to the given destination, the default destination is the same directory as the zip file itself */
				void extract(std::string fileName, File destination) const;

		};

		class PropertiesFile : private File, public Parser::PropertiesParser  {

			public:

				PropertiesFile(std::string path);
				PropertiesFile(const File& file);

			public:

				/* adds a key and a value to the properties file */
				void put(std::string key, std::string value);
				/* removes a key and its value from the properties file */
				void removeKey(std::string key);

		};

		class ConfigFile : private File, public Parser::ConfigParser  {

			public:

				ConfigFile(std::string path);
				ConfigFile(const File& file);

			public:

				/* adds a key and a value to the properties file */
				void put(std::string key, std::string value);
				/* removes a key and its value from the properties file */
				void removeKey(std::string key);

		};

		class IniFile : private File, public Parser::IniParser  {

			public:

				IniFile(std::string path);
				IniFile(const File& file);

			public:

				/* adds a key, section and a value to the properties file if needed, keep section empty for no section */
				void put(std::string section, std::string key, std::string value);
				/* removes a key and its value from the properties file */
				void removeKey(std::string key);

		};

	}

}