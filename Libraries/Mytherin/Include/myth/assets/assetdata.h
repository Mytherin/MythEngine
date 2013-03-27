

#pragma once

#include <myth\io\filemanager.h>
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

			virtual std::string GetSource() = 0;
			std::string AsString() { return m_str;}
		protected:
			std::string m_str;
		};

		class Source : public AssetData
		{
		public:
			explicit Source(std::string str) : AssetData(str) {}
			
			virtual std::string GetSource()
			{
				return m_str;
			}

			operator const std::string&() const
			{
				return m_str;
			}
		};

		class FilePath : public AssetData
		{
		public:
			explicit FilePath(std::string str) : AssetData(str) {}
			
			virtual std::string GetSource()
			{
				return g_fileManager.ReadFile(m_str);
			}

			operator const std::string&() const
			{
				return m_str;
			}
		};
	}
}