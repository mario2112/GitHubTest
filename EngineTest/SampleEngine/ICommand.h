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

	using CommandCallbackFunction = std::function< void( enKeyState eKeyState ) >;

public:

	ICommand() = delete;
	ICommand( ICommand& refCommand ) = delete;
	ICommand( int nKeyID, CommandCallbackFunction fpCallback )
		:	m_nKeyID( nKeyID )
		,	m_fpCallback( fpCallback  )
	{}

	virtual ~ICommand(){}

	virtual void initialize() abstract;
	virtual void execute()
	{
		updateKeyState();

		if( nullptr != m_fpCallback )
			m_fpCallback( m_eKeyState );
	}

	constexpr int getKeyID() const noexcept { return m_nKeyID; }
	constexpr enKeyState getKeyState() const noexcept { return m_eKeyState; }

protected:

	virtual void updateKeyState() abstract;

protected:

	CommandCallbackFunction m_fpCallback{ nullptr };

	int m_nKeyID{ 0 };

	enKeyState m_eKeyState{ enKeyState::enKeyState_Free };
};