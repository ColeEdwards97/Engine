#pragma once

namespace Engine
{
	class Action
	{
	public:
		virtual ~Action() = default;
		virtual void Execute(void) = 0;
		virtual void Undo() {}
	};
}