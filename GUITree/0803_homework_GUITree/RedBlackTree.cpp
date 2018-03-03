#include "stdafx.h"
#include <iostream>
#include "RedBlackTree.h"
#include "0803_homework_GUITree.h"
using namespace std;

RedBlackTree::RedBlackTree()
{
	root = nullptr;
	nodeNum = 0;

	nil.parent = nullptr;
	nil.left = nullptr;
	nil.right = nullptr;
	nil.color = BLACK;
	nil.data = -1;
}

RedBlackTree::~RedBlackTree()
{
	ReleaseNode(root);
	root = nullptr;
}

// 노드를 생성하는 함수
RedBlackTree::TreeNode* RedBlackTree::CreateNode(int data, TreeNode* parent)
{
	TreeNode* tmpNode = new TreeNode;

	tmpNode->parent = parent;
	tmpNode->left = &nil;
	tmpNode->right = &nil;
	tmpNode->data = data;
	tmpNode->color = RED;

	return tmpNode;
}

// 새로운 데이터를 추가한다.
void RedBlackTree::InsertNode(int data)
{
	TreeNode* insertNode = nullptr;

	if (root == nullptr)
	{
		root = CreateNode(data, nullptr);
		root->color = BLACK;
	}
	else // root != nullptr
	{
		insertNode = LinkNode(root, data);

		Draw();

		//Sleep(1000);
		
		TreeNode* parentNode = insertNode->parent;

		if (parentNode == root)
		{
			return;
		}

		TreeNode* grandParentNode = parentNode->parent;
		TreeNode* uncleNode = grandParentNode->data > parentNode->data ?
			grandParentNode->right : grandParentNode->left;
					
		while (!(parentNode->color == BLACK || insertNode == root))
		{			
			switch (uncleNode->color)
			{
			case RED:
				parentNode->color = BLACK;
				uncleNode->color = BLACK;
				grandParentNode->color = RED;

				insertNode = grandParentNode;

				if (insertNode == root)
				{
					break;
				}
				parentNode = insertNode->parent;
				grandParentNode = parentNode->parent;

				if (grandParentNode != nullptr)
				{
					uncleNode = grandParentNode->data > parentNode->data ?
						grandParentNode->right : grandParentNode->left;
				}

				Draw();
				break;
			case BLACK:
				if (uncleNode == grandParentNode->right)
				{
					if (insertNode == parentNode->right)
					{
						RotateNodeLeft(parentNode);

						TreeNode* tmpNode = insertNode;
						insertNode = parentNode;
						parentNode = tmpNode;
					}
						
					parentNode->color = BLACK;
					grandParentNode->color = RED;
					RotateNodeRight(grandParentNode);
				}
				else // uncleNode == grandParentNode->left
				{
					if (insertNode == parentNode->left)
					{
						RotateNodeRight(parentNode);

						TreeNode* tmpNode = insertNode;
						insertNode = parentNode;
						parentNode = tmpNode;
					}

					parentNode->color = BLACK;
					grandParentNode->color = RED;
					RotateNodeLeft(grandParentNode);
				}
				break;
			}

			Draw();
		}		
	}

	root->color = BLACK;
	nodeNum++;
}

// 노드를 왼쪽으로 돌리는 함수
void RedBlackTree::RotateNodeLeft(TreeNode* node)
{
	TreeNode** parentDirection = nullptr;

	if (node->parent != nullptr)
	{
		parentDirection = node->parent->data > node->data ?
			&node->parent->left : &node->parent->right;

		*parentDirection = node->right;
	}
	else
	{
		root = node->right;
	}

	// node의 부모와 오른쪽 자식을 연결한다.	
	node->right->parent = node->parent;

	// node의 오른쪽 자식을 node의 부모로 설정한다.
	node->parent = node->right;

	// node의 오른쪽 자식의 왼쪽 자식을 node의 오른쪽 자식으로 연결한다.
	node->right = node->parent->left;
	node->parent->left->parent = node;
	node->parent->left = node;

	Draw();

	//Sleep(1000);
}

// 노드를 오른쪽으로 돌리는 함수
void RedBlackTree::RotateNodeRight(TreeNode* node)
{
	TreeNode** parentDirection = nullptr;

	if (node->parent != nullptr)
	{
		parentDirection = node->parent->data > node->data ?
			&node->parent->left : &node->parent->right;

		*parentDirection = node->left;
	}
	else
	{
		root = node->left;
	}

	// node의 부모와 왼쪽 자식을 연결한다.
	node->left->parent = node->parent;

	// node의 왼쪽 자식을 node의 부모로 설정한다.
	node->parent = node->left;

	// node의 왼쪽 자식의 오른쪽 자식을 node의 왼쪽 자식으로 연결한다.
	node->left = node->parent->right;
	node->parent->right->parent = node;
	node->parent->right = node;

	Draw();

	//Sleep(1000);
}

