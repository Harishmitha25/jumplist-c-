#include "JumpList.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Node::Node(const string& s, Node* next, Node* jump, int gap) {
	data_ = s;
	next_ = next;
	jump_ = jump;
	gap_ = gap;
}

Node::~Node() {

}


JumpList::JumpList() {
	head_ = nullptr;
}

// DO NOT CHANGE
// You do not need to understand the code here to complete the assignment
JumpList::JumpList(int size, const string* arr) {

	const string s[] = {"a", "b", "blah", "c", "cat", "d", "etc", "ooo...", "x", "zzz"};
	const string* sp = (arr == nullptr) ? s : arr;

	Node** npp = new Node*[size];
	npp[size-1] = new Node(sp[size-1], nullptr, nullptr, 0);
	for(int i = size-2; i >= 0; i--)
		npp[i] = new Node(sp[i], npp[i+1], nullptr, 0);

	if (arr == nullptr) {

		if (size==1) npp[0]->gap_ = 1;
		else if (size==3) npp[0]->gap_ = 3;
 		else if (size==10) {
			npp[0]->jump_ = npp[5];
			npp[5]->jump_ = npp[8];
			npp[0]->gap_ = 5;
			npp[5]->gap_ = 3;
			npp[8]->gap_ = 2;
		}
		else throw std::invalid_argument("size must be 1, 3 or 10");

	}
	else {

		// jump node every MAX_GAP_SIZE
		int i;
		for(i=0; i < size-MAX_GAP_SIZE; i += MAX_GAP_SIZE) {
			npp[i]->jump_ = npp[i+MAX_GAP_SIZE];
			npp[i]->gap_ = MAX_GAP_SIZE;
		}
		npp[i]->gap_ = size % MAX_GAP_SIZE;
		if (npp[i]->gap_ == 0) npp[i]->gap_ = MAX_GAP_SIZE; // 0 need to become 5!

	}

	head_ = npp[0];
	delete [] npp; // note that the local array npp gets destroyed here but the nodes stay alive!

}

JumpList::~JumpList() {
       Node* temp = head_;
       while (temp != nullptr) {
       	        Node* next = temp->next_;
                delete temp;
                temp = next;
        }
        head_ = nullptr; 
}


int JumpList::size() const {
	if (head_ == nullptr) return 0;

	int size = 0;
	Node* temp = head_;

	while(temp != nullptr) {
		size = size + temp->gap_;
		temp = temp->jump_;
	}
	return size;
}

// DONE FOR YOU, DO NOT CHANGE
bool JumpList::find(const string& s) const {

	if (head_ == nullptr) return false;

	// moving along the fast lane
	Node* tmp = head_;
	while(tmp->jump_ != nullptr && tmp->jump_->data_ < s)
		tmp = tmp->jump_;

	// tmp now points to the jump node at the start of the segment where s could be

	// now slow lane
	while(tmp != nullptr) {
		if (tmp->data_ == s) return true; // match
		else if (tmp->data_ > s) return false; // went past without finding s
		else tmp = tmp->next_;
	}

	return false; // end of list
}

string JumpList::get(int i) const {
	if (head_ == nullptr) return "";
	
	Node* tmp = head_;
	int totalNodesCovered = tmp->gap_;
	int numberOfNodesBeforeJump = 0;

	while(tmp != nullptr &&  i+1>totalNodesCovered) {
		numberOfNodesBeforeJump += tmp ->gap_;
		tmp = tmp->jump_;
		totalNodesCovered = tmp!= nullptr ? totalNodesCovered + tmp->gap_ : totalNodesCovered;
	}

	// Calculate the index within the segment
	int indexInTheSegment = (i - numberOfNodesBeforeJump);

	// Slow lane to traverse through each node in the segment to find the node
	while(tmp != nullptr && indexInTheSegment != 0) {
		tmp = tmp->next_;
		indexInTheSegment--;
	}

	// Return data if the node is found or return ""
	if (indexInTheSegment == 0 && tmp != nullptr) return tmp->data_;
	else return "";
}

string JumpList::print() const {
	if (head_ == nullptr) return "\n\n";
	
	Node* temp = head_;
	string resultStr = "";
	string thirdLine = "";

	// Traverse all nodes
	while(temp != nullptr) {
		if (temp->next_!= nullptr) {
			resultStr += temp->data_ + " ";
		} else {
			resultStr += temp->data_ + "\n";
		}
		temp = temp->next_;
	}

	temp = head_;
	// Traverse jump nodes to get jump node data and gaps
	while(temp != nullptr) {
		if (temp->jump_!= nullptr) {
			resultStr += temp->data_ + " ";
			thirdLine += to_string(temp->gap_) + " ";
		} else {
			resultStr += temp->data_ + "\n";
			thirdLine += to_string(temp->gap_);
		}
		temp = temp->jump_;
	}
	
	resultStr+=thirdLine;
	return resultStr;
}

