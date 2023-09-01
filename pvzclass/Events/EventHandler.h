#pragma once
#include "../PVZ.h"
#include "BaseEvent.h"
#include <vector>
#include <iostream>

class EventHandler
{
private:
	void failLog(int line, const char* message);
	void getContext();
	void setContext();
	void continueDebug(int line);
	void waitDebugInfinity(int line);
	HANDLE getThread(int line);
	void closeThread(HANDLE hThread, int line);

public:
	DEBUG_EVENT debugEvent;
	CONTEXT context;

	// ��ʼ����PVZ���̣�����һС�ο���
	void start();

	// �ȴ�����ms��ʱ�䣬�����Ƿ����ϵͳ�ж�
	// ms����Ϊ1��������-1�������޵ȴ�
	// �������ֵΪtrue����Ҫ����handle()��resume()
	bool run(int ms);

	// ��PVZ����ִ��һ���������Ҫ�����������
	void singleStep();

	// �ָ�PVZ�����У���Ҫ��handle()�����
	void resume();
	
	// ֹͣ����PVZ����
	void stop();
};

void EventHandler::failLog(int line, const char* message)
{
	std::cout << "[ERROR] line " << line << ": " << message << "\n";
	system("pause");
	exit(-1);
}

void EventHandler::getContext()
{
	context.ContextFlags = CONTEXT_ALL;
	HANDLE hThread = getThread(__LINE__);
	if (!GetThreadContext(hThread, &context))
	{
		failLog(__LINE__, "GetThreadContext failed!");
	}
	closeThread(hThread, __LINE__);
}

void EventHandler::setContext()
{
	HANDLE hThread = getThread(__LINE__);
	if (!SetThreadContext(hThread, &context))
	{
		failLog(__LINE__, "SetThreadContext failed!");
	}
	closeThread(hThread, __LINE__);
}

void EventHandler::continueDebug(int line)
{
	if (!ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE))
	{
		failLog(__LINE__, "ContinueDebugEvent failed!");
	}
}

void EventHandler::waitDebugInfinity(int line)
{
	if (!WaitForDebugEvent(&debugEvent, -1))
	{
		failLog(__LINE__, "WaitForDebugEvent failed!");
	}
}

HANDLE EventHandler::getThread(int line)
{
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, true, debugEvent.dwThreadId);
	if (hThread == 0)
	{
		failLog(__LINE__, "hThread is 0!");
	}
	return hThread;
}

void EventHandler::closeThread(HANDLE hThread, int line)
{
	if (!CloseHandle(hThread))
	{
		failLog(__LINE__, "CloseHandle failed!");
	}
}

void EventHandler::start()
{
	if (!DebugActiveProcess(PVZ::Memory::processId))
	{
		failLog(__LINE__, "DebugActiveProcess failed!");
	}
	waitDebugInfinity(__LINE__);
	continueDebug(__LINE__);
}

bool EventHandler::run(int ms)
{
	if (!WaitForDebugEvent(&debugEvent, ms))
	{
		return false;
	}
	if (debugEvent.dwDebugEventCode != EXCEPTION_DEBUG_EVENT)
	{
		continueDebug(__LINE__);
		return false;
	}
	getContext();
	context.Eip--;
	return true;
}

void EventHandler::singleStep()
{
	context.EFlags |= 0x100;
	setContext();
	continueDebug(__LINE__);
	waitDebugInfinity(__LINE__);
}

void EventHandler::resume()
{
	continueDebug(__LINE__);
}

void EventHandler::stop()
{
	if (!DebugActiveProcessStop(PVZ::Memory::processId))
	{
		failLog(__LINE__, "DebugActiveProcessStop failed!");
	}
}