#pragma once
#include "engpch.h"


template<typename coordinate_type, size_t dimensions>
class point
{
protected:

	point(std::array<coordinate_type, dimensions> coords)
		: m_Coords(coords)
	{}

	point(std::initializer_list<coordinate_type> list)
	{
		size_t n = std::min(dimensions, list.size());
		std::copy_n(list.begin(), n, m_Coords.begin());
	}

	coordinate_type get(size_t idx) const { return m_Coords[idx]; }

	double distance2(const point& pt)
	{
		double dist = 0;
		for (int i = 0; i < dimensions, i++)
		{
			double d = get(i) - pt.get(i);
			dist += d * d;
		}
		return dist;
	}

private:
	std::array<coordinate_type, dimensions> m_Coords;
};

template<typename coordinate_type, size_t dimensions>
class kd_tree
{
public:
	typedef point<coordinate_type, dimensions> point_type;

	kd_tree(int depth)
	{}

	~kd_tree() 
	{}
	
	void insert()

private:

};