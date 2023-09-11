#include <bits/stdc++.h>
using namespace std;
struct node
{
    node *parent, *sibling, *child;
    int data, degree;
    vector<node *> childrens;
    node(int data)
    {
        this->data = data;
        this->degree = 0;
        parent = NULL;
        sibling = NULL;
        child = NULL;
    }
};
class BinomialHeap
{
public:
    node *head;
    BinomialHeap()
    {
        head = NULL;
    }
    // merges two tree according to ascending order of their degree
    node *MergeAndSort(node *node1, node *node2)
    {
        node *mergedHead = NULL;
        node *mergedTail = NULL;
        while (node1 && node2)
        {
            node *newnode = NULL;
            if (node1->degree <= node2->degree)
            {
                newnode = node1;
                node1 = node1->sibling;
            }
            else
            {
                newnode = node2;
                node2 = node2->sibling;
            }
            if (mergedTail != NULL)
            {
                mergedTail->sibling = newnode;
            }
            else
            {
                mergedHead = newnode;
            }
            mergedTail = newnode;
        }
        if (node1)
        {
            if (mergedTail)
            {
                mergedTail->sibling = node1;
            }
            else
            {
                mergedHead = node1;
            }
            mergedTail = node1;
        }
        if (node2)
        {
            if (mergedTail)
            {
                mergedTail->sibling = node2;
            }
            else
            {
                mergedHead = node2;
            }
            mergedTail = node2;
        }

        return mergedHead;
    }
    // merge two same order tree
    node *mergeSameOrderedNodes(node *node1, node *node2)
    {
        node2->parent = node1;
        node2->sibling = node1->child;
        node1->child = node2;
        node1->degree++;
        node1->childrens.push_back(node2);
    }
    // completey merge two different tree
    node *mergeTwoTree(node *node1, node *node2)
    {
        if (node1 == NULL && node2 == NULL)
            return NULL;
        if (node1 == NULL)
            return node2;
        if (node2 == NULL)
            return node1;

        node *sortedHead = MergeAndSort(node1, node2);
        node *ptr = sortedHead;
        node *prev = NULL;
        node *cur = sortedHead;
        node *next = cur->sibling;

        while (next != NULL)
        {
            if (cur->degree != next->degree || (next->sibling != NULL && next->sibling->degree == cur->degree))
            {
                prev = cur;
                cur = next;
            }
            else if (cur->data <= next->data)
            {
                cur->sibling = next->sibling;
                mergeSameOrderedNodes(cur, next);
            }
            else
            {
                if (prev != NULL)
                    prev->sibling = next;
                else
                    sortedHead = next;
                mergeSameOrderedNodes(next, cur);
                cur = next;
            }
            next = cur->sibling;
            ptr = sortedHead;
        }

        return sortedHead;
    }
    void insert(int data)
    {
        node *newnode = new node(data);
        head = mergeTwoTree(head, newnode);
    }
    // run a level order traversal for each root node
    void bfs(node *head)
    {
        queue<pair<int, node *>> q;
        int prevLevel = -1;
        q.push({0, head});
        while (!q.empty())
        {
            node *cur = q.front().second;
            int curLevel = q.front().first;
            q.pop();
            if (curLevel != prevLevel)
            {
                if (prevLevel != -1)
                    cout << endl;
                prevLevel = curLevel;
                cout << "Level " << curLevel << " : ";
            }
            cout << cur->data << " ";
            vector<node *> childrens = cur->childrens;
            reverse(childrens.begin(), childrens.end());
            for (int i = 0; i < childrens.size(); i++)
            {
                q.push({curLevel + 1, childrens[i]});
            }
        }
        cout << endl;
    }

    void print()
    {
        cout << "Printing Binomial Heap..." << endl;

        node *cur = head;

        while (cur != NULL)
        {
            cout << "Binomial Tree, B" << cur->degree << endl;
            bfs(cur);
            cur = cur->sibling;
        }
    }
    // given a set of vertices it unite them with existing tree
    void unionHeap(vector<int> vertices)
    {
        BinomialHeap newheap;
        for (int i = 0; i < vertices.size(); i++)
        {
            newheap.insert(vertices[i]);
        }
        head = mergeTwoTree(head, newheap.head);
    }
    // returns the minimum node
    node *findMinNode(node *head)
    {
        int min = INT_MAX;
        node *minNode = NULL;
        node *cur = head;
        while (cur != NULL)
        {
            if (cur->data < min)
            {
                min = cur->data;
                minNode = cur;
            }
            cur = cur->sibling;
        }
        return minNode;
    }
    int findMin()
    {
        node *minNode = findMinNode(head);
        return (minNode != NULL) ? minNode->data : -1;
    }
    // reverse the the whole rootlist
    node *reverseHeap(node *child)
    {
        node *prev = NULL;
        node *current = child;
        node *next;

        while (current != NULL)
        {
            next = current->sibling;
            current->sibling = prev;
            prev = current;
            current = next;
        }

        return prev;
    }
    node *extractMinNode()
    {

        node *minNode = findMinNode(head);
        node *prev = NULL;
        node *cur = head;
        while (cur != minNode)
        {
            prev = cur;
            cur = cur->sibling;
        }

        if (prev == NULL)
        {
            head = minNode->sibling;
        }
        else
        {
            prev->sibling = minNode->sibling;
        }
        return minNode;
    }
    int extractMin()
    {
        node *minNode = extractMinNode();
        if (minNode == NULL)
            return -1;
        int minVal = minNode->data;
        node *childHead = minNode->child;
        childHead = reverseHeap(minNode->child);
        head = mergeTwoTree(head, childHead);
        delete minNode;
        return minVal;
    }
};

int main()
{
    BinomialHeap heap;
    char opearation;
    while (cin >> opearation)
    {
        if (opearation == 'I')
        {
            int data;
            cin >> data;
            heap.insert(data);
        }
        else if (opearation == 'P')
        {
            heap.print();
        }
        else if (opearation == 'U')
        {
            cin.ignore();
            string line;
            getline(cin, line);
            istringstream iss(line);
            int num;
            vector<int> numbers;

            while (iss >> num)
            {
                numbers.push_back(num);
            }
            heap.unionHeap(numbers);
        }
        else if (opearation == 'F')
        {
            int minVal = heap.findMin();
            if (minVal != -1)
                cout << "Find-Min returned " << minVal << endl;
        }
        else if (opearation == 'E')
        {
            int min = heap.extractMin();
            if (min != -1)
                cout << "Extract-Min returned " << min << endl;
        }
    }
}