#pragma once

#include "Engine/Core/Input/InputConstants.h"
#include "Engine/Core/Input/Action.h"
#include "Engine/Core/Input/Range.h"

namespace Engine
{
	class InputContext
	{
	public:
		InputContext();
		virtual ~InputContext() = default;

		void MapToAction(const InputConstant inputConstant, const Action& action) { m_Actions[inputConstant] = action; }
		void MapToRange(const InputAxis inputAxis, const Range& range) { m_Ranges[inputAxis] = range; }

		bool IsMappedToAction(const InputConstant inputConstant) const { return m_Actions.count(inputConstant) == 1; }
		bool IsMappedToRange(const InputAxis inputAxis) const { return m_Ranges.count(inputAxis) == 1; }

		const Action& GetMappedAction(InputConstant inputConstant) const { return m_Actions.at(inputConstant); }
		const Range& GetMappedRange(InputAxis inputAxis) const { return m_Ranges.at(inputAxis); }

	private:
		std::unordered_map<InputConstant, Action> m_Actions;
		std::unordered_map<InputAxis, Range> m_Ranges;
	};
}