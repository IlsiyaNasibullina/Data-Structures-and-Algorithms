// Ilsiia Nasibullina CS-05
#include<iostream>
#include <vector>

using namespace std;

class LineSegment {
private:
    long long xbeg;
    long long ybeg;
    long long xend;
    long long yend;
public:
    LineSegment(long long x1, long long y1, long long x2, long long y2) {
        xbeg = x1;
        ybeg = y1;
        xend = x2;
        yend = y2;
    }

    long long getXbeg() {
        return this->xbeg;
    }

    long long getYbeg() {
        return this->ybeg;
    }

    long long getXend() {
        return this->xend;
    }

    long long getYend() {
        return this->yend;
    }

    void setXbeg(long long x1) {
        LineSegment::xbeg = x1;
    }

    void setYbeg(long long y1) {
        LineSegment::ybeg = y1;
    }

    void setXend(long long x2) {
        LineSegment::xend = x2;
    }

    void setYend(long long y2) {
        LineSegment::yend = y2;
    }

    bool operator<(LineSegment A) const {
        if (this->xbeg < A.getXbeg()) {
            return true;
        }
        return false;
    }

    bool operator==(LineSegment A) const {
        if (this->xbeg == A.getXbeg() && this->ybeg == A.getYbeg()
            && this->xend == A.getXend() && this->yend == A.getYend()) {
            return true;
        }
        return false;
    }

    bool operator>(LineSegment A) const {
        if (this->xbeg > A.getXbeg()) {
            return true;
        }
        return false;
    }

    friend ostream &operator<<(ostream &cout, LineSegment A);
};

ostream &operator<<(ostream &cout, LineSegment A) {
    cout << A.xbeg << " " << A.ybeg << " " << A.xend << " " << A.yend;
    cout << "\n";
    return cout;
}

class SegmentPoint {
private:
    long long x;
    long long y;
    long long indexOfLine;
    bool beginOfSegment;
public:
    SegmentPoint(long long x1, long long y1, long long index, bool begin) {
        x = x1;
        y = y1;
        indexOfLine = index;
        beginOfSegment = begin;
    }

    void setX(long long xbeg) {
        SegmentPoint::x = xbeg;
    }

    void setY(long long ybeg) {
        SegmentPoint::y = ybeg;
    }

    void setIndexOfLine(long long index) {
        SegmentPoint::indexOfLine = index;
    }

    void setBeginOfSegment(bool begin) {
        SegmentPoint::beginOfSegment = begin;
    }

    long long getX() {
        return x;
    }

    long long getY() {
        return y;
    }

    long long getIndexOfLine() {
        return indexOfLine;
    }

    bool isBeginOfSegment() {
        return beginOfSegment;
    }

    bool operator<(SegmentPoint A) {
        if (this->x < A.getX()) {
            return true;
        }
        if (this->x == A.getX() && this->y < A.getY()) return true;
        return false;
    }

    bool operator>(SegmentPoint A) const {
        if (this->x > A.getX()) {
            return true;
        }
        if (this->x == A.getX() && this->y > A.getY()) return true;
        return false;
    }

    friend ostream &operator<<(ostream &cout, SegmentPoint &A);
};

ostream &operator<<(ostream &cout, SegmentPoint &A) {
    cout << A.x << " " << A.y << " " << A.indexOfLine << " " << A.beginOfSegment;
    cout << "\n";
    return cout;
}

template<class T>
class Node {

public:
    T value;
    int height;
    Node<T> *left;
    Node<T> *right;

    explicit Node(T value) : value(value), height(1), left(nullptr), right(nullptr) {}
};

template<class T>
class AVL {
private:
    Node<T> *root;
public:
    // O(1) in all cases
    AVL() {
        root = nullptr;
    }

