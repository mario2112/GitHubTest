#pragma once

#include "ICommand.h"

class CAsyncInputCommand : public ICommand
{
public:

	CAsyncInputCommand() = delete;
	CAsyncInputCommand( CAsyncInputCommand& refInputcommand ) = delete;
	CAsyncInputCommand( int nKeyID, CommandCallbackFunction fpCallback );
	virtual ~CAsyncInputCommand();

	virtual void initialize() noexcept override{}

protected:

	virtual void updateKeyState() noexcept override;
};

typedef std::shared_ptr< CAsyncInputCommand > AsyncInputCommandHandle;