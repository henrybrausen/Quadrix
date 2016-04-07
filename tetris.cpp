#include "cApplication.h"

int main(int argc, char *argv[])
{
	int ret_val = 0;
	cApplication *app = new cApplication();
	ret_val = app->execute();
	delete app;
	return ret_val;
}


