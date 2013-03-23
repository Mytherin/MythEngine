
#pragma once

namespace myth
{
	namespace containers
	{
		/*class Leaf
		{
		public:
			Leaf(int x, int y, int z, int width):
				x(x),y(y),z(z),width(width){}

			int x, y, z;
			int width;
		};


		class Node : public Leaf
		{
			Node(int x, int y, int z, int width):
				Leaf(x,y,z,width){}

		private:
			Leaf children[8];
		};*/

		template <class T>
		class Octree
		{
			Octree();
			~Octree();

			void Insert(T &object);
			void Remove(T &object);


		};
	}
}