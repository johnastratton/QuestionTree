#include "qtree.h"
#include <exception>
#include <iostream>

const std::string QuestionTree::INTERNAL_HEADER("D:");
const std::string QuestionTree::LEAF_HEADER("FG:");

QuestionTree::Distinguish::Distinguish(const std::string& q, Node* yes, 
      Node* no, QuestionTree& t, Distinguish* _parent) :
  q(q), yesSubtree(yes), noSubtree(no), parent(_parent), tree(t) {};

QuestionTree::Distinguish* QuestionTree::Distinguish::getParent() { 
  return parent; 
}

void QuestionTree::Distinguish::setParent(Distinguish* newParent) { 
  parent = newParent;
}

void QuestionTree::Distinguish::deleteSubtrees() {
  yesSubtree->deleteSubtrees();
  delete yesSubtree;
  noSubtree->deleteSubtrees();
  delete noSubtree;
}

void QuestionTree::Distinguish::printSubtree(std::ostream& out) {
  out << INTERNAL_HEADER << ' ' << q << std::endl;
  yesSubtree->printSubtree(out);
  noSubtree->printSubtree(out);
};

//Ask the user a true-false question, and get a yes/no answer back
bool QuestionTree::getAnswer(const std::string& question) {
  std::cout << question << std::endl;
  std::string response("?");
  do {
    std::cout << "Enter (y)es or (n)o: ";
    std::getline(std::cin, response);
  } while (!std::cin.fail() && response[0] != 'y' && response[0] != 'n');
  if (response[0] == 'y') {
    return true;
  } else if (response[0] == 'n') {
    return false;
  } else {
    throw new std::exception();
  }
}

void QuestionTree::Distinguish::replaceChild(Node* orig, Node* newChild) {
  //Find which child needs to be replaced, and do the replacing
  //FIXME: only throw an exception if we have a problem, like not finding orig
  throw new std::exception();
}

void QuestionTree::Distinguish::play() {
  bool answer = QuestionTree::getAnswer(q);
  //FIXME: well, we have an answer, now what do we do?
}

void QuestionTree::FinalGuess::expand() {
  std::cin.clear();
  std::cout << "What were you thinking of?  "
    << "Include an article (a, an, the) if appropriate:" << std::endl;
  std::string response;
  //Need to use this to read a whole line/phrase instead of one word
  std::getline(std::cin, response);
  std::cout << "What is a yes/no question that would distinguish between " 
    << guess << " and " << response << "?" << std::endl;
  std::string question;
  //Need to use this to read a whole line/phrase instead of one word
  std::getline(std::cin, question);
  bool answerForNew = QuestionTree::getAnswer(std::string("What is the correct answer for ") + response + '?');

  FinalGuess* newGuess = new FinalGuess(response, tree);
  Distinguish* newQuestion;
  //FIXME: create new question node with appropriate yes/no children, and 
  //put the new question node in the tree
}

void QuestionTree::FinalGuess::play() {
  std::string question;
  question = std::string("Are you thinking of ") + guess + std::string("?");
  if (QuestionTree::getAnswer(question)) {
    std::cout << "Naturally." << std::endl;
  } else {
    std::cout << "Well, drat." << std::endl;
    if (tree.expand()) {
      expand();
    }
  }
}
