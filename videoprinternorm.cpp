#include "videoprinternorm.h"

void videoprinternorm(int y, int x, const char *c)
{
	#ifdef INITNCURSESNOW
	ncursesprint(y, x, c);
	#endif

	#ifdef INITLIBTCODNOW
	libtcodprint(y, x, c);
	#endif
}
