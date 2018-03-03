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

	// 노드를 생성하는 함수
	TreeNode* CreateNode(int data);

	// InsertNode 내부에서 호출되는 위치 찾아 추가 재귀 함수
	void LinkNode(TreeNode* node, int data);

	// 노드를 검색하는 함수
	TreeNode* SearchNode(TreeNode* node, int key);

	// ReleaseTree 내부에서 호출되는 노드 삭제용 재귀함수
	void ReleaseNode(TreeNode* node);
public:
	BinarySearchTree();
	~BinarySearchTree();

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