string JumpList::prettyPrint() const {
	if (head_ == nullptr) return "\n\n";

	string resultStr = "";
	string firstLine="";
	string secondLine = "";
	string thirdLine = "";
	Node* temp = head_;
	Node* jumpNode = head_;
	int totalDataLengthOfTheSegment = 0;
	int times = 0;

	while(temp != nullptr) {
		if (temp->next_!= nullptr) {
			firstLine += temp->data_ + " --> ";

			if ((totalDataLengthOfTheSegment == 0 && temp->gap_ != 0) || (totalDataLengthOfTheSegment > 0 && temp->gap_ == 0)) {
				totalDataLengthOfTheSegment+=temp->data_.length();
			} else if ((totalDataLengthOfTheSegment > 0 && temp->gap_ !=0)) {
				secondLine += jumpNode->data_+" ";
				thirdLine += to_string(jumpNode->gap_);
				times = (totalDataLengthOfTheSegment+jumpNode->gap_*5) - 3 - jumpNode->data_.length(); // "*5" indicates that " --> " is of length 5 so gap * 5, -3 indicates the space between the first node and the long arrow starting (1) and "> "(2) at the end of the long arrow, minus the jump node data length as it is already added
				secondLine.append(times,'-');
				secondLine+="> ";
				thirdLine.append(totalDataLengthOfTheSegment + (jumpNode->gap_*5) - 1, ' '); // "*5" because same reason as above, -1 indicates gap (single digi)
				jumpNode = temp;
				totalDataLengthOfTheSegment = jumpNode->data_.length();
			}
		} else {
			firstLine += temp->data_ + "\n";
			secondLine += jumpNode->data_+"\n";
			thirdLine += to_string(jumpNode->gap_);
		}
		temp = temp->next_;
	}
	resultStr = firstLine + secondLine + thirdLine;
	return resultStr;
}

bool JumpList::insert(const string& s) {
	// Add new node to empty list
        if (head_ == nullptr) {
		Node* newNode = new Node(s, nullptr, nullptr, 1);
		head_ = newNode;
		return true;
	};

	// s that needs to be added before the head
	if (head_ != nullptr && s < head_->data_) {
	    Node* temp = head_;
		Node* oldHead = head_;
		Node* newNode = new Node(s, nullptr, nullptr, 0);
		int segSize = head_->gap_ + 1;
		newNode->next_ = temp;
		if (segSize > MAX_GAP_SIZE) { // Odd splitting never occurs. Eg: If node is added and seg size becomes > 5 then its always split evenly
			head_ = newNode;
			temp = head_;
			int split = segSize/2;
			head_->gap_ = split;
			while(temp != nullptr && split-- > 0) {
				temp = temp->next_;
			}
			if (temp != nullptr) {
				temp->gap_ = head_->gap_;
				head_->jump_ = temp;
			}
			temp->jump_ = oldHead->jump_;
		} else {
			head_->gap_ = 0;
			head_ = newNode;
			head_->gap_ = segSize;
			head_->jump_ = temp -> jump_;
			temp-> jump_ = nullptr;
		}
		return true;
	}
	// Moving along the fast lane
	Node* temp = head_;
	while(temp->jump_ != nullptr && temp->jump_->data_ < s)
		temp = temp->jump_;

	Node* firstNodeInSegment = temp;
	Node* segmentTraversalNode = temp;
	Node* prevNode = temp;

	// s which needs to be added between first and last nodes
	while(temp != nullptr) {
		if (temp->data_ == s) return false;
		if(temp!= nullptr && temp->data_ < s) {
		    prevNode = temp;
			temp = temp->next_;
		} else if(temp!= nullptr && temp->data_ > s) {
			Node* newNode = new Node(s, nullptr, nullptr, 0);
			prevNode->next_ = newNode;
			newNode->next_ = temp;
		    
			int currentSegGap = firstNodeInSegment->gap_ + 1;
			if (currentSegGap > MAX_GAP_SIZE) {
				int split = currentSegGap/2;
				firstNodeInSegment->gap_ = split;

				while(segmentTraversalNode != nullptr && split-- > 0  ) {
					segmentTraversalNode = segmentTraversalNode->next_;
				}

				segmentTraversalNode->gap_ = firstNodeInSegment->gap_;
				
				Node* fixedJumpNode  = segmentTraversalNode;
				firstNodeInSegment->jump_ = segmentTraversalNode;

				while(segmentTraversalNode != nullptr) {
					segmentTraversalNode = segmentTraversalNode->next_;
					if (segmentTraversalNode != nullptr && segmentTraversalNode->gap_ != 0) {
						fixedJumpNode-> jump_ = segmentTraversalNode;
						break;
					}
				}				
			} else {
				firstNodeInSegment->gap_ = firstNodeInSegment->gap_ + 1;
			}
		    return true;
		}
	}
	
	// s which needs to be added after last node
	if (temp == nullptr) {
		Node* newNode = new Node(s, nullptr, nullptr, 0);
		prevNode->next_ = newNode;
		int segSize = firstNodeInSegment->gap_ + 1;
		if (segSize > MAX_GAP_SIZE) {
			int split = segSize/2;
			firstNodeInSegment->gap_ = split;
			temp = firstNodeInSegment;
			while(temp != nullptr && split > 0) {
				split--;
				temp = temp->next_;
			}
 		    if (temp!=nullptr && split == 0) {
				temp->gap_ = firstNodeInSegment->gap_;
				firstNodeInSegment->jump_ = temp;
			}
			return true;
		} else {
			firstNodeInSegment->gap_ = segSize;
			return true;
		}
	}
	return false;
}

