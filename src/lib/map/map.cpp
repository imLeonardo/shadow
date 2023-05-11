#include <cstdlib>
#include <random>
#include <thread>

#include "map/map.h"

namespace shadow {
/************************************************************************/
/* map                                                               */
/************************************************************************/
    Map::Map() : nodes(nullptr), pathX(0), pathY(0), startNode(nullptr), endNode(nullptr) {

    }

    Map::~Map() {
        if(this->nodes != nullptr) {
            for(uint32_t i = 0; i < this->pathX; i++) {
                free(this->nodes[i]);
            }
            free(this->nodes);
            this->nodes = nullptr;
        }
    }

    MapNode **Map::getNodes() {
        return this->nodes;
    }

    uint32_t Map::getPathX() const {
        return this->pathX;
    }

    uint32_t Map::getPathY() const {
        return this->pathY;
    }

    ErrCode Map::createMap(uint32_t x = shadow::PATH_MAX_X, uint32_t y = shadow::PATH_MAX_Y, uint32_t obstructNum = 0) {
        if(x > shadow::PATH_MAX_X || y > shadow::PATH_MAX_Y || obstructNum > (x * y)) {
            return ErrCode::INVALID_PARAM;
        }

        this->pathX = x;
        this->pathY = y;

        this->nodes = (MapNode **) malloc(sizeof(MapNode *) * pathX);
        if(this->nodes) {
            unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
            std::mt19937 rand_generator(seed);
            std::uniform_int_distribution<int> dist(0, 100);

            for(uint32_t i = 0; i < this->pathX; i++) {
                this->nodes[i] = (MapNode *) malloc(sizeof(MapNode) * pathY);
                if(this->nodes[i]) {
                    uint32_t x_pre = i * shadow::PATH_MAX_X;
                    for(uint32_t j = 0; j < this->pathY; j++) {
                        this->nodes[i][j].id = x_pre + j;
                        this->nodes[i][j].x = i;
                        this->nodes[i][j].y = j;
                        this->nodes[i][j].g = 0;
                        this->nodes[i][j].h = 0;
                        this->nodes[i][j].parent = nullptr;
                        this->nodes[i][j].isPath = false;
                        this->nodes[i][j].isCheck = false;
                        this->nodes[i][j].isVisited = false;

                        if(dist(rand_generator) >= 70) {
                            this->nodes[i][j].isBlock = true;
                        } else {
                            this->nodes[i][j].isBlock = false;
                            this->nodes[i][j].isPath = false;

                            if(!this->startNode)
                                this->startNode = &(this->nodes[i][j]);
                            this->endNode = &(this->nodes[i][j]);
                        }
                    }
                } else {
                    return ErrCode::BAD_ALLOC;
                }
            }
        } else {
            return ErrCode::BAD_ALLOC;
        }

        return ErrCode::SUCCESS;
    }

    ErrCode Map::printMap() {
        int flag = 0;
        std::string mapBuffer;
        for(uint32_t y = 0; y < this->getPathY(); y++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            mapBuffer = "";
            for(uint32_t x = 0; x < this->getPathX(); x++) {
                if(this->nodes[x][y].isBlock) {
                    if(flag != 1) {
                        flag = 1;
                        mapBuffer += "\033[0m";
                    }
                    mapBuffer += "1";
                } else {
                    if(this->isStart(nodes[x][y])) {
                        if(flag != 2) {
                            flag = 2;
                            mapBuffer += "\033[0;44m";
                        }
                        mapBuffer += "#";
                    } else if(this->isEnd(nodes[x][y])) {
                        if(flag != 3) {
                            flag = 3;
                            mapBuffer += "\033[0;41m";
                        }
                        mapBuffer += "#";
                    } else if(this->nodes[x][y].isPath) {
                        if(flag != 4) {
                            flag = 4;
                            mapBuffer += "\033[0;42m";
                        }
                        mapBuffer += "-";
                    } else if(this->nodes[x][y].isVisited) {
                        if(flag != 5) {
                            flag = 5;
                            mapBuffer += "\033[0;43m";
                        }
                        mapBuffer += "^";
                    } else {
                        if(flag != 6) {
                            flag = 6;
                            //map_buffer += "\033[0;47m";
                            mapBuffer += "\033[0m";
                        }
                        mapBuffer += "*";
                    }
                }
            }
            mapBuffer += "\033[0m\n";
            printf("%s", mapBuffer.c_str());
        }

        return ErrCode::SUCCESS;
    }

    MapNode *Map::getStartNode() {
        return this->startNode;
    }

    MapNode *Map::getEndNode() {
        return this->endNode;
    }

    bool Map::isStart(MapNode &node) {
        return this->startNode->id == node.id;
    }

    bool Map::isEnd(MapNode &node) {
        return this->endNode->id == node.id;
    }

/************************************************************************/
/* path                                                                 */
/************************************************************************/
    MapPath::MapPath(Token) {}

