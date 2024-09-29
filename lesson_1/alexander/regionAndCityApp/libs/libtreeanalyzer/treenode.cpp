//
// Created by alexander on 16.09.2024.
//

#include "include/treeanalyzer/treenode.h"

void TRA::TreeNode::addChild(std::shared_ptr<TreeNode> &&child) {
    childs_container_.push_back(child);
}

std::shared_ptr<TRA::TreeNode> TRA::TreeNode::getParent() const {
    return parent_.lock();
}

std::list<std::shared_ptr<TRA::TreeNode>> TRA::TreeNode::getChilds() const {
    return childs_container_;
}