// InsertNode 내부에서 호출되는 위치 찾아 추가 재귀 함수
RedBlackTree::TreeNode* RedBlackTree::LinkNode(TreeNode* node, int data)
{
	TreeNode* tmpNode = nullptr;

	if (node->data > data)
	{
		if (node->left == &nil)
		{
			node->left = CreateNode(data, node);
			tmpNode = node->left;
		}
		else // node->left != nullptr
		{
			tmpNode = LinkNode(node->left, data);
		}
	}
	else if (node->data < data)
	{
		if (node->right == &nil)
		{
			node->right = CreateNode(data, node);
			tmpNode = node->right;
		}
		else // node->right != nullptr
		{
			tmpNode = LinkNode(node->right, data);
		}
	}
	else // node->data == data
	{
		OutputDebugString(L"이미 같은 값의 Key가 존재합니다.\n");
		exit(20);
	}

	return tmpNode;
}

// 데이터를 삭제한다.
void RedBlackTree::DeleteNode(int data)
{
	if (root == nullptr)
	{
		OutputDebugString(L"root가 비어 있습니다.\n");
		exit(21);
	}

	// 삭제 작업.
	TreeNode* targetNode = root;

	while (targetNode != nullptr && targetNode->data != data)
	{
		targetNode = targetNode->data > data ? targetNode->left : targetNode->right;
	}

	if (targetNode == nullptr)
	{
		OutputDebugString(L"Key 값이 존재하지 않습니다.\n");
		exit(21);
	}

	TreeNode* parentNode = targetNode->parent;

	if (targetNode->left == &nil && targetNode->right == &nil)
	{
		if (targetNode == root)
		{
			root = nullptr;
		}
		else
		{
			if (parentNode->left == targetNode)
			{
				parentNode->left = &nil;
			}
			else // parent->right == targetNode
			{
				parentNode->right = &nil;
			}
		}
	}
	else if (targetNode->left == &nil || targetNode->right == &nil)
	{
		if (targetNode == root)
		{
			root = targetNode->left == &nil ?
				targetNode->right : targetNode->left;

			root->parent = nullptr;
			root->left = &nil;
			root->right = &nil;
		}
		else
		{
			if (parentNode->left == targetNode)
			{
				parentNode->left = targetNode->left == &nil ?
					targetNode->right : targetNode->left;

				parentNode->left->parent = parentNode;
			}
			else // parent->right == targetNode
			{
				parentNode->right = targetNode->left == &nil ?
					targetNode->right : targetNode->left;

				parentNode->right->parent = parentNode;
			}
		}
	}
	else // targetNode->left != nullptr && targetNode->right != nullptr
	{
		TreeNode* tmpNode = targetNode->left;
		parentNode = nullptr;

		while (tmpNode->right != &nil)
		{
			parentNode = tmpNode;
			tmpNode = tmpNode->right;
		}

		targetNode->data = tmpNode->data;

		if (parentNode == nullptr)
		{
			targetNode->left = tmpNode->left;
			tmpNode->left->parent = targetNode;
		}
		else // parent != nullptr
		{
			parentNode->right = tmpNode->left;
			tmpNode->left->parent = parentNode;
		}

		targetNode = tmpNode;
	}

	Draw();

	// 밸런스 맞추기
	TreeNode* deleteNode = nullptr;

	if (targetNode->left == &nil && targetNode->right == &nil)
	{
		deleteNode = &nil;
	}
	else // (targetNode->left == &nil || targetNode->right == &nil)
	{
		deleteNode = targetNode->left == &nil ?
			targetNode->right : targetNode->left;
	}

	parentNode = targetNode->parent;
	TreeNode* sibilingNode = nullptr;
	
	if (targetNode->color == RED)
	{
		deleteNode->color = BLACK;
	}
	else // targetNode->color == BLACK
	{
		while (deleteNode->parent != nullptr && root != nullptr)
		{
			sibilingNode = parentNode->left == deleteNode ?
				parentNode->right : parentNode->left;

			switch (sibilingNode->color)
			{
			case RED:
				sibilingNode->color = BLACK;

				if (sibilingNode == parentNode->right)
				{
					RotateNodeLeft(parentNode);
				}
				else // sibilingNode == parentNode->left
				{
					RotateNodeRight(parentNode);
				}

				parentNode->color = RED;
				break;
			case BLACK:
				if (deleteNode->color == RED)
				{
					deleteNode->color = BLACK;

					if (root != nullptr)
					{
						root->color = BLACK;
					}

					delete targetNode;

					nodeNum--;

					return;
				}

				if (sibilingNode->left->color == BLACK && sibilingNode->right->color == BLACK)
				{
					sibilingNode->color = RED;

					deleteNode = parentNode;
					parentNode = deleteNode->parent;
				}
				else
				{
					if (sibilingNode == parentNode->right)
					{
						if (sibilingNode->left->color == RED)
						{
							sibilingNode->left->color = BLACK;
							sibilingNode->color = RED;
							RotateNodeRight(sibilingNode);

							sibilingNode = sibilingNode->parent;
						}

						sibilingNode->color = parentNode->color;
						parentNode->color = BLACK;
						sibilingNode->right->color = BLACK;

						RotateNodeLeft(parentNode);
					}
					else // sibilingNode == parentNode->left
					{
						if (sibilingNode->right->color == RED)
						{
							sibilingNode->right->color = BLACK;
							sibilingNode->color = RED;
							RotateNodeLeft(sibilingNode);

							sibilingNode = sibilingNode->parent;
						}

						sibilingNode->color = parentNode->color;
						parentNode->color = BLACK;
						sibilingNode->left->color = BLACK;

						RotateNodeRight(parentNode);
					}

					if (root != nullptr)
					{
						root->color = BLACK;
					}

					delete targetNode;

					nodeNum--;

					return;
				}

				break;
			}

			Draw();
		}
	}
	
	if (root != nullptr)
	{
		root->color = BLACK;
	}

	delete targetNode;

	nodeNum--;
}

