#pragma once

#include "Token.h"

namespace Formula
{

	struct TreeNode
	{
		Token token_;

		TreeNode *left_;
		TreeNode *right_;
	};

	class Tree
	{
	public:
		enum Direction
		{
			DirectionLeft,
			DirectionRight
		};

	public:
		Tree();
		~Tree();

		void add(const Token& token, Direction direction);

	private:
		TreeNode *roof_;
		TreeNode *cur_node_;
	};

} // Formula
