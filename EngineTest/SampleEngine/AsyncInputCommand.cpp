#include "stdafx.h"
#include "AsyncInputCommand.h"

CAsyncInputCommand::CAsyncInputCommand( int nKeyID, std::function< void( enKeyState eKeyState ) > fpCallback )
:	ICommand( nKeyID, fpCallback )
{

}

CAsyncInputCommand::~CAsyncInputCommand()
{

}

void CAsyncInputCommand::updateKeyState() noexcept
{
	bool bPushState = ( GetAsyncKeyState( m_nKeyID ) & 0x8000 ) ? true : false;
	if( bPushState )
		m_eKeyState = ( enKeyState::enKeyState_Free == m_eKeyState ) ? enKeyState::enKeyState_Push : enKeyState::enKeyState_Hold;
	else
		m_eKeyState = ( enKeyState::enKeyState_Hold == m_eKeyState ) ? enKeyState::enKeyState_Pull : enKeyState::enKeyState_Free;
}