#include "MonsterWorld.h"
#include <time.h>

int main() {
	srand((unsigned int)time(NULL));
	int w = 16, h = 8;
	MonsterWorld game(w, h);

	// Add monsters
	game.add(new Zombie("Zombie1", "Z ", rand() % w, rand() % h));
	game.add(new Vampire("Vampire1", "V ", rand() % w, rand() % h));
	game.add(new KGhost("Ghost1", "G ", rand() % w, rand() % h));
	game.add(new Jiangshi("Jiangshi1", "J ", rand() % w, rand() % h, true));
	game.add(new Jiangshi("Jiangshi2", "J ", rand() % w, rand() % h, false));
	// Add players (last two)
	game.add(new Tuman("LeftPlayer", "L ", rand() % w, rand() % h));
	game.add(new Tuman("RightPlayer", "R ", rand() % w, rand() % h));

	game.play(500, 100);
	printf("------Game Over-------------------\n");
	getchar();
	return 0;
}