

#pragma once

#include <myth\debug\assert.h>
#include <myth\input\inputevent.h>

namespace myth
{
	namespace input
	{
		class InputNode
		{
		public:
			InputNode(InputEvent event) : m_event(event),m_next(0){}
			~InputNode(){if (m_next) delete m_next;}

			InputEvent m_event;
			InputNode* m_next;
		};

		//! The input stream handles like a FIFO queue for input events, it stores all input events and allows you to pop them in the order that they occurred in
		class InputStream
		{
		public: 
			InputStream(){Reset();}
			~InputStream(){Destroy();}

			void Push(InputEvent inputEvent)
			{
				InputNode* node = new InputNode(inputEvent);

				if (m_head)
				{
					m_tail->m_next = node;
					m_tail = node;
				}
				else
				{
					m_head = node;
					m_tail = node;
				}
			}

			InputEvent Pop()
			{
				if (!m_head) 
				{
					Assert(0,"INPUT STREAM ERROR: Attempting to pop a value from an empty InputStream");
					return InputEvent(0,0,0);
				}

				InputNode* node = m_head;
				InputEvent event = InputEvent(m_head->m_event);

				m_head = m_head->m_next;
				node->m_next = 0;
				delete node;

				return event;
			}

			InputEvent Peek() const
			{
				if (!m_head) 
				{
					Assert(0,"INPUT STREAM ERROR: Attempting to peek at value from an empty InputStream");
					return InputEvent(0,0,0);
				}

				return m_head->m_event;
			}

			bool Empty() const
			{
				return m_head == 0;
			}

			void Destroy(){if (m_head) delete m_head; }
			void Reset(){m_head = 0; m_tail = 0;}
		protected:
			InputNode* m_head;
			InputNode* m_tail;
		};
	}
}