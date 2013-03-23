

#pragma once

#include <myth\debug\assert.h>

namespace myth
{
	//! Containers
	/*!
	The containers namespace contains a collection of containers used by the Mytherin libraries. 
	*/
	namespace containers
	{
		template <class T>
		//! Hashtable with Chaining that uses an <int,T> pairing system
		/*!
		The dictionary is a hashtable with chaining that only accepts integers as keys. It simply mods the keys by the size of the hashtable
		and stores them in this node. The dictionary does not check for keys of duplicate values, but will always return the first key found
		of a specific value with the default Find and [] (which is not necessarily the first key inserted when removes are involved), 
		thus inserting values with the same keys can cause strange behavior and is not recommended. 

		The hashtable is meant for storing items with a specific id, and performs best when the id is incremental [0,1,2,3,...,n] as the
		spread of the items within the hashtable will be spread with as few collisions as possible. The initial size is best chosen as a multiple
		of the amount of items you expect to put in (so with n = 100, chose the initial size as e.g. 25,50 or 100), this will give the most even spread.
		When choosing the size of the dictionary, remember that when the initial size is chosen too low, there will be a lot of collisions and searches/inserts will be slower. But if the initial size
		is chosen too high, there will be a lot of wasted memory.
		*/
		class Dictionary
		{
		public:
			//! Empty Constructor
			/*!
			When using the empty constructor, be sure to run the Create function prior to inserting elements into the dictionary.
			If the dictionary is used prior to calling Create behavior is undefined
			*/
			Dictionary(): m_size(0),m_count(0),m_values(0)
			{}

			//! Initialization Constructor
			/*!
			If this constructor is used, do not call Create as the dictionary will already have been created. You can safely use the
			dictionary after calling the initialization constructor.

			\param initialSize The amount of nodes to put into the dictionary
			*/
			Dictionary(size_t initialSize):
				m_size(initialSize), m_count(0), m_values(new DictionaryNode<T>[initialSize]) 
			{
			}
			//! Destructor
			~Dictionary()
			{
				Destroy();
			}

			//! Initializes the dictionary with a specified amount of nodes
			/*!
			Create is automatically called when the Initialization Constructor is used, however, if the Empty Constructor is used
			either Create or Reset should be called by the user prior to using the Dictionary other than calling Create and Reset.

			\param initialiSize The amount of nodes to put into the dictionary.
			*/
			void Create(size_t initialSize = DEFAULT_SIZE)
			{
				m_count = 0;
				m_size = initialSize;
				m_values = new DictionaryNode<T>(initialSize);
			}

			//! Resets the hashtable, calling Destroy() and then Create()
			/*!
			It is safe to call Reset on a dictionary that has not yet been initialized. 

			\param newSize The size of the new dictionary
			*/
			void Reset(size_t newSize = DEFAULT_SIZE)
			{
				Destroy();
				Create(newSize);
			}

			//! Destroys the hashtable
			/*!
			Destroys all nodes of the dictionary and all elements contained within them.
			*/
			void Destroy()
			{
				if (m_values)
					delete [] m_values;
			}

			//! Insert the given key-value pair into the dictionary
			/*!
			\param key The integer key of the key-value pair that is used to identify this item
			\param value The T-value that contains the data stored in this pair
			*/
			void Insert(unsigned int key, T value)
			{
				Assert(!Contains(key),L"CONTAINER ERROR: The dictionary already contains an element with the given key.");
				DictionaryNode<T>* node = &m_values[key % m_size];
				if (!node->first) //if the node is empty, the new value is both the first and the last value
				{
					node->first = new Pair<T>(key,value); 
					node->last = node->first;
				}
				else  //if the node is not empty, the new value becomes the new last value
				{
					node->last->next = new Pair<T>(key,value);
					node->last = node->last->next;
				}
				m_count++;
			}

			//! Removes the key-value pair with the given key from the dictionary
			/*!
			\param key The key that identifies the pair to be removed
			\return Returns a bool identicating whether or not the removal was successful
			*/
			bool Remove(unsigned int key)
			{
				DictionaryNode<T>* node = &m_values[key % m_size];
				Pair<T>* previous = 0;
				Pair<T>* current = node->first;

				while(current)
				{
					if (current->Key == key)
					{
						if (current == node->first) 
						{
							node->first = current->next;
						}
						else 
						{
							previous->next = current->next;
						}

						if (current == node->last) 
						{
							node->last = previous;
						}
						current->next = NULL;
						delete current;

						m_count--;
						return true;
					}
					previous = current;
					current = current->next;
				}

				return false;
			}

			T& operator [](unsigned int key) const
			{
				return Find(key);
			}

			//! Returns a reference to the T-value that belongs to the given key
			/*!
			If the key is not present in the dictionary an error is popped up in debug mode with Assert(0) and a T object at memory address NULL
			is returned. IsNull can be used on the result to test whether or not the value returned has memory address NULL.
			\param key The identifier associated with the pair that you wish to find.
			\return The value that belongs to the current identifier
			*/
			T& Find(unsigned int key) const
			{
				DictionaryNode<T>* node = &m_values[key % m_size];
				Pair<T>* current = node->first;
				while (current)
				{
					if (current->Key == key)
						return current->Value;
					current = current->next;
				}
				Assert(false,L"CONTAINER ERROR: Element not found in the dictionary.");
				return *((T*)NULL);
			}

			//! Attempts to find the item belonging to the given key. Returns whether or nor the item is present.
			/*!
			A safe way of obtaining an item you are not sure is part of the dictionary. 

			\param key The identifier associated with the value that you wish to find.
			\param pointer The function updates the pointer to point to the value if the object is present, or to NULL if it is not present.
			\return Whether or not the key wa
			*/
			bool TryFind(unsigned int key, T* pointer) const
			{
				DictionaryNode<T>* node = &m_values[key % m_size];
				Pair<T>* current = node->first;
				while (current)
				{
					if (current->Key == key)
					{
						pointer = &current->Value;
						return true;
					}
					current = current->next;
				}
				pointer = NULL;
				return false;
			}

			//! Checks whether a T value is located at memory location NULL (0)
			/*!
			This operator can be used along with the Find method or [] operator. If the element is not present in the dictionary
			they will return a T object at location NULL, thus IsNull will return true. If the element is found IsNull will return false.
			\param value The T value to test
			\return Returns whether or not the given T value is NULL
			*/
			bool IsNull(const T& value) const
			{
				return (&value == NULL);
			}

			//! Returns whether or not the given key is present in the dictionary
			/*!
			\param key The key to check
			\return Returns whether or not the key is present in the dictionary
			*/
			bool Contains(unsigned int key) const
			{
				DictionaryNode<T>* node = &m_values[key % m_size];
				Pair<T>* current = node->first;
				while (current)
				{
					if (current->Key == key)
						return true;
				}
				return false;
			}

			enum{DEFAULT_SIZE = 1000};

			//! Returns the amount of elements present in the dictionary
			int Count() const{return m_count;}
		private:
			template <class T>
			struct Pair
			{
			public:
				Pair(int key, T value):
					Key(key),Value(value), next(0)
				{
				}

				~Pair()
				{
					if (next) delete next;
				}

				int Key;
				T Value;

				Pair<T>* next;
			};

			template <class T>
			struct DictionaryNode
			{
			public:
				DictionaryNode():
					first(0), last(0)
				{
				}

				~DictionaryNode()
				{
					delete first;
				}

				Pair<T>* first;
				Pair<T>* last;
			};

			DictionaryNode<T>* m_values;

			size_t m_count;
			size_t m_size;
		};
	}
}