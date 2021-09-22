
#include "astar.h"


static int arr_poses[][2] = {
	{-1, -1},{0, -1},{-1, 1},
	{-1, 0},       {1, 0},
	{-1, 1},{0, 1},{1, 1}
};

void SceneMap::initMap(char SceneData[SCENE_WIDTH][SCENE_WIDTH]) {
	for (int x = 0; x < SCENE_WIDTH; x++) {
		ScenePointList objList;
		for (int y = 0; y < SCENE_WIDTH; y++) {
			ScenePoint * obj = new ScenePoint(x, y, SceneData[x][y]);
			objList.push_back(obj);
		}
		m_sceneMapData.push_back(objList);
	}
}

static SceneNode sceneNodeCache[SCENE_WIDTH][SCENE_WIDTH];
void SceneMap::findPath(ScenePoint * startPoint, ScenePoint * endPoint, SceneNode *&nodePath) {
	nodePath = NULL;
	if (!startPoint || !endPoint){
		return;
	}

	if ( (startPoint == endPoint) || ( startPoint->m_x == endPoint->m_x && startPoint->m_y == endPoint->m_y)) {
		return ;
	}

	m_openList.clear();
	int size = SCENE_WIDTH * SCENE_WIDTH * sizeof(SceneNode);
	memset(sceneNodeCache, 0, size);

	startPoint = m_sceneMapData[startPoint->m_x][startPoint->m_y];
	endPoint = m_sceneMapData[endPoint->m_x][endPoint->m_y];
	SceneNode * node = &sceneNodeCache[startPoint->m_x][startPoint->m_y];
	node->m_curPoint = startPoint;
	node->m_pNode = NULL;
	node->m_h = getH(startPoint, endPoint);
	node->m_g = 0;
	node->m_nodeStauts = NodeStatus::OPEN;
	node->m_f = node->m_h + node->m_g;
	m_openList.push_back(node);

	while (!m_openList.empty()) {
		SceneNode *curNode = m_openList[0];
		SceneNodeList::iterator remove_it = m_openList.begin();
		for (SceneNodeList::iterator it = m_openList.begin(); it != m_openList.end(); it++) {
			SceneNode * itNode = (*it);
			if (itNode->m_f < curNode->m_f) {
				curNode = itNode;
				remove_it = it;
			}
		}
		m_openList.erase(remove_it);

		if (curNode->m_curPoint == endPoint) { // ÕÒµ½
			nodePath = &sceneNodeCache[endPoint->m_x][endPoint->m_y];
			break;
		}

		for (int i = 0; i < 8; i++) {
			int * pose = arr_poses[i];
			int tmpx = curNode->m_curPoint->m_x + pose[0];
			int tmpy = curNode->m_curPoint->m_x + pose[1];
			if (tmpx < 0 || tmpx >= SCENE_WIDTH || tmpy < 0 || tmpy >= SCENE_WIDTH) {
				continue;
			}

			ScenePoint *point = m_sceneMapData[tmpx][tmpy];
			if (point->m_pointType != PointType::SPACE) {
				continue;
			}

			int g = 14;//Ð±¶Ô½Ç
			if (pose[0] == 0 || pose[1] == 0) {
				g = 10;
			}

			SceneNode * tmpNode = &sceneNodeCache[tmpx][tmpy];
			int tmpg = curNode->m_g + g;
			if (tmpNode->m_nodeStauts == NodeStatus::OPEN) {
				if (tmpNode->m_h < curNode->m_h) {
					tmpNode->m_g = tmpg;
					tmpNode->m_pNode = curNode;
				}
				continue;
			}
			tmpNode->m_nodeStauts = NodeStatus::OPEN;
			tmpNode->m_pNode = curNode;
			tmpNode->m_curPoint = point;
			tmpNode->m_g = tmpg;
			tmpNode->m_h = getH(point, endPoint);
			tmpNode->m_f = tmpNode->m_h + tmpNode->m_g;
			m_openList.push_back(tmpNode);
		}
	}

}
