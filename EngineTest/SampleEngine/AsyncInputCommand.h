#pragma once

#include "ICommand.h"

class CAsyncInputCommand : public ICommand
{
public:

	CAsyncInputCommand() = delete;
	CAsyncInputCommand( CAsyncInputCommand& refInputcommand ) = delete;
	CAsyncInputCommand( int nKeyID, std::function< void( enKeyState eKeyState ) > fpCallback );
	virtual ~CAsyncInputCommand();

protected:

	virtual void updateKeyState() noexcept override final;
};