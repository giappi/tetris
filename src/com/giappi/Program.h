#pragma once
class Program
{
public:
	Program(){};
	virtual ~Program(){};

public:
	virtual void OnStart() = 0;
	virtual void OnPause() = 0;
	virtual void OnClose() = 0;

};

