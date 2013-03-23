
#include <myth\debug\assert.h>
#include <myth\debug\assertfunctions.h>
#include <myth\phys\simplex.h>

using myth::phys::Direction;
using myth::phys::Offset;
using myth::phys::Point;
using myth::phys::Simplex;

Simplex::Simplex(Point A)
{
	Create(A);
}

Simplex::Simplex(Point A, Point B)
{
	Create(A,B);
}

Simplex::Simplex(Point A, Point B, Point C)
{
	Create(A,B,C);
}

Simplex::Simplex(Point A, Point B, Point C, Point D)
{
	Create(A,B,C,D);
}

void Simplex::Create(Point A)
{
	m_elements = 1;
	m_points[0] = A;
}

void Simplex::Create(Point A, Point B)
{
	m_elements = 2;
	m_points[0] = A;
	m_points[1] = B;
}

void Simplex::Create(Point A, Point B, Point C)
{
	m_elements = 3;
	m_points[0] = A;
	m_points[1] = B;
	m_points[2] = C;
}

void Simplex::Create(Point A, Point B, Point C, Point D)
{
	m_elements = 4;	
	m_points[0] = A;
	m_points[1] = B;
	m_points[2] = C;
	m_points[3] = D;
}



Direction Simplex::Expand(const Point& A)
{
	switch(m_elements)
	{
	case 0: //no points on simplex
		return Expand0(A);
	case 1: //0-simplex
		return Expand1(m_points[0],A);
	case 2: //1-simplex
		return Expand2(m_points[0],m_points[1],A);
	case 3: //2-simplex
		return Expand3(m_points[0],m_points[1],m_points[2],A);
	};
	Assert(false,L"DEGENERATE SIMPLEX ERROR: The simplex can only contain 0,1,2 or 3 elements.");
}

Direction Simplex::Expand0(const Point& A)
{
	//the simplex has no points, add the point to the simplex
	Create(A);
	return -A; //and return the direction from the simplex to the origin (A => O)
}

Direction Simplex::Expand1(const Point& B, const Point& A)
{
	//Assert(AreInequal(m_points[0],A),L"DEGENERATE SIMPLEX ERROR: The two points on the 1-simplex (line) are equal.");

	Offset AB = B - A; //A => B
	Offset AO = - A;   //A => O

	//check if the point lies closest to the edge AB or closest to the vertex A
	if (mDot(AB,AO) > 0) 
	{
		//the point lies closest to the edge AB, the simplex is the 1-simplex (line) AB and the direction is the direction from AB to the origin
		//we can compute this direction with a double cross product, the cross product of AB x AO returns the normal of the plane containing A, B, O
		//and the cross product of that normal with the line A => B gives us the line pointing towards O
		Create(A,B);
		return mCross(mCross(AB,AO),AB);
	}
	else
	{
		return Expand0(A);
	}
}

Direction Simplex::Expand2(const Point& B, const Point& C, const Point& A)
{
	//Assert(AreNotCollinear(m_points[0],m_points[1],A),L"DEGENERATE SIMPLEX ERROR: The three points on the 2-simplex (triangle) are collinear.");

	Offset AB = B - A;                 //the edge AB
	Offset AC = C - A;                 //the edge AC
	Offset AO = - A;                   //the edge AO (A to origin)
	Normal ABC = mCross(AB,AC);         //normal of the triangle
	Normal ACN = mCross(ABC,AC);        //normal of the edge AC pointing outwards of the triangle


	if (mDot(ACN,AO) > 0) //check if the origin lies outwards of the edge A => C
	{
		//if it does, it can lie in three voronai regions (AC, AB and A)
		if (mDot(AC,AO) > 0) //first check if it lies within the voronai region of AC
		{
			Create(A,C); //if it does, create the simplex with A and C
			return mCross(mCross(AC,AO),AC);
		}
		else
		{   
			//else check if it lies on AB or on A similar to how we would test a 1-simplex (line)
			return Expand1(B,A);
		}
	}

	Normal ABN = mCross(AB,ABC);        //normal of the edge AB pointing outwards of the triangle


	if (mDot(ABN,AO) > 0) //if it lies inwards of the edge A => C, check if it lies outwards of the edge A => B
	{ //if it lies outwards of the edge A => B, it can be in the voronai regions of A and AB, check those as we would a 1-simplex
		return Expand1(B,A); 
	}
	else
	{ //otherwise if it lies inwards of AB and inwards of AC, it must lie within the triangle. Check if it lies above or below the triangle ABC.
		if (mDot(ABC,AO) > 0)
		{
			Create(A,B,C);
			return ABC;
		}
		else
		{
			Create(A,C,B);
			return -ABC;
		}
	}
}


Direction Simplex::Expand3(const Point& B, const Point& C,const Point& D,const Point& A)
{
	//Assert(AreNotCoplanar(m_points[0],m_points[1],m_points[2],A),L"DEGENERATE SIMPLEX ERROR: The four points on the 4-simplex (tetrahedron) are coplanar.");

	return Direction(0,0,0);
}