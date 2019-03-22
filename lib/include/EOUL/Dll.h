#pragma once

#include <Windows.h>
#include <filesystem>

namespace EOUL {

	namespace Windows {

		class Dll {

			private:

				HMODULE library = 0;

			public:

				Dll() = default;
				Dll(const std::filesystem::path& path);
				~Dll();

				Dll(const Dll& other) = delete;

			private:

				void* loadProcAdress(const std::string& symbol) const;

			public:

				void unload();
				void load(const std::filesystem::path& path);

				template <typename T>
				inline T* get(const std::string& symbol) const;


		};

		template <typename T>
		inline T* Dll::get(const std::string& symbol) const {

			return reinterpret_cast<T*>(this->loadProcAdress(symbol));

		}

	}

}