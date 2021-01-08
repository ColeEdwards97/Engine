#pragma once

// General includes


// For use by Engine applications only
#include "Engine/Core/Application.h"
#include "Engine/Core/TimeStep.h"
#include "Engine/Core/Layer.h"
#include "Engine/Core/Log.h"

#include "Engine/Core/Input.h"
#include "Engine/Core/KeyCodes.h"
#include "Engine/Core/MouseButtonCodes.h"


#include "Engine/Entity/Entity.h"
#include "Engine/Entity/GameObject.h"
#include "Engine/Entity/Component.h"
#include "Engine/Entity/System.h"
#include "Engine/Entity/ECS.h"
#include "Engine/Entity/EntityManager.h"
#include "Engine/Entity/ComponentManager.h"
#include "Engine/Entity/SystemManager.h"

#include "Engine/Entity/Camera.h"
#include "Engine/Entity/Controller.h"
#include "Engine/Entity/CameraComponent.h"
#include "Engine/Entity/CameraController.h"
#include "Engine/Entity/ControllerComponent.h"
#include "Engine/Entity/ControllerSystem.h"

#include "Engine/Event/Event.h"
#include "Engine/Event/KeyEvent.h"
#include "Engine/Event/MouseEvent.h"
#include "Engine/Event/EntityEvent.h"
#include "Engine/Event/ApplicationEvent.h"

#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/GraphicsContext.h"
#include "Engine/Renderer/RenderCommand.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/VertexArray.h"

#include "Engine/Renderer/Texture.h"


#include "Engine/Assets/Mesh.h"
#include "Engine/Assets/Model.h"
#include "Engine/Assets/ModelLoader.h"

#include "Engine/World/Transform.h"

#include "Engine/imgui/ImGuiLayer.h"

#include "Engine/Utils/Handle.h"
#include "Engine/Utils/FamilyTypeID.h"

#include "Engine/SparseSet.h"
#include "Engine/Math/Random.h"


// ENTRY POINT ----------------------------------
#include "Engine/Core/EntryPoint.h"
// ----------------------------------------------