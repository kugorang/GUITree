#include "stdafx.h"
#include <iostream>
#include "AVLTree.h"
#include "0803_homework_GUITree.h"
using namespace std;

AVLTree::AVLTree()
{
	root = nullptr;
	nodeNum = 0;
}

AVLTree::~AVLTree()
{
	ReleaseNode(root);
	root = nullptr;
}

// 노드를 생성하는 함수
AVLTree::TreeNode* AVLTree::CreateNode(int data)
{
	TreeNode* tmpNode = new TreeNode;

	tmpNode->left = nullptr;
	tmpNode->right = nullptr;
	tmpNode->data = data;

	return tmpNode;
}

// 새로운 데이터를 추가한다.
void AVLTree::InsertNode(int data)
{
	if (root == nullptr)
	{
		root = CreateNode(data);
	}
	else // root != nullptr
	{
		LinkNode(root, data);
		root = Rebalance(root);
	}

	nodeNum++;
}

// InsertNode 내부에서 호출되는 위치 찾아 추가 재귀 함수
void AVLTree::LinkNode(TreeNode* node, int data)
{
	if (node->data > data)
	{
		if (node->left == nullptr)
		{
			node->left = CreateNode(data);
		}
		else // node->left != nullptr
		{
			LinkNode(node->left, data);
			node->left = Rebalance(node->left);
		}
	}
	else if (node->data < data)
	{
		if (node->right == nullptr)
		{
			node->right = CreateNode(data);
		}
		else // node->right != nullptr
		{
			LinkNode(node->right, data);
			node->right = Rebalance(node->right);
		}
	}
	else // node->data == data
	{
		OutputDebugString(L"이미 같은 값의 Key가 존재합니다.\n");
		exit(20);
	}

	Draw();
}

// 데이터를 삭제한다.
void AVLTree::DeleteNode(int data)
{
	if (root == nullptr)
	{
		OutputDebugString(L"root가 비어 있습니다.\n");
		exit(21);
	}

	TreeNode *parent = nullptr, *target = root;

	while (target != nullptr && target->data != data)
	{
		parent = target;
		target = target->data > data ? target->left : target->right;
	}

	if (target == nullptr)
	{
		OutputDebugString(L"Key 값이 존재하지 않습니다.\n");
		exit(21);
	}

	TreeNode* tmpNode = target;

	if (target->left != nullptr && target->right != nullptr)
	{
		tmpNode = target->left;
		parent = nullptr;

		while (tmpNode->right != nullptr)
		{
			parent = tmpNode;
			tmpNode = tmpNode->right;
		}
	}

	int tmpData = tmpNode->data;

	TreeNode* deleteNode = SearchNode(root, tmpNode, parent);

	target->data = tmpData;
		
	if (root != nullptr)
	{
		root = Rebalance(root);
	}

	delete deleteNode;

	nodeNum--;
}

// 노드를 검색하는 함수
AVLTree::TreeNode* AVLTree::SearchNode(TreeNode* node, TreeNode* target, TreeNode* parent)
{
	TreeNode* returnNode = nullptr;

	if (node == nullptr)
	{
		return nullptr;
	}

	if (node->data > target->data)
	{
		returnNode = SearchNode(node->left, target, node);

		if (node->left != nullptr)
		{
			node->left = Rebalance(node->left);
		}
	}
	else if (node->data < target->data)
	{
		returnNode = SearchNode(node->right, target, node);

		if (node->right != nullptr)
		{
			node->right = Rebalance(node->right);
		}
	}
	else // node->data == target->data
	{
		if (target->left == nullptr && target->right == nullptr)
		{
			if (target == root)
			{
				root = nullptr;
			}
			else
			{
				if (parent->left == target)
				{
					parent->left = nullptr;
				}
				else // parent->right == target
				{
					parent->right = nullptr;
				}
			}
		}
		else if (target->left == nullptr || target->right == nullptr)
		{
			if (target == root)
			{
				root = target->left == nullptr ?
					target->right : target->left;
			}
			else
			{
				if (parent->left == target)
				{
					parent->left = target->left == nullptr ?
						target->right : target->left;
				}
				else // parent->right == target
				{
					parent->right = target->left == nullptr ?
						target->right : target->left;
				}
			}
		}
		else // target->left != nullptr && target->right != nullptr
		{
			TreeNode* tmpNode = target->left;
			parent = nullptr;

			while (tmpNode->right != nullptr)
			{
				parent = tmpNode;
				tmpNode = tmpNode->right;
			}

			//target->data = tmpNode->data;

			if (parent == nullptr)
			{
				target->left = tmpNode->left;
			}
			else // parent != nullptr
			{
				parent->right = tmpNode->left;
			}
		}

		return node;
	}

	return returnNode;
}

// 트리 전체 삭제
void AVLTree::ReleaseTree()
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
	}
}

