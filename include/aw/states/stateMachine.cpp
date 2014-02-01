#include "stateMachine.hpp"

namespace aw
{
	/////////////////////////////////////////////////
	void StateMachine::pushState(State_ptr &state)
	{
		mStateStack.push(std::move(state));
	}
	/////////////////////////////////////////////////
	void StateMachine::popStateNextFrame()
	{
		mShouldPopState++;
	}
	/////////////////////////////////////////////////
	State *StateMachine::getCurrentState()
	{
		return &*mStateStack.top();
	}
	/////////////////////////////////////////////////
	void StateMachine::processEvent(const sf::Event &event)
	{
		//Call ProcessEvent on the top of the stack
		if (!mStateStack.empty())
			mStateStack.top()->processEvent(event);
	}
	/////////////////////////////////////////////////
	void StateMachine::update(const sf::Time &frameTime)
	{
		//Check if the top of the stack should be popped
		if (mShouldPopState > 0)
		{
			mStateStack.pop();
			mShouldPopState--;
		}
		//Call update on the top of the stack
		if (!mStateStack.empty())
			mStateStack.top()->update(frameTime);
	}
	/////////////////////////////////////////////////
	void StateMachine::render(sf::RenderTarget &target)
	{
		//Call render on the top of the stack
		if (!mStateStack.empty())
			mStateStack.top()->render(target);
	}
	/////////////////////////////////////////////////
	bool StateMachine::isEmpty()
	{
		return mStateStack.empty();
	}
}