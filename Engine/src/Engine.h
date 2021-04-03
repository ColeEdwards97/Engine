#pragma once

// For use by Engine applications only
#include "Engine/Core/Core.h"

#include "Engine/Core/Application.h"
#include "Engine/Core/TimeStep.h"
#include "Engine/Core/Layer.h"
#include "Engine/Core/Log.h"

#include "Engine/Core/null.h"

#include "Engine/Core/Input/Input.h"
#include "Engine/Core/Input/InputContext.h"
#include "Engine/Core/Input/InputContextStack.h"
#include "Engine/Core/Input/InputConstants.h"
#include "Engine/Core/Input/InputConversion.h"
#include "Engine/Core/Input/Action.h"
#include "Engine/Core/Input/Range.h"

#include "Engine/Core/ServiceLocator.h"

#include "Engine/Event/Event.h"
#include "Engine/Event/KeyEvent.h"
#include "Engine/Event/MouseEvent.h"
#include "Engine/Event/ApplicationEvent.h"



#include "Engine/ECS/Entity.h"
#include "Engine/ECS/Component.h"
#include "Engine/ECS/DefaultComponents.h"
#include "Engine/ECS/Registry.h"



#include "Engine/Renderer/GraphicsContext.h"
#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/Framebuffer.h"
#include "Engine/Renderer/RenderCommand.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/VertexArray.h"

#include "Engine/Renderer/Camera.h"
#include "Engine/Renderer/Light.h"
#include "Engine/Renderer/Texture.h"


#include "Engine/Assets/Mesh.h"
#include "Engine/Assets/Model.h"
#include "Engine/Assets/ModelLoader.h"

#include "Engine/World/World.h"
#include "Engine/World/Transform.h"

#include "Engine/ImGui/ImGuiLayer.h"

#include "Engine/Utils/Identifier.h"

#include "Engine/quadtree.h"
#include "Engine/Math/Random.h"


// ENTRY POINT ----------------------------------
#include "Engine/Core/EntryPoint.h"
// ----------------------------------------------