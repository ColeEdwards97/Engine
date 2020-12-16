#pragma once

namespace Engine
{
	class Component
	{
	public:

		virtual ~Component() {}

		virtual bool AllowsMultiple() const = 0;

#define ALLOWS_MULTIPLE(b) static bool AllowsMultipleStatic() { return b; }\
							virtual bool AllowsMultiple() const override { return AllowsMultipleStatic(); }

	};

}