bool JumpList::erase(const string& s) {
	if (head_==nullptr) return false;

	// s which is the head
	if(head_-> data_== s) {
		if (head_->next_ != nullptr) {
			Node* temp = head_;
			head_ = head_->next_;
			if(head_->gap_ != 1) {
				head_->gap_ = temp->gap_ - 1;
			    head_->jump_ = temp->jump_;
			}			
			delete temp;
			return true;
		} else {
			delete head_;
			head_ = nullptr;
			return true;
		}
	}

	Node* temp = head_;
	Node* prevJumpNode = temp;
	Node* prevNode = temp;

	while(temp->jump_ != nullptr && temp->jump_->data_ < s) {
		prevJumpNode = temp;
		temp = temp->jump_;
	}
        Node* jumpNodeOfTheSegment = temp;
	while(temp!=nullptr) {
		if (temp->data_ == s && temp->gap_ != 0) { // Jump node deletion
			// Special cases
			if (temp->gap_ == 1 && prevJumpNode->gap_ == 1 && temp->jump_!=nullptr && temp->jump_->gap_ == 1) {
				prevJumpNode->jump_ = temp->jump_;
				prevJumpNode->next_ = temp->jump_;
				delete temp;
				return true;
			} else if (temp->gap_ == 1 && prevJumpNode->gap_ == 1 && temp->jump_==nullptr) {
				prevJumpNode->jump_ = nullptr;
				prevJumpNode-> next_ = nullptr;
				delete temp;
				return true;
			} else if (temp->gap_ == 1 && prevJumpNode->gap_ > 1) {
				prevJumpNode->gap_ = prevJumpNode->gap_ - 1;
				prevJumpNode->jump_ = nullptr;
				delete temp;
				return true;
			}

			// Normal cases
			if (temp != nullptr) prevNode->next_ = temp->next_ != nullptr ? temp->next_ : nullptr;
			
			int mergedSegSize = (prevJumpNode->gap_ + temp->gap_) - 1;
			if (mergedSegSize > MAX_GAP_SIZE) {
				int split =  mergedSegSize/2;
				if (mergedSegSize % 2 == 0) {
					prevJumpNode->gap_ = split;
					Node* tmp = prevJumpNode;
					while(tmp != nullptr && split-- > 0) {
						tmp = tmp->next_;
					}
					if (tmp != nullptr) {
						tmp-> gap_ = prevJumpNode-> gap_;
						prevJumpNode->jump_ = tmp;
					}
					tmp->jump_ = temp->jump_;
					delete temp;
					return true;
				} else {
					split+=1;
					prevJumpNode->gap_ = split;
					Node* tmp = prevJumpNode;
					while(tmp != nullptr && split-- > 0) {
						tmp = tmp->next_;
					}
					if (tmp != nullptr) {
						tmp-> gap_ = prevJumpNode->gap_ - 1;
						prevJumpNode->jump_ = tmp;
					}
					tmp->jump_ = temp->jump_;
					delete temp;
					return true;
				}
			} else {
				prevJumpNode->gap_ = mergedSegSize;
				prevJumpNode->jump_ = temp->jump_;
				delete temp;
				return true;
			}
		}

		if (temp!=nullptr && temp->data_ == s && temp->gap_ == 0) { //Non-jump node
			if(temp != nullptr) prevNode->next_ = temp->next_ != nullptr ? temp->next_ : nullptr;
			
			jumpNodeOfTheSegment->gap_ = jumpNodeOfTheSegment->gap_ - 1;
			delete temp;
			return true;
		}
		
		prevNode = temp;
		if (temp->jump_ != nullptr && temp-> gap_ !=0 && temp->data_ != s) {  //Case where node to be deleted is equal to the last jump node
			prevJumpNode = temp;
		}
		temp =temp->next_;
	}

	return false;
}