// 노드를 검색하는 함수
RedBlackTree::TreeNode* RedBlackTree::SearchNode(TreeNode* node, int key)
{
	if (node == nullptr)
	{
		return nullptr;
	}

	TreeNode* tmpNode = nullptr;

	if (node->data > key)
	{
		tmpNode = SearchNode(node->left, key);
	}
	else if (node->data < key)
	{
		tmpNode = SearchNode(node->right, key);
	}
	else // node->data == key
	{
		tmpNode = node;
	}

	return tmpNode;
}

// 트리 전체 삭제
void RedBlackTree::ReleaseTree()
{
	if (root == nullptr)
	{
		/*OutputDebugString(L"root가 비어 있습니다.\n");
		exit(22);*/

		return;
	}
	else // root != nullptr
	{
		ReleaseNode(root);		
		nodeNum = 0;
	}
}

// ReleaseTree 내부에서 호출되는 노드 삭제용 재귀함수
void RedBlackTree::ReleaseNode(TreeNode* node)
{
	if (node == nullptr)
	{
		OutputDebugString(L"root가 비어 있습니다.\n");
		exit(23);
	}

	if (node->left != &nil)
	{
		ReleaseNode(node->left);
	}

	if (node->right != &nil)
	{
		ReleaseNode(node->right);
	}

	cout << "delete : " << node->data << endl;

	if (node == root)
	{
		delete root;
		root = nullptr;
	}
	else // node != root
	{
		delete node;
	}
}

// 중위순회 방식 출력
void RedBlackTree::InOrderPrint(HDC hdc, HDC memDC, POINT point, TreeNode* node, int depth)
{
	if (node == nullptr)
	{
		if (root != nullptr)
		{
			node = root;
		}
		else
		{
			/*OutputDebugString(L"root가 비어 있습니다.\n");
			exit(24);*/
			return;
		}
	}

	POINT tmpPoint;

	if (node->left != nullptr)
	{
		tmpPoint.x = point.x - 960 / (int)pow(2.0, depth + 1);
		tmpPoint.y = (depth + 1) * 30;

		MoveToEx(memDC, point.x + 8, point.y + 9, NULL);
		LineTo(memDC, tmpPoint.x + 8, tmpPoint.y + 9);

		InOrderPrint(hdc, memDC, tmpPoint, node->left, depth + 1);
	}

	if (node->right != nullptr)
	{
		tmpPoint.x = point.x + 960 / (int)pow(2.0, depth + 1);
		tmpPoint.y = (depth + 1) * 30;

		MoveToEx(memDC, point.x + 8, point.y + 9, NULL);
		LineTo(memDC, tmpPoint.x + 8, tmpPoint.y + 9);
		InOrderPrint(hdc, memDC, tmpPoint, node->right, depth + 1);
	}

	WCHAR tmpChar[2] = { 0, };
	wsprintf(tmpChar, L"%d", node->data);

	SelectObject(memDC, GetStockObject(DC_PEN));

	if (node->color == RED)
	{
		SetDCPenColor(memDC, RGB(255, 0, 0));
	}
	
	Rectangle(memDC, point.x - 1, point.y, point.x + 17, point.y + 18);
	
	SetDCPenColor(memDC, RGB(0, 0, 0));

	SetBkMode(memDC, OPAQUE);
	TextOut(memDC, point.x, point.y + 1, tmpChar, lstrlen(tmpChar));
}

// 노드 개수 구하기
int RedBlackTree::GetNodeNum()
{
	return nodeNum;
}