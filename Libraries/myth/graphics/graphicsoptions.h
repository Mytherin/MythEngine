
#pragma once

#ifdef _dll_graphics_export_
#define declspec_graphics __declspec(dllexport)
#else
#define declspec_graphics __declspec(dllimport)
#endif


namespace myth
{
	namespace graphics
	{
		struct declspec_graphics GraphicsOptions
		{
		public:
			GraphicsOptions() : m_initialized(false) {}
			~GraphicsOptions(){}

			void Initialize()
			{
				
			}

			bool IsInitialized()
			{
				return m_initialized;
			}

			int m_buffers;
		private:
			bool m_initialized;
		};
	}
}