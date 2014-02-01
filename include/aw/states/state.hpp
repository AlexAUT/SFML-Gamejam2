#ifndef STATE_HPP
#define STATE_HPP

#include <memory>
//Forward declaration
namespace sf
{
	class Event;
	class Time;
	class RenderTarget;
}
//Interface class (inhert from this)
namespace aw
{
	class StateMachine;

	class State
	{
	public:
		State(StateMachine &machine);
		virtual ~State();

		virtual void processEvent(const sf::Event &event) = 0;
		virtual void update(const sf::Time &frameTime) = 0;
		virtual void render(sf::RenderTarget &target) = 0;

	protected:

		void pushState(std::unique_ptr<State> &state);
		void popStateNextFrame();
		State *getCurrentState();

		StateMachine &getStateMachine();

	private:

		StateMachine &mStateMachine;
	};
}

#endif