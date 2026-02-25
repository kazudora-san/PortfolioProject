#ifndef		STATE_H
#define		STATE_H

#include	<vector>
#include	<string>

class GameCharacter;

class State
{
protected:
	GameCharacter*	m_OwnerObject	= {};
	std::string		m_StateName		= {};

public:
	State() = default;
	State(GameCharacter* ownerObject);

	virtual ~State();

	virtual void	Enter()				= 0;
	virtual void	Update()			= 0;
	virtual void	Exit()				= 0;

	virtual bool	IsActive()	const	= 0;

	void	SetStateOwner	(GameCharacter* ownerObject)	{ m_OwnerObject = ownerObject; }
	void	SetStateName	(const std::string& stateName)	{ m_StateName = stateName; }

	const std::string&	GetStateName() const { return m_StateName; }
};

#endif // STATE_H