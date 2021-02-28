#pragma once

#include "engpch.h"

namespace Engine
{

	// quadtree coordinates
	template<typename T>
	struct qt_point
	{
		T _x; T _y;
	};

	// quadtree region
	template<typename T>
	class qt_AABB
	{
	public:
		qt_point<T> _center;
		T _half_dim;

		qt_AABB(qt_point<T> center, T halfDimension) : _center(center), _half_dim(halfDimension) {}

		bool contains_point(qt_point<T> other) { 
			return (other._x >= _center._x - _half_dim && other._x < _center._x + _half_dim) &&
				   (other._y >= _center._y - _half_dim && other._y < _center._y + _half_dim);
		}
		bool intersects_AABB(qt_AABB<T> other) {
			if (std::abs(_center._x - other._center._x) > (_half_dim + other._half_dim)) return false;
			if (std::abs(_center._y - other._center._y) > (_half_dim + other._half_dim)) return false;
			return true;
		}

	};

	// quadtree
	template<typename T>
	class quadtree
	{
		static_assert(std::is_arithmetic<T>::value, "type must be arithmetic");
		static const int QT_NODE_CAPACITY = 4;

	public:
		qt_AABB<T> _boundary;
		std::vector<qt_point<T>> _points;

		quadtree* _nw = nullptr;
		quadtree* _ne = nullptr;
		quadtree* _sw = nullptr;
		quadtree* _se = nullptr;

		quadtree(qt_AABB<T> boundary) : _boundary(boundary) {}

		bool insert(qt_point<T> point) 
		{

			// Ignore objects that do not belong in this quad tree
			if (!_boundary.contains_point(point)) return false;

			// There is space in this quadtree and it doesn't have subdivisions
			if (_points.size() < QT_NODE_CAPACITY && _nw == nullptr)
			{
				_points.push_back(point);
				return true;
			}

			// Subdivide  and add the point to whichever node will accept it
			if (_nw == nullptr)
			{
				subdivide();
			}
			
			if (_nw->insert(point)) return true;
			if (_ne->insert(point)) return true;
			if (_sw->insert(point)) return true;
			if (_se->insert(point)) return true;

			// Otherwise, the point cannot be inserted for some unknown reason (this should never happen)
			return false;
		}

		void subdivide() 
		{
			T new_half_dim = _boundary._half_dim / 2;
			
			qt_point<T> nw_center{ _boundary._center._x - new_half_dim, _boundary._center._y + new_half_dim };
			qt_point<T> ne_center{ _boundary._center._x + new_half_dim, _boundary._center._y + new_half_dim };
			qt_point<T> sw_center{ _boundary._center._x - new_half_dim, _boundary._center._y - new_half_dim };
			qt_point<T> se_center{ _boundary._center._x + new_half_dim, _boundary._center._y - new_half_dim };
			
			_nw = new quadtree<T>(qt_AABB<T>{nw_center, new_half_dim});
			_ne = new quadtree<T>(qt_AABB<T>{ne_center, new_half_dim});
			_sw = new quadtree<T>(qt_AABB<T>{sw_center, new_half_dim});
			_se = new quadtree<T>(qt_AABB<T>{se_center, new_half_dim});

			// sort our points into the correct leaf
			for (auto point : _points)
			{
				if (_nw->insert(point)) continue;
				if (_ne->insert(point)) continue;
				if (_sw->insert(point)) continue;
				if (_se->insert(point)) continue;
			}
			_points.clear();

		}

	};


}