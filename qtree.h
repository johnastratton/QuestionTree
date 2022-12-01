#ifndef CS270_QUESTION_TREE
#define CS270_QUESTION_TREE
#include <string>
#include <iostream>

//A decision tree to play a game of X questions, where X is yet to 
//be determined.
class QuestionTree {
 public:
  static const std::string INTERNAL_HEADER;
  static const std::string LEAF_HEADER;
 private:
  //Forward declarations for the two kinds of nodes in our tree
  class FinalGuess;
  class Distinguish;
  //Base class for all tree nodes
  class Node {
   public:
    //Play a guessing game, beginning with the question described in this node.
    virtual void play() = 0;
    // Get the parent of the current Node, or NULL if it is the root
    // Requires that nodes have parents, but no promises about 
    // children.  Clearly identifies all internal nodes as Distinguish nodes.
    virtual Distinguish* getParent() = 0;
    // Set the parent of the current Node
    virtual void setParent(Distinguish* newParent) = 0;
    // Delete the subtree rooted at this node : default behavior is to do nothing
    virtual void deleteSubtrees() { };
    // Print the subtree rooted at this node to the output stream specified
    virtual void printSubtree(std::ostream& out) = 0;
    virtual ~Node() { };
  };

  class Distinguish : public Node {
    friend class FinalGuess;
   public:
    Distinguish(const std::string& q, Node* yes, Node* no, QuestionTree& t, Distinguish* _parent = NULL);
    //Nothing to destroy in this node specifically
    virtual ~Distinguish() { }
    virtual Distinguish* getParent();
    virtual void setParent(Distinguish* newParent);
    virtual void play();
    void replaceChild(Node* orig, Node* newChild);
    //Delete all of the nodes in the subtrees attached to this node
    virtual void deleteSubtrees();
    //Print all of the nodes in this subtree in preorder traversal
    virtual void printSubtree(std::ostream& out);

   private:
    std::string q;
    Node* yesSubtree;
    Node* noSubtree;
    Distinguish* parent;
    QuestionTree& tree;
  };

  class FinalGuess : public Node {
    friend class Distinguish;
   public:
    FinalGuess(const std::string& g, QuestionTree& t, Distinguish* _parent = NULL) : 
      guess(g), parent(_parent), tree(t) {};
    //Nothing to destroy in this node specifically
    virtual ~FinalGuess() { }
    virtual Distinguish* getParent() { return parent; }
    virtual void play();
    void expand();
    virtual void setParent(Distinguish* newParent) { parent = newParent; }
    virtual void printSubtree(std::ostream& out) {
      out << LEAF_HEADER << ' ' << guess << std::endl;
    };
   private:
    std::string guess;
    Distinguish* parent;
    QuestionTree& tree;
  };

  void deleteTree(Node* root);
  Node* buildTreeFromStream(std::istream& in);

  Node* root;
  bool expandOnWrongGuess;

 public:
  QuestionTree(bool expanding = false) : 
    root(new FinalGuess("a polar bear", *this)), 
    expandOnWrongGuess(expanding) { };
  ~QuestionTree() { clear(); }
  void clear() { root->deleteSubtrees(); delete root; root = NULL; }
  bool expand() { return expandOnWrongGuess; }
  void play() { root->play(); }
  void readFromStream(std::istream& in);
  void writeToStream(std::ostream& out);
  //Ask the use a true-false question, and get a yes/no answer back
  static bool getAnswer(const std::string& question);

};
#endif // CS270_QUESTION_TREE
