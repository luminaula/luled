#include "input.h"

namespace luled
{

Input::Input()
{
	m_workerThread = std::jthread([this](std::stop_token st)
	{
		while(!st.stop_requested())
		{
			std::unique_lock<std::mutex> elock(m_eventsMutex);
			m_cv.wait(elock, [this, st](){ return !m_events.empty() || st.stop_requested(); });	
			
			if (st.stop_requested()) return;

			const SDL_Event currentEvent = m_events.front();
			m_events.pop_front();
			elock.unlock();

			std::unique_lock<std::mutex> klock(m_keyMutex);

			if (currentEvent.type == SDL_KEYDOWN
				|| currentEvent.type == SDL_KEYUP)
			{
				if (currentEvent.key.repeat) continue;

				auto it = m_keys.find(currentEvent.key.keysym.sym);
				if (it != m_keys.end())
				{
					for (const auto& i : it->second)
					{
						if (currentEvent.type == SDL_KEYDOWN
							&& (!m_ignorePress || i.ignoreIgnoration))
						{
							i.pressedCb();
						}
						else if (currentEvent.type == SDL_KEYUP
							&& (!m_ignoreRelease || i.ignoreIgnoration))
						{
							i.releasedCb();
						}
					}
				}
			}
		}
	});
}

Input::~Input()
{
	m_workerThread.request_stop();
	m_cv.notify_one();
}

void Input::queueEvent(const SDL_Event& event)
{
	std::unique_lock<std::mutex> lock(m_eventsMutex);
	m_events.push_back(event);
	m_cv.notify_one();
}

void Input::addKeyCb(
	const SDL_Keycode& key,
	const KeyFuncs& funcs
)
{
	std::unique_lock<std::mutex> lock(m_keyMutex);
	m_keys[key].push_back(funcs);
}

template<typename T>
void Input::addKeyCb_multiply(
	const SDL_Keycode& key,
	std::reference_wrapper<T> value,
	const auto multiplier
)
{
	addKeyCb(key, KeyFuncs{
		.pressedCb = [value, multiplier]()
		{
			value.get() *= multiplier;
		},
		.releasedCb = [value, multiplier]()
		{
			value.get() /= multiplier;
		}
	});
}
template void Input::addKeyCb_multiply(const SDL_Keycode&, std::reference_wrapper<double>, const double);
template void Input::addKeyCb_multiply(const SDL_Keycode&, std::reference_wrapper<float>, const float);
template void Input::addKeyCb_multiply(const SDL_Keycode&, std::reference_wrapper<float>, const double);

template<typename T>
void Input::addKeyCb_add(
	const SDL_Keycode& key,
	std::reference_wrapper<T> value,
	const auto add
)
{
	addKeyCb(key, KeyFuncs{
		.pressedCb = [value, add]()
		{
			value.get() += add;
		},
		.releasedCb = [value, add]()
		{
			value.get() -= add;
		}
	});
}
template void Input::addKeyCb_add(const SDL_Keycode&, std::reference_wrapper<double>, const double);
template void Input::addKeyCb_add(const SDL_Keycode&, std::reference_wrapper<float>, const float);
template void Input::addKeyCb_add(const SDL_Keycode&, std::reference_wrapper<float>, const double);

void Input::addKeyCb_ignoreRelease(
	const SDL_Keycode& key,
	const bool ignorePress
)
{
	addKeyCb(key, KeyFuncs{
		.pressedCb =  [this, ignorePress]()
		{
            ignorePress ? m_ignorePress = true : m_ignoreRelease = true;
        },
		.releasedCb = [this]()
		{
			m_ignoreRelease = false;
			m_ignorePress = false;
		},
		.ignoreIgnoration = true
	});
}

} // namespace luled
