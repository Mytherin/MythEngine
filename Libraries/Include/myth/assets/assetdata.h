

#pragma once

#include <string>

namespace myth
{
	namespace assets
	{
		class AssetData
		{
		public:
			explicit AssetData(std::string str) : m_str(str){}
			virtual ~AssetData(){}

		protected:
			std::string m_str;
		};

		class Source : public AssetData
		{
		public:
			explicit Source(std::string str) : AssetData(str) {}
			
			operator const std::string&() const{
				return m_str;
			}
		};

		class FilePath : public AssetData
		{
		public:
			explicit FilePath(std::string str) : AssetData(str) {}
			
			operator const std::string&() const{
				return m_str;
			}
		};
	}
}