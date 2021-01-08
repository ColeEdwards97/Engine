#pragma once

#include <glm/glm.hpp>

namespace Engine
{

	class Shader
	{

	public:

		virtual ~Shader() = default;

		static Ref<Shader> Create(const char* fragShaderPath, const char* vertShaderPath);
		static Ref<Shader> Create(std::string fragShaderSrc, std::string vertShaderSrc);
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		// TODO: to be abstracted away if future RenderAPIs are implemented
		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetBool(const std::string& name, bool value) = 0;

		virtual void SetVec3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetVec4(const std::string& name, const glm::vec4& value) = 0;

		virtual void SetMat3(const std::string& name, const glm::mat3& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

	};

}