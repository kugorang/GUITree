#pragma once

#define SCREEN_WIDTH 1000

class AVLTree
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

	// 노드를 생성하는 함수
	TreeNode* CreateNode(int data);

	// InsertNode 내부에서 호출되는 위치 찾아 추가 재귀 함수
	void LinkNode(TreeNode* node, int data);

	// 노드를 검색하는 함수
	TreeNode* SearchNode(TreeNode* node, TreeNode* target, TreeNode* parent);

	// ReleaseTree 내부에서 호출되는 노드 삭제용 재귀함수
	void ReleaseNode(TreeNode* node);

	// 트리 깊이 구하기
	int GetDepth(TreeNode* node);

	// 밸런스 구하기
	int GetBalance(TreeNode* node);

	// LL 회전으로 돌리는 함수
	TreeNode* RotateNodeLL(TreeNode* node);

	// LR 회전으로 돌리는 함수
	TreeNode* RotateNodeLR(TreeNode* node);

	// RL 회전으로 돌리는 함수
	TreeNode* RotateNodeRL(TreeNode* node);

	// RR 회전으로 돌리는 함수
	TreeNode* RotateNodeRR(TreeNode* node);

	// 밸런스를 맞추는 함수
	TreeNode* Rebalance(TreeNode* node);
public:
	AVLTree();
	~AVLTree();

	// 새로운 데이터를 추가한다.
	void InsertNode(int data);

	// 데이터를 삭제한다.
	void DeleteNode(int data);

	// 트리 전체 삭제
	void ReleaseTree();

	// 중위순회 방식 출력
	void InOrderPrint(HDC hdc, HDC memDC, POINT point, TreeNode* node = nullptr, int depth = 0);

	// 노드 개수 구하기
	int GetNodeNum();
};