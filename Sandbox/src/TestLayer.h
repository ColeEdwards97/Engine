#pragma once

#include <Engine.h>
#include <imgui/imgui.h>


class TestLayer : public Engine::Layer
{
public:

	TestLayer()
		: Layer("Test Layer"), m_CubeTransform()
	{

		// VAO
		m_VertexArray.reset(Engine::VertexArray::Create());
		m_QuadVAO.reset(Engine::VertexArray::Create());

		// vertices
		float vertices[24 * 8] =
		{
			// positions          // normals		  // texture Coords
			// Front face
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,

			// Back face
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,

			// Top face
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,

			// Bottom face
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
			-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
			 
			// Right face
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,

			// Left face
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f
		}; 

		// quad vertices
		float quadVertices[4 * 6] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f
		};


		// VBO
		Engine::Ref<Engine::VertexBuffer> vertexBuffer = Engine::VertexBuffer::Create(vertices, sizeof(vertices));
		vertexBuffer->SetLayout({
			{ Engine::ShaderDataType::Float3, "a_Position" },
			{ Engine::ShaderDataType::Float3, "a_Normal" },
			{ Engine::ShaderDataType::Float2, "a_TexCoords" }
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		Engine::Ref<Engine::VertexBuffer> quadVertexBuffer = Engine::VertexBuffer::Create(quadVertices, sizeof(quadVertices));
		quadVertexBuffer->SetLayout({
			{ Engine::ShaderDataType::Float3, "a_Position" },
			{ Engine::ShaderDataType::Float2, "a_TexCoords" }
			});
		m_QuadVAO->AddVertexBuffer(quadVertexBuffer);


		// indices
		uint32_t indices[6 * 6] =
		{
			0,  1,  2,      0,  2,  3,    // front
			4,  5,  6,      4,  6,  7,    // back
			8,  9,  10,     8,  10, 11,   // top
			12, 13, 14,     12, 14, 15,   // bottom
			16, 17, 18,     16, 18, 19,   // right
			20, 21, 22,     20, 22, 23,   // left
		};

		uint32_t quadIndices[6]
		{
			0, 1, 2,
			0, 2, 3 
		};

		// VIO
		Engine::Ref<Engine::IndexBuffer> indexBuffer = Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		Engine::Ref<Engine::IndexBuffer> quadIndexBuffer = Engine::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));
		m_QuadVAO->SetIndexBuffer(quadIndexBuffer);

		// shaders
		std::string geometryVertShaderSrc = R"(
			#version 330 core
			
			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec3 a_Normal;
			layout (location = 2) in vec2 a_TexCoords;
			
			out vec3 v_FragPos;
			out vec3 v_Normal;
			out vec2 v_TexCoords;
			
			uniform mat4 u_Model;
			uniform mat4 u_View;
			uniform mat4 u_Projection;

