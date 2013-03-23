
#pragma once


namespace myth
{
	namespace window
	{
		struct Monitor
		{
			Monitor(){}
			Monitor(float left, float right, float top, float bottom):
				m_left(left),m_right(right),m_top(top),m_bottom(bottom)
			{
			}

			float m_left;
			float m_right;
			float m_top;
			float m_bottom;
		};
	}
}
