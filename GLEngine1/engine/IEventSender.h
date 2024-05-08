#pragma once
#include <vector>
#include <functional>

template<typename TEventListener>
class IEventSender {
public:
	virtual ~IEventSender() = default;

	void addListener(TEventListener* listener) {
		m_listeners.push_back(listener);
	}

	void removeListener(TEventListener* listener) {
		m_listeners.erase(std::find(m_listeners.begin(), m_listeners.end(), listener));
	}

protected:
	void notifyListeners(std::function<void(TEventListener*)> func) {
		for (auto* listener : m_listeners) {
			func(listener);
		}
	}

private:
	std::vector<TEventListener*> m_listeners{};

};