#pragma once

class BinarySearchTree
{
private:
	struct TreeNode
	{
		TreeNode* left;
		TreeNode* right;

		int data;
	};

	TreeNode* root;
	int nodeNum;

	// ��带 �����ϴ� �Լ�
	TreeNode* CreateNode(int data);

	// InsertNode ���ο��� ȣ��Ǵ� ��ġ ã�� �߰� ��� �Լ�
	void LinkNode(TreeNode* node, int data);

	// ��带 �˻��ϴ� �Լ�
	TreeNode* SearchNode(TreeNode* node, int key);

	// ReleaseTree ���ο��� ȣ��Ǵ� ��� ������ ����Լ�
	void ReleaseNode(TreeNode* node);
public:
	BinarySearchTree();
	~BinarySearchTree();

	// ���ο� �����͸� �߰��Ѵ�.
	void InsertNode(int data);

	// �����͸� �����Ѵ�.
	void DeleteNode(int data);

	// Ʈ�� ��ü ����
	void ReleaseTree();

	// ������ȸ ��� ���
	void InOrderPrint(HDC hdc, HDC memDC, POINT point, TreeNode* node = nullptr, int depth = 0);
	
	// ��� ���� ���ϱ�
	int GetNodeNum();
};