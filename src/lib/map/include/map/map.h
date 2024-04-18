#ifndef SHADOW_MAP_H
#define SHADOW_MAP_H

#include <list>
#include <map>
#include <unordered_map>

#include "define.h"
#include "singleton/singleton.h"

# ifdef SHARED_LIB
#   ifdef WIN32
#      ifdef DLLEXPORT
#        define SHADOW_API __declspec(dllexport)
#      else
#        define SHADOW_API __declspec(dllimport)
#      endif // !DLLEXPORT
#   else
#     define SHADOW_API
#   endif // !WIN32
# else
#    define SHADOW_API
# endif // !SHARED_LIB

namespace shadow {
    const uint32_t PATH_MAX_X = 1000;
    const uint32_t PATH_MAX_Y = 1000;
    const uint32_t MAP_MAX_NODES = shadow::PATH_MAX_X * shadow::PATH_MAX_Y;

    struct MapNode {
        uint32_t id;
        uint32_t x;
        uint32_t y;
        uint32_t g;
        uint32_t h;
        MapNode *parent;
        bool isBlock;
        bool isPath;
        bool isCheck;
        bool isVisited;
    };

    class SHADOW_API Map {
    public:
        Map();

        virtual ~Map();

        MapNode **getNodes();

        uint32_t getPathX() const;

        uint32_t getPathY() const;

        ErrCode createMap(uint32_t, uint32_t, uint32_t);

        ErrCode printMap();

        MapNode *getStartNode();

        MapNode *getEndNode();

        bool isStart(MapNode &);

        bool isEnd(MapNode &);

    protected:
    private:
        uint32_t pathX;
        uint32_t pathY;
        MapNode **nodes, *startNode, *endNode;
    };

    class SHADOW_API MapPath : public shadow::Singleton<MapPath> {
    public:
        explicit MapPath(Token);

        ErrCode aStar(Map *);

        MapNode *findMinF(std::map<uint32_t, std::list<MapNode *>> &);

        ErrCode getNeighbors(Map *, MapNode &, std::unordered_map<uint32_t, MapNode *> &, std::list<MapNode
        *> &);

        ErrCode addNeighbor(std::list<MapNode *> &, MapNode **, std::unordered_map<uint32_t, MapNode *> &,
                            uint32_t, uint32_t, uint32_t, uint32_t);

        uint32_t calcG(MapNode &, MapNode &);

        uint32_t calcH(MapNode &, MapNode &);

    protected:
    private:
    };
} // namespace shadow

#endif // !SHADOW_MAP_H