			void main()
			{
				vec4 worldPos = u_Model * vec4(a_Position, 1.0);
				v_FragPos = worldPos.xyz; 
				v_TexCoords = a_TexCoords;
    
				mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
				v_Normal = normalMatrix * a_Normal;

				gl_Position = u_Projection * u_View * worldPos;
			}
		)";

		std::string geometryFragShaderSrc = R"(
			#version 330 core

			layout (location = 0) out vec3 GBufPosition;
			layout (location = 1) out vec3 GBufNormal;
			layout (location = 2) out vec4 GBufAlbedoSpec;

			in vec3 v_FragPos;
			in vec3 v_Normal;
			in vec2 v_TexCoords;

			uniform sampler2D u_texture_diffuse1;
			uniform sampler2D u_texture_specular1;

			void main()
			{
				GBufPosition = v_FragPos;
				GBufNormal = normalize(v_Normal);
				GBufAlbedoSpec.rgb = texture(u_texture_diffuse1, v_TexCoords).rgb;
				GBufAlbedoSpec.a = texture(u_texture_specular1, v_TexCoords).r;
			}
		)";
		

		std::string lightingVertShaderSrc = R"(
			#version 330 core
			
			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec2 a_TexCoords;

			out vec2 v_TexCoords;

			void main()
			{
				v_TexCoords = a_TexCoords;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";
		std::string lightingFragShaderSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 v_FragColor;
			in vec2 v_TexCoords;
			
			uniform sampler2D u_GBufPosition;
			uniform sampler2D u_GBufNormal;
			uniform sampler2D u_GBufAlbedoSpec;

			struct Light
			{
				vec3 Position;
				vec3 Diffuse;
				float Linear;
				float Quadratic;
				float Radius;
			};

			uniform Light u_Light;
			uniform vec3 u_ViewPos;
			
			void main()
			{             
				// retrieve data from gbuffer
				vec3 FragPos = texture(u_GBufPosition, v_TexCoords).rgb;
				vec3 Normal = texture(u_GBufNormal, v_TexCoords).rgb;
				vec3 Diffuse = texture(u_GBufAlbedoSpec, v_TexCoords).rgb;
				float Specular = texture(u_GBufAlbedoSpec, v_TexCoords).a;

				
				// then calculate lighting as usual
				vec3 lighting  = Diffuse * 0.1; // hard-coded ambient component
				vec3 viewDir  = normalize(u_ViewPos - FragPos);

				// calculate distance between light source and current fragment
				float distance = length(u_Light.Position - FragPos);
				if(distance < u_Light.Radius)
				{
					// diffuse
					vec3 lightDir = normalize(u_Light.Position - FragPos);
					vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * u_Light.Diffuse;
					
					// specular
					vec3 halfwayDir = normalize(lightDir + viewDir);  
					float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
					vec3 specular = u_Light.Diffuse * spec * Specular;
					
					// attenuation
					float attenuation = 1.0 / (1.0 + u_Light.Linear * distance + u_Light.Quadratic * distance * distance);

					// bringing it all together
					diffuse *= attenuation;
					specular *= attenuation;
					lighting += diffuse + specular;
				} 
				v_FragColor = vec4(lighting, 1.0);
			}
		)";

		m_GeometryShader = Engine::Shader::Create(geometryFragShaderSrc, geometryVertShaderSrc);
		m_LightingShader = Engine::Shader::Create(lightingFragShaderSrc, lightingVertShaderSrc);
		
		// shader setup
		m_GeometryShader->Bind();
		m_GeometryShader->SetInt("u_texture_diffuse1", 0);
		m_GeometryShader->SetInt("u_texture_specular1", 1);

		m_LightingShader->Bind();
		m_LightingShader->SetInt("u_GBufPosition", 0);
		m_LightingShader->SetInt("u_GBufNormal", 1);
		m_LightingShader->SetInt("u_GBufAlbedoSpec", 2);

		// transform setup
		m_CubeTransform.SetLocation(glm::vec3(0.0f, 0.0f, 0.0f));

		// create GBuffer
		unsigned int width = Engine::Application::Get().GetWindow().GetWidth();
		unsigned int height = Engine::Application::Get().GetWindow().GetHeight();
		Engine::FramebufferSpecification spec;
		spec.Width = width;
		spec.Height = height;
		m_GBuffer = Engine::Framebuffer::Create(spec);

		// setup lights
		Engine::Light light;
		light.Position = glm::vec3(3.14f, 5.0f, 5.0f);
		light.Diffuse = glm::vec3(247.0f, 245.0f, 195.0f);
		m_Lights.push_back(light);

		// load texture for cube
		std::string texturePathDiff = "C:/Users/edwar/Desktop/container.jpg";
		std::string texturePathSpec = "C:/Users/edwar/Desktop/container_spec.jpg";
		m_CubeTextureDiff = Engine::Texture2D::Create(texturePathDiff);
		m_CubeTextureSpec = Engine::Texture2D::Create(texturePathSpec);
		
		// camera setup
		m_Camera = new Engine::Camera(Engine::ProjectionMode::Perspective);


		auto rand_vec3 = Engine::random_t<glm::vec3>{}.next();
		auto rand_bvec3 = Engine::random_t<glm::bvec3>{}.probability();
		auto rand_mat2x3 = Engine::random_t<glm::mat2x3>{}.next_in_range(0.0f, 69.0f);


	}

	void OnUpdate(Engine::TimeStep ts) override
	{


		// TODO: move into Render System
		
		// update geometry
		//m_CubeTransform.Rotate(60.0f * ts, glm::vec3(0.0f, 1.0f, 0.0f));

		// update frametime
		m_LastFrameTime = ts;


		// --------------- GEOMETRY PASS --------------- //
		
		// bind gbuffer
		m_GBuffer->Bind();
		Engine::RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 1.0f });

		m_GeometryShader->Bind();
		m_GeometryShader->SetMat4("u_Projection", m_Camera->GetProjectionMatrix());
		m_GeometryShader->SetMat4("u_View", m_Camera->GetViewMatrix());
		m_GeometryShader->SetMat4("u_Model", m_CubeTransform.GetTransformMatrix());

		// bind vertex array and draw
		m_CubeTextureDiff->Bind(0);
		m_CubeTextureSpec->Bind(1);
		m_VertexArray->Bind();
		Engine::RenderCommand::DrawIndexed(m_VertexArray);

		// unbind gbuffer
		m_GBuffer->Unbind();


		// --------------- LIGHTING PASS --------------- //
		
		Engine::RenderCommand::Clear();

		// bind gbuffer color attachment textures
		m_GBuffer->SetActiveAttachment(0);
		m_GBuffer->SetActiveAttachment(1);
		m_GBuffer->SetActiveAttachment(2);
		
		// set lighting shader uniforms
		m_LightingShader->Bind();
		m_LightingShader->SetVec3("u_ViewPos", m_Camera->GetTransform().GetLocation());
		m_LightingShader->SetVec3("u_Light.Position", m_Lights[0].Position);
		m_LightingShader->SetVec3("u_Light.Diffuse", m_Lights[0].Diffuse);

		const float constant = 1.0f;
		const float linear = 0.7f;
		const float quadratic = 1.8f;
		m_LightingShader->SetFloat("u_Light.Linear", linear);
		m_LightingShader->SetFloat("u_Light.Quadratic", quadratic);

		const float maxBrightness = std::fmaxf(std::fmaxf(m_Lights[0].Diffuse.r, m_Lights[0].Diffuse.g), m_Lights[0].Diffuse.b);
		float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * quadratic);
		m_LightingShader->SetFloat("u_Light.Radius", radius);

		m_QuadVAO->Bind();
		Engine::RenderCommand::DrawIndexed(m_QuadVAO);

		
	}

	void OnEvent(Engine::Event& e) override
	{
		// CAMERA CONTROLLER EVENT
		// TODO: this should probably be done automatically by making each system an Observer
		//Engine::SystemManager::Get().GetSystem<Engine::ControllerSystem>()->OnEvent(e);

		Engine::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Engine::WindowResizedEvent>(ENG_BIND_FN(OnWindowResized));

	}

	bool OnWindowResized(Engine::WindowResizedEvent& e)
	{
		m_GBuffer->Resize(e.GetWidth(), e.GetHeight());
		return false;
	}
	
	void OnImGuiRender() override
	{
		ImGui::Begin("Frametime");
		ImGui::Text(std::to_string(m_LastFrameTime).append(" ms").c_str());
		ImGui::Text(std::to_string(1.0f / m_LastFrameTime).append(" FPS").c_str());
		ImGui::End();

		ImGui::Begin("Light");
		ImGui::SliderFloat3("LightPosition", m_LightPosition, -10.0f, 10.0f);
		m_Lights[0].Position = glm::vec3(m_LightPosition[0], m_LightPosition[1], m_LightPosition[2]);
		ImGui::End();

		ImGui::Begin("Framebuffer");
		ImGui::Image((ImTextureID)m_GBuffer->GetAttachment(0), ImVec2(128, 90), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::Image((ImTextureID)m_GBuffer->GetAttachment(1), ImVec2(128, 90), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::Image((ImTextureID)m_GBuffer->GetAttachment(2), ImVec2(128, 90), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();
	}


private:

	Engine::Ref<Engine::Shader> m_GeometryShader;
	Engine::Ref<Engine::Shader> m_LightingShader;

	Engine::Ref<Engine::Texture2D> m_CubeTextureDiff;
	Engine::Ref<Engine::Texture2D> m_CubeTextureSpec;

	Engine::Ref<Engine::VertexArray> m_VertexArray;
	Engine::Ref<Engine::VertexArray> m_QuadVAO;
	Engine::Ref<Engine::Framebuffer> m_GBuffer;

	Engine::Transform m_CubeTransform;
	
	float m_LightPosition[3] = { 0.0f, 0.0f, 0.0f };

	Engine::Camera* m_Camera;

	std::vector<Engine::Light> m_Lights;

	float m_LastFrameTime = 0.0f;

	/* hacking in triangle */


};