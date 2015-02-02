#include "stdafx.h"

#include "Tree.h"

namespace Formula
{

	Tree::Tree()
		: roof_(NULL)
		, cur_node_(NULL)
	{
	}

	Tree::~Tree()
	{
	}

	void Tree::add(const Token& token, Direction direction)
	{
		if (roof_ == NULL)
		{
			roof_ = new TreeNode();
			roof_->token_ = token;
			roof_->left_ = NULL;
			roof_->right_ = NULL;

			cur_node_ = roof_;
		}
		else
		{
		}
	}

} // Formula
