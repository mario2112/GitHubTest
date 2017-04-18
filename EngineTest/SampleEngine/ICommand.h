#pragma once

class ICommand
{
public:

	enum class enKeyState : unsigned short
	{
		enKeyState_Free,
		enKeyState_Push,
		enKeyState_Hold,
		enKeyState_Pull,
	};

public:

	ICommand() = delete;
	ICommand( ICommand& refCommand ) = delete;
	ICommand( int nKeyID, std::function< void( enKeyState eKeyState ) > fpCallback )
		:	m_nKeyID( nKeyID )
		,	m_fpCallback( fpCallback  )
	{}

	virtual ~ICommand(){}

	virtual void execute()
	{
		updateKeyState();

		if( nullptr != m_fpCallback )
			m_fpCallback( m_eKeyState );
	}

	virtual void updateKeyState() abstract;

	constexpr int getKeyID() const noexcept { return m_nKeyID; }

	constexpr enKeyState getKeyState() const noexcept { return m_eKeyState; }

protected:

	std::function< void( enKeyState eKeyState ) > m_fpCallback{ nullptr };

	int m_nKeyID{ 0 };

	enKeyState m_eKeyState{ enKeyState::enKeyState_Free };
};