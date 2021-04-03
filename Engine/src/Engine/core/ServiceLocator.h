#pragma once

namespace Engine
{
	
	class ServiceLocator
	{
	public:
		static ServiceLocator& Get() { return *s_Instance; }

	public:
		template<class T>
		void Provide(T* service) { 
			ENGINE_CORE_ASSERT(service, "Provided Service is nullptr");
			m_Service = service; 
		}

		template<class T>
		void Provide(T* service, T* nullService) {
			if (service) { 
				m_Service = service; 
				return;
			}
			ENGINE_CORE_ASSERT(nullService, "Provided Null Implementation of Service is nullptr");
			m_Service = nullService;
		}

		template<class T>
		T& Locate() const { return *m_Service; }

	private:
		static ServiceLocator* s_Instance;

	private:
		template<class T>
		static inline T* m_Service = nullptr;

	};


}