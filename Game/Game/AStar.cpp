#include "AStar.h"

AStar::AStar()
{
    directions =
    {
        // �ϻ���� �̵�.
        { 0, 1, 1.0f },
        { 0, -1, 1.0f },
        { 1, 0, 1.0f },
        { -1, 0, 1.0f },
        // �밢�� �̵�.
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
    // ���� ����.
    this->startNode = startNode;
    this->goalNode = goalNode;

    // ���� ��ġ�� ���� ����Ʈ�� �߰�.
    openList.emplace_back(startNode);

    // �̿� ��� Ž��(���� ����Ʈ�� ��� ���� ������ �ݺ�).
    while (!openList.empty())
    {
        // ���� ���� ����Ʈ���� ���(fCost)�� ���� ���� ��� �˻�.
        // ����ȭ ����(�켱 ���� ť, ��).
        AStarNode* lowestNode = openList[0];
        for (AStarNode* node : openList)
        {
            if (node->fCost < lowestNode->fCost)
                lowestNode = node;
        }

        // ����� ���� ���� ��带 ���� ���� ����.
        AStarNode* currentNode = lowestNode;

        // ���� ��尡 ��ǥ ������� Ȯ��.
        if (IsDestination(currentNode))
            // ��ǥ �������κ��� �������ؼ� ��θ� ���� �� ��ȯ.
            return ConstructPath(currentNode);

        // �湮 ó���� ���� ���� ��带 ���� ����Ʈ���� ����.
        int size = (int)openList.size();
        for (int i = 0; i < size; i++)
        {
            // �� ����� ��ġ�� ������� ������ Ȯ��.
            if (openList[i]->position.x == currentNode->position.x &&
                openList[i]->position.y == currentNode->position.y)
            {
                openList.erase(openList.begin() + i);
                break;
            }
        }

        // �湮 ó���� ���� ���� ����Ʈ�� �߰�.
        // �̹� �߰��� ���� ����.
        bool isNodeInList = false;
        for (AStarNode* node : closedList)
        {
            // ��ġ ������� ��.
            if (node->position.x == currentNode->position.x &&
                node->position.y == currentNode->position.y)
            {
                isNodeInList = true;
                break;
            }
        }

        // �̹� ������ ����.
        if (isNodeInList)
            continue;

        // ������ ���� ����Ʈ�� �߰�.
        closedList.emplace_back(currentNode);

        // �̿� ��� �湮(�ϻ���� .. ���ʷ� �湮).
        for (const Direction& direction : directions)
        {
            // ������ �̵��� ��ġ Ȯ��.
            int newX = currentNode->position.x + direction.x;
            int newY = currentNode->position.y + direction.y;

            // �׸��带 ����� ����.
            if (!IsInRange(newX, newY, grid))
                continue;

            // �̵��� ��尡 �̵� �������� Ȯ��.
            if (grid[newY][newX] == true)
                continue;

            // �̹� �湮�ߴ��� Ȯ��.
            if (HasVisited(newX, newY, currentNode->gCost + direction.cost))
                continue;

            // �湮�� ��� ����(��� ���).
            AStarNode* neighborNode = new AStarNode(newX, newY, currentNode);
            neighborNode->gCost = currentNode->gCost + direction.cost;
            neighborNode->hCost = CalculateHeuristic(neighborNode, goalNode);
            neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

            // ���� ����Ʈ�� �߰�.
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

            // �̿� ��尡 ����Ʈ�� ������ �ٷ� �߰�.
            // ����Ʈ�� �ִٸ� ����� ���� �� �����ϸ� ��� �߰�.
            if (openListNode == nullptr ||
                neighborNode->gCost < openListNode->gCost ||
                neighborNode->fCost < openListNode->fCost)
            {
                openList.emplace_back(neighborNode);
            }
            else
            {
                // ����Ʈ �߰� ����� �ƴ϶��, �޸� ����.
                SafeDelete(neighborNode);
            }
        }
    }

    // Ž�� ����.
    return vector<AStarNode*>();
}

vector<AStarNode*> AStar::ConstructPath(AStarNode* goalNode)
{
    // ��ǥ ���κ��� �θ� ��带 ���� �������ϸ鼭 ��� ����.
    std::vector<AStarNode*> path;
    AStarNode* currentNode = goalNode;
    while (currentNode != nullptr)
    {
        path.emplace_back(currentNode);
        currentNode = currentNode->parent;
    }

    // ���� �������� ��ǥ �������� ���ϵ��� �迭 ������.
    std::reverse(path.begin(), path.end());
    return path;
}

float AStar::CalculateHeuristic(AStarNode* currentNode, AStarNode* goalNode)
{
    // ���� ��忡�� ��ǥ �������� ���� ���.
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
    // ����/���� ����Ʈ�� �̹� �ش� ��ġ�� ������ �湮�� ������ �Ǵ�.
    int size = (int)openList.size();
    for (int i = 0; i < size; i++)
    {
        AStarNode* node = openList[i];
        if (node->position.x == x && node->position.y == y)
        {
            // ��ġ�� ���� ����� �� ũ�� �湮�� ������ ����.
            if (gCost >= node->gCost)
                return true;

            // �� ����� ����� ���� ��쿡�� ���� ��� ����.
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
            // ��ġ�� ���� ����� �� ũ�� �湮�� ������ ����.
            if (gCost >= node->gCost)
                return true;

            // �� ����� ����� ���� ��쿡�� ���� ��� ����.
            closedList.erase(closedList.begin() + i);
            SafeDelete(node);
            size--;
        }
    }

    // ����Ʈ�� ������ �湮���� ���� ������ �Ǵ�.
    return false;
}

bool AStar::IsDestination(const AStarNode* node)
{
    return (node->position.x == goalNode->position.x &&
            node->position.y == goalNode->position.y);
}