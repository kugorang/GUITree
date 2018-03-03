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

// ��带 �����ϴ� �Լ�
BinarySearchTree::TreeNode* BinarySearchTree::CreateNode(int data)
{
	TreeNode* tmpNode = new TreeNode;

	tmpNode->left = nullptr;
	tmpNode->right = nullptr;
	tmpNode->data = data;

	return tmpNode;
}

// ���ο� �����͸� �߰��Ѵ�.
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

// InsertNode ���ο��� ȣ��Ǵ� ��ġ ã�� �߰� ��� �Լ�
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
		OutputDebugString(L"�̹� ���� ���� Key�� �����մϴ�.\n");
		exit(20);
	}
}

// �����͸� �����Ѵ�.
void BinarySearchTree::DeleteNode(int data)
{
	if (root == nullptr)
	{
		OutputDebugString(L"root�� ��� �ֽ��ϴ�.\n");
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
		OutputDebugString(L"Key ���� �������� �ʽ��ϴ�.\n");
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

// ��带 �˻��ϴ� �Լ�
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

// Ʈ�� ��ü ����
void BinarySearchTree::ReleaseTree()
{
	if (root == nullptr)
	{
		/*OutputDebugString(L"root�� ��� �ֽ��ϴ�.\n");
		exit(22);*/

		return;
	}
	else // root != nullptr
	{
		ReleaseNode(root);
	}
}

// ReleaseTree ���ο��� ȣ��Ǵ� ��� ������ ����Լ�
void BinarySearchTree::ReleaseNode(TreeNode* node)
{
	if (node == nullptr)
	{
		OutputDebugString(L"root�� ��� �ֽ��ϴ�.\n");
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

// ������ȸ ��� ���
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
			/*OutputDebugString(L"root�� ��� �ֽ��ϴ�.\n");
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

// ��� ���� ���ϱ�
int BinarySearchTree::GetNodeNum()
{
	return nodeNum;
}