    ErrCode MapPath::aStar(Map *mapObj) {
        if(!mapObj)
            return ErrCode::INVALID_PARAM;

        uint32_t openlistNum = 0;
        std::map<uint32_t, std::list<MapNode *>> openlist;
        std::unordered_map<uint32_t, MapNode *> closelist;

        openlist.insert(std::make_pair(0, std::list<MapNode *>()));
        openlist[0].push_back(mapObj->getStartNode());
        openlistNum += 1;

        do {
            MapNode *node = this->findMinF(openlist);
            closelist[node->id] = node;
            openlistNum -= 1;

            if(mapObj->isEnd(*node)) {
                node = node->parent;
                while(node && node->parent) {
                    node->isPath = true;
                    node = node->parent;
                }
                return ErrCode::SUCCESS;
            } else {
                std::list<MapNode *> neighbors;
                this->getNeighbors(mapObj, *node, closelist, neighbors);
                for(auto neighbor: neighbors) {
                    neighbor->isVisited = true;
                    if(!neighbor->isCheck) {
                        neighbor->g = node->g + this->calcG(*node, *neighbor);
                        neighbor->h = this->calcH(*neighbor, *mapObj->getEndNode());
                        neighbor->parent = node;
                        neighbor->isCheck = true;
                        uint32_t f = neighbor->g + neighbor->h;
                        if(openlist.find(f) == openlist.end()) {
                            openlist.insert(std::make_pair(f, std::list<MapNode *>()));
                        }
                        openlist[f].push_back(neighbor);
                        openlistNum += 1;
                    } else if(closelist.find(neighbor->id) == closelist.end()) {
                        uint32_t g = node->g + this->calcG(*node, *neighbor);
                        if(g < neighbor->g) {
                            neighbor->g = g;
                            neighbor->h = this->calcH(*neighbor, *mapObj->getEndNode());
                            neighbor->parent = node;
                        }
                    }
                }
            }
        } while(openlistNum > 0);

        return ErrCode::FAIL;
    }

    MapNode *MapPath::findMinF(std::map<uint32_t, std::list<MapNode *>> &openlist) {
        auto it_min = openlist.begin();

        MapNode *map_node = it_min->second.front();

        it_min->second.pop_front();
        if(it_min->second.empty())
            openlist.erase(it_min->first);

        return map_node;
    }

    ErrCode
    MapPath::getNeighbors(Map *mapObj, MapNode &oriNode, std::unordered_map<uint32_t, MapNode *> &closelist,
                          std::list<MapNode *> &neighbors) {
        MapNode **mapNodes = mapObj->getNodes();
        uint32_t pathX = mapObj->getPathX();
        uint32_t pathY = mapObj->getPathY();
        // t
        uint32_t x = oriNode.x;
        uint32_t y = oriNode.y + 1;
        this->addNeighbor(neighbors, mapNodes, closelist, x, pathX, y, pathY);
        // l
        x = oriNode.x + 1;
        y = oriNode.y;
        this->addNeighbor(neighbors, mapNodes, closelist, x, pathX, y, pathY);
        // b
        x = oriNode.x;
        y = oriNode.y - 1;
        this->addNeighbor(neighbors, mapNodes, closelist, x, pathX, y, pathY);
        // r
        x = oriNode.x - 1;
        y = oriNode.y;
        this->addNeighbor(neighbors, mapNodes, closelist, x, pathX, y, pathY);
        // lt
        x = oriNode.x - 1;
        y = oriNode.y + 1;
        this->addNeighbor(neighbors, mapNodes, closelist, x, pathX, y, pathY);
        // rt
        x = oriNode.x + 1;
        y = oriNode.y + 1;
        this->addNeighbor(neighbors, mapNodes, closelist, x, pathX, y, pathY);
        // rb
        x = oriNode.x + 1;
        y = oriNode.y - 1;
        this->addNeighbor(neighbors, mapNodes, closelist, x, pathX, y, pathY);
        // lb
        x = oriNode.x - 1;
        y = oriNode.y - 1;
        this->addNeighbor(neighbors, mapNodes, closelist, x, pathX, y, pathY);

        return ErrCode::SUCCESS;
    }

    ErrCode MapPath::addNeighbor(std::list<MapNode *> &neighbors, MapNode **mapNodes,
                                 std::unordered_map<uint32_t, MapNode *> &closelist, uint32_t x, uint32_t pathX,
                                 uint32_t y, uint32_t pathY) {
        if((x >= 0 && x < pathX) && (y >= 0 && y < pathY)) {
            MapNode *mapNode = &mapNodes[x][y];
            if(!mapNode->isBlock && (closelist.find(mapNode->id) == closelist.end()))
                neighbors.push_back(mapNode);
        }
        return ErrCode::SUCCESS;
    }

    uint32_t MapPath::calcG(MapNode &mapNode1, MapNode &mapNode2) {
        uint32_t dx = mapNode1.x > mapNode2.x ? mapNode1.x - mapNode2.x : mapNode2.x - mapNode1.x;
        uint32_t dy = mapNode1.y > mapNode2.y ? mapNode1.y - mapNode2.y : mapNode2.y - mapNode1.y;
        return dx > dy ? dy * 14 + (dx - dy) * 10 : dx * 14 + (dy - dx) * 10;
    }

    uint32_t MapPath::calcH(MapNode &mapNode1, MapNode &mapNode2) {
        //return 0;
        uint32_t dx = mapNode1.x > mapNode2.x ? mapNode1.x - mapNode2.x : mapNode2.x - mapNode1.x;
        uint32_t dy = mapNode1.y > mapNode2.y ? mapNode1.y - mapNode2.y : mapNode2.y - mapNode1.y;
        return dx > dy ? dx * 14 : dy * 14;
    }
} // namespace shadow