// ReleaseTree 내부에서 호출되는 노드 삭제용 재귀함수
void AVLTree::ReleaseNode(TreeNode* node)
{
	if (node == nullptr)
	{
		OutputDebugString(L"root가 비어 있습니다.\n");
		exit(23);
	}

	if (node->left != nullptr)
	{
		ReleaseNode(node->left);
	}

	if (node->right != nullptr)
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
		node = nullptr;
	}
}

// 중위순회 방식 출력
void AVLTree::InOrderPrint(HDC hdc, HDC memDC, POINT point, TreeNode* node, int depth)
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
		tmpPoint.x = point.x - SCREEN_WIDTH / 2 / (int)pow(2.0, depth + 1);
		tmpPoint.y = (depth + 1) * 30;

		MoveToEx(memDC, point.x + 8, point.y + 9, NULL);
		LineTo(memDC, tmpPoint.x + 8, tmpPoint.y + 9);

		InOrderPrint(hdc, memDC, tmpPoint, node->left, depth + 1);
	}

	if (node->right != nullptr)
	{
		tmpPoint.x = point.x + SCREEN_WIDTH / 2 / (int)pow(2.0, depth + 1);
		tmpPoint.y = (depth + 1) * 30;

		MoveToEx(memDC, point.x + 8, point.y + 9, NULL);
		LineTo(memDC, tmpPoint.x + 8, tmpPoint.y + 9);

		InOrderPrint(hdc, memDC, tmpPoint, node->right, depth + 1);
	}

	WCHAR tmpChar[16] = { 0, };
	wsprintf(tmpChar, L"%2d", node->data);
	wsprintf(tmpChar + 2, L":");
	wsprintf(tmpChar + 3, L"%d", GetBalance(node));

	Rectangle(memDC, point.x - 1, point.y, point.x + 33, point.y + 18);

	SetBkMode(memDC, OPAQUE);
	TextOut(memDC, point.x, point.y + 1, tmpChar, lstrlen(tmpChar));
}

// 노드 개수 구하기
int AVLTree::GetNodeNum()
{
	return nodeNum;
}

// 트리 깊이 구하기
int AVLTree::GetDepth(TreeNode* node)
{
	int leftDepth = 0, rightDepth = 0;

	if (node->left != nullptr)
	{
		leftDepth = GetDepth(node->left);
	}
	
	if (node->right != nullptr)
	{
		rightDepth = GetDepth(node->right);
	}

	int thisDepth = (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;

	return thisDepth;
}

// 밸런스 구하기
int AVLTree::GetBalance(TreeNode* node)
{
	int leftDepth = 0, rightDepth = 0;

	if (node->left != nullptr)
	{
		leftDepth = GetDepth(node->left);
	}

	if (node->right != nullptr)
	{
		rightDepth = GetDepth(node->right);
	}

	return leftDepth - rightDepth;
}

// LL 회전으로 돌리는 함수
AVLTree::TreeNode* AVLTree::RotateNodeLL(TreeNode* node)
{
	TreeNode* topNode = node;
	TreeNode* middleNode = node->left;
	TreeNode* bottomNode = middleNode->left;

	topNode->left = middleNode->right;
	middleNode->right = topNode;

	return middleNode;
}

// LR 회전으로 돌리는 함수
AVLTree::TreeNode* AVLTree::RotateNodeLR(TreeNode* node)
{
	TreeNode* topNode = node;
	TreeNode* middleNode = node->left;
	TreeNode* bottomNode = middleNode->right;

	topNode->left = bottomNode->right;
	middleNode->right = bottomNode->left;

	bottomNode->left = middleNode;
	bottomNode->right = topNode;

	return bottomNode;
}

// RL 회전으로 돌리는 함수
AVLTree::TreeNode* AVLTree::RotateNodeRL(TreeNode* node)
{
	TreeNode* topNode = node;
	TreeNode* middleNode = node->right;
	TreeNode* bottomNode = middleNode->left;

	topNode->right = bottomNode->left;
	middleNode->left = bottomNode->right;

	bottomNode->left = topNode;
	bottomNode->right = middleNode;

	return bottomNode;
}

// RR 회전으로 돌리는 함수
AVLTree::TreeNode* AVLTree::RotateNodeRR(TreeNode* node)
{
	TreeNode* topNode = node;
	TreeNode* middleNode = node->right;
	TreeNode* bottomNode = middleNode->right;

	topNode->right = middleNode->left;
	middleNode->left = topNode;

	return middleNode;
}

// 밸런스를 맞추는 함수
AVLTree::TreeNode* AVLTree::Rebalance(TreeNode* node)
{
	int balance = GetBalance(node);

	if (balance > 1)
	{
		node = GetBalance(node->left) > 0 ? 
			RotateNodeLL(node) : RotateNodeLR(node);
	}
	else if (balance < -1)
	{
		node = GetBalance(node->right) < 0 ?
			RotateNodeRR(node) : RotateNodeRL(node);
	}

	return node;
}