    // The time complexity of balanceFactor() is O(1) in all best, average and worst cases,
    // as height() also works in constant time
    int balanceFactor(Node<T> *node) {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    // The time complexity of insertInTree() is O(log n) in worst case
    Node<T> *insertInTree(T data, Node<T> *node) {
        if (node == nullptr) {
            node = new Node<T>(data);
        } else if (data < node->value) {
            node->left = insertInTree(data, node->left);
        } else if (data > node->value) {
            node->right = insertInTree(data, node->right);
        }
        node->height = (max(height(node->left), height(node->right)) + 1);

        int factor = balanceFactor(node);
        if (factor > 1) {
            if (data < node->left->value) {
                return rightRotate(node);
            } else if (data > node->left->value) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        if (factor < -1) {
            if (data > node->right->value) {
                return leftRotate(node);
            } else if (data < node->right->value) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }

    // The time complexity of rightRotate() is O(1) in all best, average and worst cases
    Node<T> *rightRotate(Node<T> *node) {
        Node<T> *x = node->left;
        node->left = x->right;
        x->right = node;
        node->height = (max(height(node->left), height(node->right)) + 1);
        x->height = (max(height(x->right), height(x->left)) + 1);
        return x;
    }

    // The time complexity of leftRotate() is O(1) in all best, average and worst cases
    Node<T> *leftRotate(Node<T> *node) {
        Node<T> *x = node->right;
        node->right = x->left;
        x->left = node;
        node->height = (max(height(node->right), height(node->left)) + 1);
        x->height = (max(height(x->right), height(x->left)) + 1);
        return x;
    }

    // The time complexity of findMin() is O(log n) in worst case
    // as in worst case we search for min for the root and go through height of the tree, which is log n
    Node<T> * findMin(Node<T> * node) {
        if (node == nullptr) return node;
        else if (node->left == nullptr) return node;
        else return findMin(node->left);
    }

    // The time complexity of deleteFromTree() is O(log n) in worst case
    Node<T> *deleteFromTree(T data, Node<T> *node) {
        Node<T> * temp = nullptr;
        if (node == nullptr) {
            return node;
        }
        else if (data < node->value) {
            node->left = deleteFromTree(data, node->left);
        }
        else if (data > node->value) {
            node->right = deleteFromTree(data, node->right);
        }
        else if (node->left && node->right) {
            temp = findMin(node->right);
            node->value = temp->value;
            node->right = deleteFromTree(node->value, node->right);
        }
        else {
            temp = node;
            if (node->left == nullptr) node = node->right;
            else if (node->right == nullptr) node = node->left;
            delete temp;
        }

        if (node == nullptr) return node;
        node->height = max(height(node->right), height(node->left)) + 1;
        int factor = balanceFactor(node);
        if (factor > 1) {
            if (height(node->left) >= height(node->right)) {
                return rightRotate(node);
            }
            else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        else if (factor < -1) {
            if (height(node->right) >= height(node->left)) {
                return leftRotate(node);
            }
            else {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }

    //The time complexity of insert() is O(log n) in worst cae
    // as it calls insertInTree() which works in O(lon n) in worst case
    void insert(T value) {
        root = insertInTree(value, root);
    }

    // The time complexity of deleteNode() is O(log n) in worst case
    // as it calls deleteFromNode() which works in O(log n) in worst case
    void deleteNode(T value) {
        root = deleteFromTree(value, root);
    }

    // The time complexity of height() is O(1) in both average and worst cases
    int height(Node<T> *node) {
        if (node == nullptr) {
            return -1;
        }
        return node->height;
    }

    // The time complexity of successorExist() is O(1) in best case and O(log n) in worst and average case,
    // inside this function we do constant operations and call successor() and search(),
    // which work in O(log n) in average and worst cases and O(1) in best case
    bool successorExist(T value) {
        Node<T> *temp = search(value, root);
        if (successor(temp) != nullptr && successor(temp) != temp) return true;
        return false;
    }

    // The time complexity of predeccessorExist() is O(1) in best case and O(log n) in worst and average case,
    // inside this function we do constant operations and call predeccessor() and search(),
    // which work in O(log n) in average and worst cases and O(1) in best case
    bool predeccessorExist(T value) {
        Node<T> *temp = search(value, root);
        if (predeccessor(temp) != nullptr && predeccessor(temp) != temp) return true;
        return false;
    }

    // The time complexity of findSuccessor() is O(1) in best case and O(log n) in worst and average case,
    // inside this function we do constant operations and call successor() and search(),
    // which work in O(log n) in average and worst cases and O(1) in best case
    T findSuccessor(T value) {
        Node<T> *temp = search(value, root);
        return successor(temp)->value;
    }

    // The time complexity of findPredeccessor() is O(1) in best case and O(log n) in worst and average case,
    // inside this function we do constant operations and call predeccessor() and search(),
    // which work in O(log n) in average and worst cases and O(1) in best case
    T findPredeccessor(T value) {
        Node<T> *temp = search(value, root);
        return predeccessor(temp)->value;
    }

    // The time complexity of predeccessor() is O(log n) in average and worst case, in best case O(1)
    // as in the worst cae we will have to travel the whole height of the tree
    Node<T> *predeccessor(Node<T> *node) {
        if (node == nullptr) return node;
        if (node->left != nullptr) {
            Node<T> *temp = node->left;
            while (temp->right != nullptr) {
                temp = temp->right;
            }
            return temp;
        }
        Node<T> *temp = findParent(node, root);
        while (temp != nullptr && node == temp->left) {
            node = temp;
            temp = findParent(temp, root);
        }
        return temp;
    }

    // The time complexity of search() is O(log n) in worst case
    // as we go from root to leaves and log n is the height of the tree, the case of searching a leaf is the worst one
    Node<T> *search(T value, Node<T> *node) {
        if (node == nullptr || node->value == value) {
            return node;
        } else if (value < node->value) {
            return search(value, node->left);
        }
        return search(value, node->right);
    }

    // The time complexity of findParent() is O(log n) in worst case
    // we go from root and the worst case is when we search for the parent of a leaf, so we go through the height
    // of th tree, which is log n
    Node<T> *findParent(Node<T> *toFind, Node<T> *node) {
        if (node == nullptr) return node;
        if (node->right == toFind || node->left == toFind) {
            return node;
        } else if (toFind->value < node->value) {
            return findParent(toFind, node->left);
        }
        return findParent(toFind, node->right);
    }

    //The time complexity of successor() is O(log n) in worst and average case, O(1) in best case
    // as in worst case we travel the whole height of the tree
    Node<T> *successor(Node<T> *node) {
        if (node == nullptr) return node;
        if (node->right != nullptr) {
            Node<T> *temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            return temp;
        }
        Node<T> *temp = findParent(node, root);
        while (temp != nullptr && node == temp->right) {
            node = temp;
            temp = findParent(temp, root);
        }
        return temp;
    }
};

template<typename T>
void quicksort(vector<T> *tosort, int leftbound, int rightbound) {
    int leftNewBound = leftbound;
    int rightNewBound = rightbound;
    T pivot = (*tosort)[(leftNewBound + rightNewBound) / 2];
    do {
        while ((*tosort)[leftNewBound] < pivot) {
            leftNewBound++;
        }
        while ((*tosort)[rightNewBound] > pivot) {
            rightNewBound--;
        }
        if (leftNewBound <= rightNewBound) {
            if (leftNewBound < rightNewBound) {
                T tmp = (*tosort)[leftNewBound];
                (*tosort)[leftNewBound] = (*tosort)[rightNewBound];
                (*tosort)[rightNewBound] = tmp;
            }
            leftNewBound++;
            rightNewBound--;
        }
    } while (leftNewBound <= rightNewBound);

    if (leftNewBound < rightbound) {
        quicksort(tosort, leftNewBound, rightbound);
    }
    if (leftbound < rightNewBound) {
        quicksort(tosort, leftbound, rightNewBound);
    }
}

// The method of determining intersection is taken from:
// https://www.geeksforgeeks.org/given-a-set-of-line-segments-find-if-any-two-segments-intersect/?ref=rp

long long orientation(SegmentPoint p, SegmentPoint q, SegmentPoint r) {
    long long val = (q.getY() - p.getY()) * (r.getX() - q.getX()) - (q.getX() - p.getX()) * (r.getY() - q.getY());
    if (val == 0) return 0;
    return (val > 0)? 1: 2;
}

bool belongToSegment(SegmentPoint p, SegmentPoint q, SegmentPoint r) {
    if (q.getX() <= max(p.getX(), r.getX()) && q.getX() >= min(p.getX(), r.getX()) &&
        q.getY() <= max(p.getY(), r.getY()) && q.getY() >= min(p.getY(), r.getY()))
        return true;

    return false;
}

bool intersect(LineSegment s1, LineSegment s2) {
    SegmentPoint p1(s1.getXbeg(), s1.getYbeg(), 0, true);
    SegmentPoint q1(s1.getXend(), s1.getYend(), 0, false);
    SegmentPoint p2(s2.getXbeg(), s2.getYbeg(), 0, true);
    SegmentPoint q2(s2.getXend(), s2.getYend(), 0, false);

    long long o1 = orientation(p1, q1, p2);
    long long o2 = orientation(p1, q1, q2);
    long long o3 = orientation(p2, q2, p1);
    long long o4 = orientation(p2, q2, q1);


    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && belongToSegment(p1, p2, q1)) return true;


    if (o2 == 0 && belongToSegment(p1, q2, q1)) return true;


    if (o3 == 0 && belongToSegment(p2, p1, q2)) return true;


    if (o4 == 0 && belongToSegment(p2, q1, q2)) return true;

    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int numberOfSegments;
    cin >> numberOfSegments;
    vector<LineSegment> allLines;
    vector<SegmentPoint> allPoints;
    for (int i = 0; i < numberOfSegments; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        LineSegment tek = LineSegment(x1, y1, x2, y2);
        allLines.push_back(tek);
        if (x1 > x2) {
            SegmentPoint beginOfLine = SegmentPoint(x2, y2, i, true);
            SegmentPoint endOfLine = SegmentPoint(x1, y1, i, false);
            allPoints.push_back(beginOfLine);
            allPoints.push_back(endOfLine);
        }
        else {
            SegmentPoint beginOfLine = SegmentPoint(x1, y1, i, true);
            SegmentPoint endOfLine = SegmentPoint(x2, y2, i, false);
            allPoints.push_back(beginOfLine);
            allPoints.push_back(endOfLine);
        }
    }
    quicksort(&allPoints, 0, 2 * numberOfSegments - 1);

    AVL<LineSegment> tree = AVL<LineSegment>();
    bool intersection = false;
    vector<LineSegment> answer;
    int cn = 0;
    for (auto i: allPoints) {
        if (i.isBeginOfSegment()) {
            tree.insert(allLines[i.getIndexOfLine()]);
            LineSegment A = allLines[i.getIndexOfLine()];
            if (tree.successorExist(allLines[i.getIndexOfLine()])) {
                LineSegment B = tree.findSuccessor(allLines[i.getIndexOfLine()]);
                if (intersect(B, A)) {
                    intersection = true;
                    answer.push_back(A);
                    answer.push_back(B);
                    break;
                }
            }
            if (tree.predeccessorExist(allLines[i.getIndexOfLine()])) {
                LineSegment B = tree.findPredeccessor(allLines[i.getIndexOfLine()]);
                if (intersect(A, B)) {
                    intersection = true;
                    answer.push_back(A);
                    answer.push_back(B);
                    break;
                }
            }
        } else {
            if (tree.predeccessorExist(allLines[i.getIndexOfLine()])
                && tree.successorExist(allLines[i.getIndexOfLine()])) {
                LineSegment A = tree.findSuccessor(allLines[i.getIndexOfLine()]);
                LineSegment B = tree.findPredeccessor(allLines[i.getIndexOfLine()]);
                if (intersect(A, B)) {
                    intersection = true;
                    answer.push_back(A);
                    answer.push_back(B);
                    break;
                }
            }
            tree.deleteNode(allLines[i.getIndexOfLine()]);
        }
    }
    if (!intersection) {
        cout << "NO INTERSECTIONS" << "\n";
    } else {
        cout << "INTERSECTION" << "\n";
        cout << answer[0];
        cout << answer[1];
    }
}
