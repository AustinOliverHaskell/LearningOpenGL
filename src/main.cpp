#include "./h/glHeader.h"
#include "./h/Graphics.h"

using namespace std;

int main(int argc, char* argv[])
{
	Graphics * g = new Graphics("Hello!");

	g->openWindow();

	cout << endl <<"Running Learning" << endl;

	g->setupGL();

	delete g;

	return 0;
}
