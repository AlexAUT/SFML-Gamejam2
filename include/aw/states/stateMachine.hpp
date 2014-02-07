#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <stack>
#include <memory>
#include <atomic>

#include "state.hpp"

namespace aw
{
	//Class declaration
	class StateMachine
	{
	public:
		typedef std::unique_ptr<State> State_ptr;

	public:

		void pushState(State_ptr &state);
		void popStateNextFrame();
		State *getCurrentState();

		void processEvent(const sf::Event &event);
		void update(const sf::Time &frameTime);
		void render(sf::RenderTarget &target);

		bool isEmpty();

	private:

	private:
		std::stack<State_ptr> mStateStack;
		std::atomic<int> mShouldPopState{0}; //Loading screen is working due to multithreading = protect this var
	};
}

#endif
