
#ifdef _WIN32
#if _DEBUG
#include <vld.h>
#endif
#include <tchar.h>
#endif

#include "game/Application.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

int main(int argc, char* args[])
{

	__printf__("[I] Program lauch at `%s`\n", *args);

	GameS::GetInstance()->Run();

//	printf("\n>> Press any key...\n");
//	getchar();

	return 0;
}


int _tmain(int argc, char* args[])
{
	return main(argc, args);
}