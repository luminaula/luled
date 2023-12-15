#pragma once

#include <SDL2/SDL.h>

#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <unordered_map>

namespace luled
{

class Input
{
public:
	Input();
	~Input();

	void queueEvent(const SDL_Event& event);

	struct KeyFuncs
	{
		const std::function<void()> pressedCb;
		const std::function<void()> releasedCb = []() {};
		const bool ignoreIgnoration = false;
	};

	void addKeyCb(
		const SDL_Keycode& key,
		const KeyFuncs& funcs
	);

	template<typename T>
	void addKeyCb_multiply(
		const SDL_Keycode& key,
		std::reference_wrapper<T> value,
		const auto multiplier
	);

	template<typename T>
	void addKeyCb_add(
		const SDL_Keycode& key,
		std::reference_wrapper<T> value,
		const auto add
	);

	void addKeyCb_ignoreRelease(
		const SDL_Keycode& key,
		const bool ignorePress = false
	);

private:

	std::unordered_map<SDL_Keycode, std::vector<KeyFuncs>> m_keys;
	std::mutex m_keyMutex;

	std::deque<SDL_Event> m_events;
	std::mutex m_eventsMutex;

	std::jthread m_workerThread;
	std::condition_variable m_cv;

	bool m_ignoreRelease = false;
	bool m_ignorePress = false;
};

} // namespace luled
