#include "state.hpp"

#include "stateMachine.hpp"

namespace aw
{
	/////////////////////////////////////////////////
	State::State(StateMachine &stateMachine) :
		mStateMachine(stateMachine)
	{}
	/////////////////////////////////////////////////
	State::~State()
	{}
	/////////////////////////////////////////////////
	void State::pushState(std::unique_ptr<State> &state)
	{
		mStateMachine.pushState(state);
	}
	/////////////////////////////////////////////////
	void State::popStateNextFrame()
	{
		mStateMachine.popStateNextFrame();
	}
	/////////////////////////////////////////////////
	State *State::getCurrentState()
	{
		return mStateMachine.getCurrentState();
	}
	/////////////////////////////////////////////////
	StateMachine &State::getStateMachine()
	{
		return mStateMachine;
	}
}