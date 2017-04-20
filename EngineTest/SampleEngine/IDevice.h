#pragma once

class IDevice
{
public:
	IDevice(){}
	~IDevice(){}

	virtual bool initialize() abstract;
	virtual bool finalize() abstract;
};
