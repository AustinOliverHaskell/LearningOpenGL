#include "glHeader.h"
#include "Graphics.h"

using namespace std;

int main(int argc, char* argv[])
{
	Graphics * g = new Graphics("Hello!");

	g->openWindow();

	cout << "here" << endl;

	g->setupGL();

	sleep(5);

	delete g;

	return 0;
}
