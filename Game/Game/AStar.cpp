#include "AStar.h"

AStar::AStar()
{
    directions =
    {
        // 하상우좌 이동.
        { 0, 1, 1.0f },
        { 0, -1, 1.0f },
        { 1, 0, 1.0f },
        { -1, 0, 1.0f },
        // 대각선 이동.
        { 1, 1, 1.414f },
        { 1, -1, 1.414f },
        { -1, 1, 1.414f },
        { -1, -1, 1.414f },
    };
}

AStar::~AStar()
{
    for (AStarNode* node : openList)
        SafeDelete(node);
    openList.clear();

    for (AStarNode* node : closedList)
        SafeDelete(node);
    closedList.clear();
}

vector<AStarNode*> AStar::FindPath(AStarNode* startNode, AStarNode* goalNode, const vector<vector<bool>>& grid)
{
    // 시작 지점.
    this->startNode = startNode;
    this->goalNode = goalNode;

    // 시작 위치를 열린 리스트에 추가.
    openList.emplace_back(startNode);

    // 이웃 노드 탐색(열린 리스트가 비어 있지 않으면 반복).
    while (!openList.empty())
    {
        // 현재 열린 리스트에서 비용(fCost)이 가장 낮은 노드 검색.
        // 최적화 가능(우선 순위 큐, 힙).
        AStarNode* lowestNode = openList[0];
        for (AStarNode* node : openList)
        {
            if (node->fCost < lowestNode->fCost)
                lowestNode = node;
        }

        // 비용이 가장 작은 노드를 현재 노드로 선택.
        AStarNode* currentNode = lowestNode;

        // 현재 노드가 목표 노드인지 확인.
        if (IsDestination(currentNode))
            // 목표 지점으로부터 역추적해서 경로를 생성 후 반환.
            return ConstructPath(currentNode);

        // 방문 처리를 위해 현재 노드를 열린 리스트에서 제거.
        int size = (int)openList.size();
        for (int i = 0; i < size; i++)
        {
            // 두 노드의 위치를 기반으로 같은지 확인.
            if (openList[i]->position.x == currentNode->position.x &&
                openList[i]->position.y == currentNode->position.y)
            {
                openList.erase(openList.begin() + i);
                break;
            }
        }

        // 방문 처리를 위해 닫힌 리스트에 추가.
        // 이미 추가된 노드는 제외.
        bool isNodeInList = false;
        for (AStarNode* node : closedList)
        {
            // 위치 기반으로 비교.
            if (node->position.x == currentNode->position.x &&
                node->position.y == currentNode->position.y)
            {
                isNodeInList = true;
                break;
            }
        }

        // 이미 있으면 무시.
        if (isNodeInList)
            continue;

        // 없으면 닫힌 리스트에 추가.
        closedList.emplace_back(currentNode);

        // 이웃 노드 방문(하상우좌 .. 차례로 방문).
        for (const Direction& direction : directions)
        {
            // 다음에 이동할 위치 확인.
            int newX = currentNode->position.x + direction.x;
            int newY = currentNode->position.y + direction.y;

            // 그리드를 벗어나면 무시.
            if (!IsInRange(newX, newY, grid))
                continue;

            // 이동할 노드가 이동 가능한지 확인.
            if (grid[newY][newX] == true)
                continue;

            // 이미 방문했는지 확인.
            if (HasVisited(newX, newY, currentNode->gCost + direction.cost))
                continue;

            // 방문할 노드 생성(비용 계산).
            AStarNode* neighborNode = new AStarNode(newX, newY, currentNode);
            neighborNode->gCost = currentNode->gCost + direction.cost;
            neighborNode->hCost = CalculateHeuristic(neighborNode, goalNode);
            neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

            // 열린 리스트에 추가.
            AStarNode* openListNode = nullptr;
            for (AStarNode* node : openList)
            {
                if (node->position.x == neighborNode->position.x &&
                    node->position.y == neighborNode->position.y)
                {
                    openListNode = node;
                    break;
                }
            }

            // 이웃 노드가 리스트에 없으면 바로 추가.
            // 리스트에 있다면 비용을 비교해 더 저렴하면 비용 추가.
            if (openListNode == nullptr ||
                neighborNode->gCost < openListNode->gCost ||
                neighborNode->fCost < openListNode->fCost)
            {
                openList.emplace_back(neighborNode);
            }
            else
            {
                // 리스트 추가 대상이 아니라면, 메모리 해제.
                SafeDelete(neighborNode);
            }
        }
    }

    // 탐색 실패.
    return vector<AStarNode*>();
}

vector<AStarNode*> AStar::ConstructPath(AStarNode* goalNode)
{
    // 목표 노드로부터 부모 노드를 따라 역추적하면서 경로 설정.
    std::vector<AStarNode*> path;
    AStarNode* currentNode = goalNode;
    while (currentNode != nullptr)
    {
        path.emplace_back(currentNode);
        currentNode = currentNode->parent;
    }

    // 시작 시점부터 목표 지점으로 향하도록 배열 뒤집기.
    std::reverse(path.begin(), path.end());
    return path;
}

float AStar::CalculateHeuristic(AStarNode* currentNode, AStarNode* goalNode)
{
    // 현재 노드에서 목표 노드까지의 차이 계산.
    Position diff = Position(currentNode->position.x - goalNode->position.x, 
                             currentNode->position.y - goalNode->position.y);
    return std::sqrtf(diff.x * diff.x + diff.y * diff.y);
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<bool>>& grid)
{
    if (x < 0 || x >= grid[0].size() || y < 0 || y >= grid.size())
        return false;
    return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
    // 열린/닫힌 리스트에 이미 해당 위치가 있으면 방문한 것으로 판단.
    int size = (int)openList.size();
    for (int i = 0; i < size; i++)
    {
        AStarNode* node = openList[i];
        if (node->position.x == x && node->position.y == y)
        {
            // 위치도 같고 비용이 더 크면 방문할 이유가 없음.
            if (gCost >= node->gCost)
                return true;

            // 새 노드의 비용이 작은 경우에는 기존 노드 제거.
            openList.erase(openList.begin() + i);
            SafeDelete(node);
            size--;
        }
    }

    size = (int)closedList.size();
    for (int i = 0; i < size; i++)
    {
        AStarNode* node = closedList[i];
        if (node->position.x == x && node->position.y == y)
        {
            // 위치도 같고 비용이 더 크면 방문할 이유가 없음.
            if (gCost >= node->gCost)
                return true;

            // 새 노드의 비용이 작은 경우에는 기존 노드 제거.
            closedList.erase(closedList.begin() + i);
            SafeDelete(node);
            size--;
        }
    }

    // 리스트에 없으면 방문하지 않은 것으로 판단.
    return false;
}

bool AStar::IsDestination(const AStarNode* node)
{
    return (node->position.x == goalNode->position.x &&
            node->position.y == goalNode->position.y);
}