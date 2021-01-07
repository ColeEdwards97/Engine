#pragma once

#include "Engine/Entity/Component.h"

namespace Engine
{

	class TagComponent : public Component<TagComponent>
	{

	public:

		TagComponent()
		{}

		TagComponent(std::string& tag)
			: m_Tag(tag)
		{}

		virtual ~TagComponent()
		{}

		std::string& GetTag() { return m_Tag; }
		void SetTag(std::string& tag) { m_Tag = tag; }

	private:
		std::string m_Tag;

	};

}