#ifndef CRTCHECKMEMORY_H
#define CRTCHECKMEMORY_H

#include "stdafx.h"
#include "CppUnitTest.h"
#include "crtdbg.h"

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	struct CrtCheckMemory
	{
		_CrtMemState state1;
		_CrtMemState state2;
		_CrtMemState state3;
		CrtCheckMemory()
		{
			_CrtMemCheckpoint(&state1);
		}
		~CrtCheckMemory()
		{
			_CrtMemCheckpoint(&state2);

			if (_CrtMemDifference(&state3, &state1, &state2) != 0)
			{
				_CrtMemDumpStatistics(&state3);
				_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
				_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
				_CrtDumpMemoryLeaks();
				Assert::Fail(L"Detected memory leaks!");
			}
		}
	};
}

#endif

