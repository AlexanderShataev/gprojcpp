//
// Created by alexander on 16.09.2024.
//

#ifndef TREENODE_H
#define TREENODE_H

#include <list>
#include <memory>

namespace TRA {
    class TreeNode: public std::enable_shared_from_this<TreeNode> {
    public:
        TreeNode() = default;
        void addChild(std::shared_ptr<TreeNode>&& child);
        std::shared_ptr<TreeNode> getParent() const;
        std::list<std::shared_ptr<TreeNode> > getChilds() const;

    private:
        std::weak_ptr<TreeNode> parent_;
        std::list<std::shared_ptr<TreeNode> > childs_container_;
    };
}

#endif //TREENODE_H
