#pragma once

class RedBlackTree
{
private:
	enum NodeColor
	{
		BLACK,
		RED
	};

	struct TreeNode
	{
		TreeNode* parent;
		TreeNode* left;
		TreeNode* right;

		NodeColor color;

		int data;
	};

	TreeNode* root;
	TreeNode nil;	// ���� ����̸� ������ ���̰� NULL �뵵�̴�.

	int nodeNum;

	// ��带 �����ϴ� �Լ�
	TreeNode* CreateNode(int data, TreeNode* parent);

	// InsertNode ���ο��� ȣ��Ǵ� ��ġ ã�� �߰� ��� �Լ�
	TreeNode* LinkNode(TreeNode* node, int data);

	// ��带 �˻��ϴ� �Լ�
	TreeNode* SearchNode(TreeNode* node, int key);

	// ReleaseTree ���ο��� ȣ��Ǵ� ��� ������ ����Լ�
	void ReleaseNode(TreeNode* node);

	// ��带 �������� ������ �Լ�
	void RotateNodeLeft(TreeNode* node);

	// ��带 ���������� ������ �Լ�
	void RotateNodeRight(TreeNode* node);
public:
	RedBlackTree();
	~RedBlackTree();

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