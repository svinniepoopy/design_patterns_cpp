#include <iostream>
#include <memory>
#include <unordered_map>

/* 
 * Create a few different types of trees using the prototype pattern.
 * Each deriving tree class must implement a clone() method, which is
 * abstract in the base Tree class. Here it just returns a smart pointer
 * of the concrete tree class but it could create a tree of that particular
 * type and return it.
 */

namespace {
  enum TreeType {BTREE, SPLAYTREE, AVLTREE};
};

class Tree {
  public:
    virtual ~Tree() {}
    virtual std::unique_ptr<Tree> clone() = 0;
    virtual void print() = 0;
};

class BTree : public Tree {
  public:
    BTree()=default;
    void print() override {
      std::cout << "BTree";
    }

    std::unique_ptr<Tree> clone() override {
      return std::make_unique<BTree>(*this);
    }
};

class SplayTree : public Tree {
  public:
    SplayTree()=default;
    void print() override {
      std::cout << "SplayTree";
    }

    std::unique_ptr<Tree> clone() override {
      return std::make_unique<SplayTree>(*this);
    }
};

class AVLTree : public Tree {
  public:
    AVLTree()=default;
    void print() override {
      std::cout << "AVLTree";
    }

    std::unique_ptr<Tree> clone() override {
      return std::make_unique<AVLTree>(*this);
    }
};

class TreeFactory {
  private:
    std::unordered_map<TreeType, std::unique_ptr<Tree>> records;
  public:
      TreeFactory() {
	records[BTREE] = std::make_unique<BTree>();
	records[SPLAYTREE] = std::make_unique<SplayTree>();
	records[AVLTREE] = std::make_unique<AVLTree>();
      }

      std::unique_ptr<Tree> createTree(TreeType tree_type) {
	return records[tree_type]->clone();
      }
};

int main() {
  TreeFactory tf;
  auto tree = tf.createTree(SPLAYTREE);
  tree->print();

  tree = tf.createTree(BTREE);
  tree->print();

  tree = tf.createTree(AVLTREE);
  tree->print();
}
