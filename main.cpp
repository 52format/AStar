#include <iostream>
#include "astar.h"

int main(int argc, char *argv[]) {
	char SceneData[SCENE_WIDTH][SCENE_WIDTH] =
	{
		{1,1,1,1,1,0,1,1,1,1},
		{1,1,0,0,0,1,1,1,1,1},
		{0,1,1,1,0,1,1,1,1,1},
		{1,1,2,1,2,1,1,1,1,3},
		{1,1,1,1,0,1,1,1,1,1},
		{1,0,0,2,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,3,1,1,1,1,1,1,1},
		{1,1,0,0,1,1,1,1,1,1},
		{1,0,1,1,1,1,1,1,1,1},
	};
	
	SceneMap sceneMap;
	sceneMap.initMap(SceneData);

	ScenePoint startObj(0, 0, 0);
	ScenePoint endObj(9, 9, 0);
	SceneNode *nodePath = NULL;
	sceneMap.findPath(&startObj, &endObj, nodePath);

	while (nodePath) {
		printf("x = %d  y = %d\n", nodePath->m_curPoint->m_x, nodePath->m_curPoint->m_y);
		nodePath = nodePath->m_pNode;
	}

	return 0;
}
