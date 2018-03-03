#include "stdafx.h"
#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

BinarySearchTree::BinarySearchTree()
{
	root = nullptr;
	nodeNum = 0;
}

BinarySearchTree::~BinarySearchTree()
{
	ReleaseNode(root);
	root = nullptr;
}

// 노드를 생성하는 함수
BinarySearchTree::TreeNode* BinarySearchTree::CreateNode(int data)
{
	TreeNode* tmpNode = new TreeNode;

	tmpNode->left = nullptr;
	tmpNode->right = nullptr;
	tmpNode->data = data;

	return tmpNode;
}

// 새로운 데이터를 추가한다.
void BinarySearchTree::InsertNode(int data)
{
	if (root == nullptr)
	{
		root = CreateNode(data);
	}
	else // root != nullptr
	{
		LinkNode(root, data);
	}

	nodeNum++;
}

// InsertNode 내부에서 호출되는 위치 찾아 추가 재귀 함수
void BinarySearchTree::LinkNode(TreeNode* node, int data)
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
		}
	}
	else // node->data == data
	{
		OutputDebugString(L"이미 같은 값의 Key가 존재합니다.\n");
		exit(20);
	}
}

// 데이터를 삭제한다.
void BinarySearchTree::DeleteNode(int data)
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

		target->data = tmpNode->data;

		if (parent == nullptr)
		{
			target->left = tmpNode->left;
		}
		else // parent != nullptr
		{
			parent->right = tmpNode->left;
		}		

		target = tmpNode;
	}

	delete target;
	nodeNum--;
}

// 노드를 검색하는 함수
BinarySearchTree::TreeNode* BinarySearchTree::SearchNode(TreeNode* node, int key)
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
void BinarySearchTree::ReleaseTree()
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
void BinarySearchTree::ReleaseNode(TreeNode* node)
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
void BinarySearchTree::InOrderPrint(HDC hdc, HDC memDC, POINT point, TreeNode* node, int depth)
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

	Rectangle(memDC, point.x - 1, point.y, point.x + 17, point.y + 18);

	SetBkMode(memDC, OPAQUE);
	TextOut(memDC, point.x, point.y + 1, tmpChar, lstrlen(tmpChar));
}

// 노드 개수 구하기
int BinarySearchTree::GetNodeNum()
{
	return nodeNum;
}