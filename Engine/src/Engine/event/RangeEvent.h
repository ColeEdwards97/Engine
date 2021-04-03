#pragma once
#include "Engine/Event/Event.h"
#include "Engine/Core/Input/Range.h"

namespace Engine
{
	class RangeEvent : public Event
	{
	public:
		Range GetRange() const { return m_Range; }

	protected:
		RangeEvent(const Range range)
			: m_Range(range)
		{}
		
	private:
		Range m_Range;
	};


	class RangeChangedEvent : public RangeEvent
	{
	public:
		RangeChangedEvent(const Range range, double value)
			: RangeEvent(range), m_Value(value)
		{}

		double GetValue() const { return m_Value; }

	private:
		double m_Value;
	};
}