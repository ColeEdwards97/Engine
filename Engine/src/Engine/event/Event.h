#pragma once

#include "engpch.h"

namespace Engine 
{

	// BASE EVENT CLASS
	class Event
	{
	public:
		virtual ~Event() = default;

		bool handled = false;
		bool cancelled = false;
		
		template<typename E>
		bool IsEventType() {
			return (dynamic_cast<E*>(this) != nullptr);
		}

	};
	

	// EVENT DISPATCHER
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e)
			: m_event(e)
		{}

		template<typename E, typename F>
		bool Dispatch(const F& func)
		{
			if (std::type_index(typeid(E)) == std::type_index(typeid(m_event)))
			{
				m_event.handled |= func(static_cast<E&>(m_event));
				return true;
			}
			return false;
		}

	private:
		Event& m_event;

	};


	// OBSERVER INTERFACE
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnEvent(Event& e) = 0;

	};


	// EVENT CALLBACK
	template<typename T>
	struct event_callback {
		using type = std::function<bool(T&)>;
	};

	template<typename T>
	using event_callback_t = typename event_callback<T>::type;


	// EVENT WRAPPER
	struct event_wrapper {
		virtual bool call(Event& e) = 0;
	};

	template<typename T>
	struct event_wrapper_impl : event_wrapper 
	{
		event_wrapper_impl(event_callback_t<T> f) : callback(f) {}
		
		event_callback_t<T> callback;
		
		virtual bool call(Event& e) override {
			return callback(static_cast<T&>(e));
		}
	};


	// EVENT DELEGATE
	struct EventDelegate {
		Observer* observer;
		std::unique_ptr<event_wrapper> callback;
	};


	// INVALID TYPE_INDEX
	inline static const std::type_index INVALID_INDEX = std::type_index(typeid(nullptr));


	// SUBJECT
	class Subject
	{
	public:
		virtual ~Subject() = default;

		// IS REGISTERED
		bool IsRegistered(Observer* observer) {
			equal_range_t registered_delegates = m_Delegates.equal_range(INVALID_INDEX);
			for (auto it = registered_delegates.first; it != registered_delegates.second; ++it) {
				if ((*it).second.observer == observer) return true;
			}
			return false;
		}

		template<typename T>
		bool IsRegistered(Observer* observer) {
			equal_range_t registered_delegates = m_Delegates.equal_range(std::type_index(typeid(T)));
			for (auto it = registered_delegates.first; it != registered_delegates.second; ++it) {
				if ((*it).second.observer == observer) return true;
			}
			return false;
		}


		// REGISTER
		void RegisterObserver(Observer* observer) {
			if (IsRegistered(observer)) return;
			EventDelegate delegate{ observer, nullptr };
			m_Delegates.insert(
				std::make_pair(
					INVALID_INDEX, std::move(delegate)
			));
		}

		template<typename T>
		void RegisterObserver(Observer* observer, event_callback_t<T> callback) {
			if (IsRegistered<T>(observer)) return;
			std::unique_ptr<event_wrapper> wrapper = std::make_unique<event_wrapper_impl<T>>(callback);
			EventDelegate delegate{ observer, std::move(wrapper) };
			m_Delegates.insert(
				std::move(
				std::make_pair(
				std::type_index(typeid(T)), std::move(delegate)
			)));
		}
		

		// UNREGISTER
		void UnregisterObserver(Observer* observer) {
			equal_range_t registered_delegates = m_Delegates.equal_range(INVALID_INDEX);
			for (auto it = registered_delegates.first; it != registered_delegates.second; ++it) {
				// unregister general interest
				if ((*it).second.observer == observer) {
					m_Delegates.erase(it);
					break;
				}
			}
		}

		template<typename T>
		void UnregisterObserver(Observer* observer) {
			equal_range_t registered_delegates = m_Delegates.equal_range(std::type_index(typeid(T)));
			for (auto it = registered_delegates.first; it != registered_delegates.second; ++it) {
				// unregister if observer matches
				if ((*it).second.observer == observer) {
					m_Delegates.erase(it);
					break;
				}
			}
		}


		// NOTIFY
		template<typename T>
		void Notify(T& e) {
			this->Notify(e, std::type_index(typeid(T)));	// specific interest observers
			this->Notify(e, INVALID_INDEX);		// general interest observers
		}

	private:

		template<typename T>
		void Notify(T& e, std::type_index index) {
			equal_range_t registered_delegates = m_Delegates.equal_range(index);
			for (auto it = registered_delegates.first; it != registered_delegates.second; ++it) {

				if ((*it).second.callback) {
					e.handled |= (*it).second.callback->call(e);
				}
				else {
					(*it).second.observer->OnEvent(e);
				}

			}
		}

		using delegate_map = std::multimap<std::type_index, EventDelegate>;
		using mmap_iterator = delegate_map::iterator;
		using equal_range_t = std::pair<mmap_iterator, mmap_iterator>;

	private:
		delegate_map m_Delegates;

	};

}
