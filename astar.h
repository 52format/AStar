#pragma once

#include <vector>
using namespace std;
#define SCENE_WIDTH 10


enum PointType
{
	RIVER, // 河
	SPACE, // 空地
	HILL,  // 山地
	BARRIER, // 不可走
};

enum NodeStatus {
	INIT = 0,
	OPEN = 1,
	CLOSE = 2,
};



struct ScenePoint {
public:
	ScenePoint(int x, int y, char pointType) : m_x(x), m_y(y), m_pointType(pointType) {
	}

	int m_x;
	int m_y;
	char m_pointType;
};

struct SceneNode {
public:
	SceneNode() {

	}
	int m_f;
	int m_g;
	int m_h;
	int m_nodeStauts;
	ScenePoint * m_curPoint;
	SceneNode * m_pNode; //pre
};

typedef vector<ScenePoint *> ScenePointList;
typedef vector<ScenePointList> SceneMapData;
typedef vector<SceneNode *> SceneNodeList;

class SceneMap{
public:
	void initMap(char SceneData[SCENE_WIDTH][SCENE_WIDTH]);
	int getH(ScenePoint * startPoint, ScenePoint * endPoint) {
		return (abs(endPoint->m_y - startPoint->m_y) + abs(endPoint->m_x - startPoint->m_x)) * 10;
	}
	void findPath(ScenePoint * startObj, ScenePoint * endObj, SceneNode *&nodePath);

private:
	SceneNodeList m_openList;
	SceneMapData m_sceneMapData;

};
