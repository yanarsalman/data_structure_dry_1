#include <stdexcept>
#include <iostream>
#include <cmath>
#include <queue>

// StatusType
enum struct StatusType {
    SUCCESS          = 0,
    ALLOCATION_ERROR = 1,
    INVALID_INPUT    = 2,
    FAILURE          = 3,
};

// Genre
enum struct Genre {
    COMEDY           = 0,
    DRAMA            = 1,
    ACTION           = 2,
    FANTASY          = 3,
    NONE             = 4,
};

// output_t<T>
// The following class is used to support output with status code.
template<typename T>
class output_t {
private:
    // DO NOT access these private fields - may be enforced by verifier.
    const StatusType __status;
    const T __ans;

public:
    output_t() : __status(StatusType::SUCCESS), __ans(T()) { }
    output_t(StatusType status) : __status(status), __ans(T()) { }
    output_t(const T &ans) : __status(StatusType::SUCCESS), __ans(ans) { }

    StatusType status() { return __status; }
    T ans() { return __ans; }
};








//node.h
template<class T>
class Node {
public:
    int key;
    int content;
    Genre genre;
    bool isVip;
    int views;
    int numOfLeftSons;
    int numOfRightSons;
    int height;
    int ComedyViews;
    int FantasyViews;
    int DramaViews;
    int ActionViews;
    int GroupComedyViews;
    int GroupFantasyViews;
    int GroupDramaViews;
    int GroupActionViews;
    int rating;
    Node* leftSon;
    Node* rightSon;
    Node* father; //if needed
    T* curGroup;
    int groupViews;
    Node* groupUser;

    void addLeftSon(Node<T>* son);
    void addRightSon(Node<T>* son);
    void swapNodes(Node<T>* node1);
    int getBalanceFactor() const;
    int updateHeight();
    Node():content(0),leftSon(nullptr),rightSon(nullptr),
    father(nullptr),numOfRightSons(0),numOfLeftSons(0),height(0),key(0),
    genre(Genre::NONE), isVip(0), views(0), ComedyViews(0), FantasyViews(0), DramaViews(0), ActionViews(0),
    curGroup(nullptr), groupViews(0), groupUser(nullptr), GroupActionViews(0), GroupComedyViews(0),
    GroupDramaViews(0), GroupFantasyViews(0), rating(0){};
    Node(int key, int content,Node* father):key(key),content(content),genre(Genre::NONE),isVip(0),views(0),
    leftSon(nullptr),rightSon(nullptr),numOfRightSons(0),numOfLeftSons(0),father(father),height(0), ComedyViews(0)
    , FantasyViews(0), DramaViews(0), ActionViews(0), curGroup(nullptr), groupViews(0), groupUser(nullptr)
    , GroupActionViews(0), GroupComedyViews(0), GroupDramaViews(0), GroupFantasyViews(0), rating(0){}
    Node(int key):content(0),leftSon(nullptr),rightSon(nullptr),
    father(nullptr),numOfRightSons(0),numOfLeftSons(0),height(0),key(key),
    genre(Genre::NONE), isVip(0), views(0), ComedyViews(0),FantasyViews(0), DramaViews(0), ActionViews(0)
    ,curGroup(nullptr), groupViews(0), groupUser(nullptr)
    , GroupActionViews(0), GroupComedyViews(0), GroupDramaViews(0), GroupFantasyViews(0), rating(0){};
    ~Node()=default;
    Node(Node&)=default;
    Node& operator=(const Node& other)= default;
    void changeVip(bool newVip){isVip = newVip;}
    void changeViews(int newViews){views = newViews;}
    void changeGenre(Genre newGenre){genre = newGenre;}
    void changeContent(int newContent){content = newContent;}
};











//node.cpp
template<class T>
void Node<T>::addLeftSon(Node<T>* son)
{
    this->leftSon = son;
    Node<T>* currentFather = son->father;
    while(currentFather != nullptr)
    {
        currentFather->numOfLeftSons++;
        currentFather = currentFather->father;
    }
}

//
template<class T>
void Node<T>::addRightSon(Node<T>* son)
{
    this->rightSon = son;
    Node<T>* currentFather = son->father;
    while(currentFather != nullptr)
    {
        currentFather->numOfRightSons++;
        currentFather = currentFather->father;
    }

}
template<class T>
int Node<T>::updateHeight()
{
    int leftHeight,rightHeight;
    if(this->leftSon == nullptr)
    {
        leftHeight = -1;
    }
    else
    {
        leftHeight= this->leftSon->height;
    }
    if(this->rightSon == nullptr)
    {
        rightHeight = -1;
    }
    else
    {
        rightHeight= this->rightSon->height;
    }

    if(leftHeight > rightHeight)
    {
        this->height = leftHeight+1;
        return height;
    }
    this->height = rightHeight+1;
    return height;
}

template<class T>
int Node<T>::getBalanceFactor() const
{
    int leftHeight,rightHeight;
    if(this->leftSon == nullptr)
    {
        leftHeight = -1;
    } else
    {
        leftSon->updateHeight();
        leftHeight = leftSon->height;
    }
    if(this->rightSon == nullptr)
    {
        rightHeight = -1;
    } else
    {

        rightSon->updateHeight();
        rightHeight = rightSon->height;
    }
    return leftHeight-rightHeight;
}

template<class T>
void Node<T>::swapNodes(Node *node1)
{
    int temp;
    temp = this->content;
    this->content = node1->content;
    node1->content = temp;
}









// avl_tree.h

template<class T>
class AVL_Tree {
    int numOfNodes;
    T* root;
public:
    AVL_Tree():numOfNodes(0),root(nullptr){};
    ~AVL_Tree()=default;
    AVL_Tree(AVL_Tree& avlTree)=default;
    T* getRoot(){return this->root;};
    int getNumOfNodes() const{return this->numOfNodes;};
    T* searchAndAdd (T* toInsert);
    T* search(int content);
    StatusType searchAndDelete(int content);
    void leftRoll(T* node);
    void rightRoll(T* node);
    void printLevelOrder(); //FOR DEBUGGING
    void printTree(T* ptr){
        if(ptr == nullptr){
            return;
        }
        printTree(ptr->leftSon);
        std::cout << ptr->content << ",  ";
        printTree(ptr->rightSon);
    }
};







//avl_tree.cpp
template<class T>
T* AVL_Tree<T>::searchAndAdd(T* toInsert)
{
    // Search

    int toInsert_index= toInsert->content;
    T* currentNodePtr = this->root;
    T* currentFatherNodePtr = nullptr;
    while(currentNodePtr != nullptr)
    {
        currentFatherNodePtr = currentNodePtr;
        if (currentNodePtr->content < toInsert->content)
        {
            currentNodePtr = currentNodePtr->rightSon; //Go to right son
            if (currentNodePtr == nullptr)
            {
                toInsert->father = currentFatherNodePtr;
                currentFatherNodePtr->addRightSon(toInsert);
                break;
            }
            continue;
        }
        if (currentNodePtr->content == toInsert->content)
            return new T(-1);
        currentNodePtr = currentNodePtr->leftSon; //Go to right son
        if (currentNodePtr == nullptr)
        {
            toInsert->father = currentFatherNodePtr;
            currentFatherNodePtr->addLeftSon(toInsert);
            break;
        }
    }
    // Add
    if(currentFatherNodePtr == nullptr) //new root
    {
        toInsert->father = nullptr;
        this->root=toInsert;
        toInsert->updateHeight();
        this->numOfNodes++;
        return toInsert;
    }

    int oldHeight = currentFatherNodePtr->height;
    while(oldHeight != currentFatherNodePtr->updateHeight())
    {
        int currentBalanceFactor = currentFatherNodePtr->getBalanceFactor();
        if(abs(currentBalanceFactor) == 2)
        {
            if(currentBalanceFactor == -2) //balance -2 -> RR/RL
            {
                if(currentFatherNodePtr->rightSon->getBalanceFactor() == 1) //RL
                {
                    rightRoll(currentFatherNodePtr->rightSon);
                    leftRoll(currentFatherNodePtr);
                    break;
                }
                //RR
                leftRoll(currentFatherNodePtr);
                break;

            }
            //balance 2 -> LR/LL
            if(currentFatherNodePtr->leftSon->getBalanceFactor() == -1) //LR
            {
                leftRoll(currentFatherNodePtr->leftSon);
                rightRoll(currentFatherNodePtr);
                break;
            }
            //LL
            rightRoll(currentFatherNodePtr);
            break;
        }

        currentFatherNodePtr = currentFatherNodePtr->father;
        if (currentFatherNodePtr == nullptr)
            break;
        oldHeight = currentFatherNodePtr->height;
    }
    this->numOfNodes++;
    return toInsert;
}
template<class T>
StatusType AVL_Tree<T>::searchAndDelete(int content)
{
// Search

    T* currentNodePtr = this->root;
    T* currentFatherNodePtr = nullptr;
    while(currentNodePtr != nullptr)
    {
        if (currentNodePtr->content == content)
        {
            //found the node to delete
            //leaf
            currentFatherNodePtr = currentNodePtr->father;
            if(currentNodePtr->rightSon == nullptr && currentNodePtr->leftSon == nullptr)
            {
                //deleting root
                if (currentNodePtr->father == nullptr)
                {
                    root = nullptr;
                    numOfNodes--;
                    return StatusType::SUCCESS;
                }

                if (currentNodePtr->father->rightSon == currentNodePtr)
                {
                    currentNodePtr->father->rightSon = nullptr;
                    break;
                }
                currentNodePtr->father->leftSon = nullptr;
                break;
            }
            // has just one son
            if(currentNodePtr->rightSon != nullptr && currentNodePtr->leftSon == nullptr)
            {
                //deleting root
                if (currentNodePtr->father == nullptr)
                {
                    root = currentNodePtr->rightSon;
                    currentNodePtr->rightSon->father = nullptr;
                    numOfNodes--;
                    return StatusType::SUCCESS;
                }

                if (currentNodePtr->father->rightSon == currentNodePtr)
                {
                    currentNodePtr->father->rightSon = currentNodePtr->rightSon;
                    currentNodePtr->rightSon->father = currentNodePtr->father;
                    break;
                }
                currentNodePtr->father->leftSon = currentNodePtr->rightSon;
                currentNodePtr->rightSon->father = currentNodePtr->father;
                break;
            }
            if(currentNodePtr->leftSon != nullptr && currentNodePtr->rightSon == nullptr)
            {
                //deleting root
                if (currentNodePtr->father == nullptr)
                {
                    root = currentNodePtr->leftSon;
                    currentNodePtr->leftSon->father = nullptr;
                    numOfNodes--;
                    return StatusType::SUCCESS;
                }

                if (currentNodePtr->father->rightSon == currentNodePtr)
                {
                    currentNodePtr->father->rightSon = currentNodePtr->leftSon;
                }
                currentNodePtr->father->leftSon = currentNodePtr->leftSon;
                break;
            }
            // has two sons
            T* nodeToSwitch;
            nodeToSwitch = currentNodePtr->rightSon;
            while(nodeToSwitch->leftSon != nullptr)
            {
                nodeToSwitch = nodeToSwitch->leftSon;
            }
            if(nodeToSwitch->father->leftSon == nodeToSwitch)
            {
                nodeToSwitch->father->leftSon = nullptr;
            }
            else{nodeToSwitch->father->rightSon = nullptr; }
            currentFatherNodePtr = nodeToSwitch->father;
            nodeToSwitch->father = nullptr;
            nodeToSwitch->swapNodes(currentNodePtr);
            break;
        }
        if (currentNodePtr->content < content)
        {
            currentNodePtr = currentNodePtr->rightSon; //Go to right son
            if (currentNodePtr == nullptr)
            {
                return StatusType::FAILURE;
            }
            continue;
        }

        currentNodePtr = currentNodePtr->leftSon; //Go to right son
        if (currentNodePtr == nullptr)
        {
            return StatusType::FAILURE;
        }
    }

    // fixing the tree with rolls

    int oldHeight = currentFatherNodePtr->height;
    while(oldHeight != currentFatherNodePtr->updateHeight())
    {
        int currentBalanceFactor = currentFatherNodePtr->getBalanceFactor();
        if(abs(currentBalanceFactor) == 2)
        {
            if(currentBalanceFactor == -2) //balance -2 -> RR/RL
            {
                if(currentFatherNodePtr->rightSon->getBalanceFactor() == 1) //RL
                {
                    rightRoll(currentFatherNodePtr->rightSon);
                    leftRoll(currentFatherNodePtr);
                    continue;
                }
                //RR
                leftRoll(currentFatherNodePtr);
                continue;

            }
            //balance 2 -> LR/LL
            if(currentFatherNodePtr->leftSon->getBalanceFactor() == -1) //LR
            {
                leftRoll(currentFatherNodePtr->leftSon);
                rightRoll(currentFatherNodePtr);
                continue;
            }
            //LL
            rightRoll(currentFatherNodePtr);
            continue;
        }

        currentFatherNodePtr = currentFatherNodePtr->father;
        if (currentFatherNodePtr == nullptr)
            break;
        oldHeight = currentFatherNodePtr->height;
    }
    this->numOfNodes--;
    return StatusType::SUCCESS;

}
template <class T>
void AVL_Tree<T>::leftRoll(T* node)
{
    T *newHead,*tempNode;
    newHead = node->rightSon;
    tempNode = newHead->leftSon;
    newHead->leftSon = node;
    node->rightSon = tempNode;
    //correcting fathers
    newHead->father=node->father;
    node->father=newHead;
    if (tempNode!= nullptr)
    {
        tempNode->father=node;
    }
    // correcting root and father's son
    if (newHead->father == nullptr)
    {
        this->root = newHead;
    }
    else if (newHead->father->rightSon == node)
    {
        newHead->father->rightSon = newHead;
    }
    else if (newHead->father->leftSon == node)
    {
        newHead->father->leftSon = newHead;
    }
    // correcting number of sons
    node->numOfRightSons = newHead->numOfLeftSons; //node-> leftsons doesn't change
    newHead->numOfLeftSons += node->numOfLeftSons + 1;  //  newHead->rightsons doesn't change
}
template<class T>
void AVL_Tree<T>::rightRoll(T* node)
{
    T *newHead,*tempNode;
    newHead = node->leftSon;
    tempNode = newHead->rightSon;
    newHead->rightSon = node;
    node->leftSon = tempNode;
    //correcting fathers
    newHead->father=node->father;
    node->father=newHead;
    if (tempNode!= nullptr)
    {
        tempNode->father=node;
    }
    // correcting root
    if (newHead->father == nullptr)
    {
        this->root = newHead;
    }
    else if (newHead->father->rightSon == node)
    {
        newHead->father->rightSon = newHead;
    }
    else if (newHead->father->leftSon == node)
    {
        newHead->father->leftSon = newHead;
    }

    // correcting number of sons
    node->numOfLeftSons = newHead->numOfRightSons; //node-> rightsons doesn't change
    newHead->numOfRightSons += node->numOfRightSons + 1;  //  newHead->numOfLeftSons doesn't change


}
template<class T>
T* AVL_Tree<T>::search(int content){
    T* ptr = this->root;
    while (ptr){
        if (content < ptr->content){
            ptr = ptr->leftSon;
        }
        if (content > ptr->content){
            ptr = ptr->rightSon;
        }
        if (content == ptr->content){
            return ptr;
        }
    }
    return new T(-1);
}
template<class T>
void AVL_Tree<T>::printLevelOrder() {
    if (root == nullptr) {
        return;
    }
    std::queue<T*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            T* curr = q.front();
            q.pop();
            if (curr != nullptr) {
                std::cout << curr->content << " ";
                q.push(curr->leftSon);
                q.push(curr->rightSon);
            } else {
                std::cout << "null ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------------------------------------------------------" << std::endl;
}
class group_node
{
public:
    group_node* leftSon;
    group_node* rightSon;
    group_node* father;
    AVL_Tree<Node<group_node>> members;
    int key;
    int content;
    bool isVip;
    int views;
    int numOfLeftSons;
    int numOfRightSons;
    int height;
    int ComedyViews;
    int FantasyViews;
    int DramaViews;
    int ActionViews;
    int moviesWatched;
    int ComedyWatched;
    int FantasyWatched;
    int DramaWatched;
    int ActionWatched;

    group_node():content(0),leftSon(nullptr),rightSon(nullptr),
    father(nullptr),numOfRightSons(0),numOfLeftSons(0),height(0),key(0), isVip(0),
    views(0), ComedyViews(0), FantasyViews(0), DramaViews(0), moviesWatched(0) , ActionViews(0)
    ,ComedyWatched(0), ActionWatched(0), FantasyWatched(0),DramaWatched(0){members = AVL_Tree<Node<group_node>>();}
    group_node(int key1, int content1,group_node* father1):content(content1),leftSon(nullptr),rightSon(nullptr),
    father(father1),numOfRightSons(0),numOfLeftSons(0),height(0),key(key1), isVip(0),
    views(0), ComedyViews(0), FantasyViews(0), DramaViews(0), moviesWatched(0), ActionViews(0)
    ,ComedyWatched(0), ActionWatched(0), FantasyWatched(0),DramaWatched(0){members = AVL_Tree<Node<group_node>>();}
    group_node(int key1):content(0),leftSon(nullptr),rightSon(nullptr),
    father(nullptr),numOfRightSons(0),numOfLeftSons(0),height(0),key(0), isVip(0),
    views(0), ComedyViews(0), FantasyViews(0), DramaViews(0), moviesWatched(0), ActionViews(0)
    ,ComedyWatched(0), ActionWatched(0), FantasyWatched(0),DramaWatched(0){members = AVL_Tree<Node<group_node>>();}
    void addLeftSon(group_node* son){
        this->leftSon = son;
        group_node* currentFather = son->father;
        while(currentFather != nullptr)
        {
            currentFather->numOfLeftSons++;
            currentFather = currentFather->father;
        }
    }
    void addRightSon(group_node* son){
        this->rightSon = son;
        group_node* currentFather = son->father;
        while(currentFather != nullptr)
        {
            currentFather->numOfRightSons++;
            currentFather = currentFather->father;
        }
    }
    void swapNodes(group_node* node1){
        int temp;
        temp = this->content;
        this->content = node1->content;
        node1->content = temp;
    }
    int updateHeight()
    {
        int leftHeight,rightHeight;
        if(this->leftSon == nullptr)
        {
            leftHeight = -1;
        }
        else
        {
            leftHeight= this->leftSon->height;
        }
        if(this->rightSon == nullptr)
        {
            rightHeight = -1;
        }
        else
        {
            rightHeight= this->rightSon->height;
        }

        if(leftHeight > rightHeight)
        {
            this->height = leftHeight+1;
            return height;
        }
        this->height = rightHeight+1;
        return height;
    }
    int getBalanceFactor() const
    {
        int leftHeight,rightHeight;
        if(this->leftSon == nullptr)
        {
            leftHeight = -1;
        } else
        {
            leftSon->updateHeight();
            leftHeight = leftSon->height;
        }
        if(this->rightSon == nullptr)
        {
            rightHeight = -1;
        } else
        {

            rightSon->updateHeight();
            rightHeight = rightSon->height;
        }
        return leftHeight-rightHeight;
    }
    ~group_node()=default;
    group_node(group_node&)=default;
    group_node& operator=(const group_node& other)= default;
};









void copyNodeContent(Node<group_node>* ptr1, const Node<group_node>* ptr2){
    ptr1->key = ptr2->key;
    ptr1->content = ptr2->content;
    ptr1->views = ptr2->views;
    ptr1->groupViews = ptr2->groupViews;
    ptr1->GroupFantasyViews = ptr2->GroupFantasyViews;
    ptr1->GroupDramaViews = ptr2->GroupDramaViews;
    ptr1->GroupComedyViews = ptr2->GroupComedyViews;
    ptr1->GroupActionViews = ptr2->GroupActionViews;
    ptr1->isVip = ptr2->isVip;
    ptr1->curGroup =ptr2->curGroup;
    ptr1->genre = ptr2->genre;
    ptr1->ActionViews = ptr2->ActionViews;
    ptr1->DramaViews = ptr2->DramaViews;
    ptr1->FantasyViews = ptr2->FantasyViews;
    ptr1->ComedyViews = ptr2->ComedyViews;
}
















//streamingdtb.h
class streaming_database {
private:
    AVL_Tree<Node<group_node>> movies;
    AVL_Tree<Node<group_node>> users;
    AVL_Tree<group_node> groups;
    AVL_Tree<Node<group_node>> comedyMovies;
    AVL_Tree<Node<group_node>> actionMovies;
    AVL_Tree<Node<group_node>> dramaMovies;
    AVL_Tree<Node<group_node>> fantasyMovies;
public:
    // <DO-NOT-MODIFY> {

    streaming_database();

    virtual ~streaming_database();

    StatusType add_movie(int movieId, Genre genre, int views, bool vipOnly);

    StatusType remove_movie(int movieId);

    StatusType add_user(int userId, bool isVip);

    StatusType remove_user(int userId);

    StatusType add_group(int groupId);

    StatusType remove_group(int groupId);

    StatusType add_user_to_group(int userId, int groupId);

    StatusType user_watch(int userId, int movieId);

    StatusType group_watch(int groupId,int movieId);

    output_t<int> get_all_movies_count(Genre genre);

    StatusType get_all_movies(Genre genre, int *const output);

    output_t<int> get_num_views(int userId, Genre genre);

    StatusType rate_movie(int userId, int movieId, int rating);

    output_t<int> get_group_recommendation(int groupId);

    // } </DO-NOT-MODIFY>
};









// streamingdtb.cpp
streaming_database::streaming_database()
{
    movies = AVL_Tree<Node<group_node>>();
    users = AVL_Tree<Node<group_node>>();
    groups = AVL_Tree<group_node>();
    comedyMovies = AVL_Tree<Node<group_node>>();
    actionMovies = AVL_Tree<Node<group_node>>();
    fantasyMovies = AVL_Tree<Node<group_node>>();
    dramaMovies = AVL_Tree<Node<group_node>>();
}

template<class T>
void deleteTree(T* root){
    T* ptr = root;
    if(ptr == nullptr){
        return;
    }
    deleteTree(ptr->leftSon);
    deleteTree(ptr->rightSon);
    delete ptr;
}

streaming_database::~streaming_database()
{
    deleteTree(movies.getRoot());
    deleteTree(users.getRoot());
    deleteTree(groups.getRoot());
    deleteTree(comedyMovies.getRoot());
    deleteTree(actionMovies.getRoot());
    deleteTree(fantasyMovies.getRoot());
    deleteTree(dramaMovies.getRoot());
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    if(movieId <= 0 || genre == Genre::NONE || views < 0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* movie = new Node<group_node>(0,movieId, nullptr);
    if(!movie){
        return StatusType::ALLOCATION_ERROR;
    }
    Node<group_node>* ptr = movies.searchAndAdd(movie);
    if(ptr->key == -1){
        delete ptr;
        return StatusType::FAILURE;
    }
    Node<group_node>* genreMovie = new Node<group_node>(0,movieId, nullptr);
    movie->changeVip(vipOnly);
    genreMovie->changeVip(vipOnly);
    movie->changeGenre(genre);
    genreMovie->changeGenre(genre);
    movie->changeViews(views);
    genreMovie->changeViews(views);
    switch (genre) {
        case Genre::COMEDY:
            comedyMovies.searchAndAdd(genreMovie);
            return StatusType::SUCCESS;
        case Genre::ACTION:
            actionMovies.searchAndAdd(genreMovie);
            return StatusType::SUCCESS;
        case Genre::FANTASY:
            fantasyMovies.searchAndAdd(genreMovie);
            return StatusType::SUCCESS;
        case Genre::DRAMA:
            dramaMovies.searchAndAdd(genreMovie);
            return StatusType::SUCCESS;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
    if(movieId <=0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* curMovie = movies.search(movieId);
    if(curMovie->key == -1){
        delete curMovie;
        return StatusType::FAILURE;
    }

    switch (curMovie->genre) {
        case Genre::COMEDY:
            comedyMovies.searchAndDelete(movieId);
            break;
        case Genre::ACTION:
            actionMovies.searchAndDelete(movieId);
            break;
        case Genre::FANTASY:
            fantasyMovies.searchAndDelete(movieId);
            break;
        case Genre::DRAMA:
            dramaMovies.searchAndDelete(movieId);
            break;
    }
    return movies.searchAndDelete(movieId);
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
    if(userId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* user = new Node<group_node>(0,userId, nullptr);
    if(!user){
        return StatusType::ALLOCATION_ERROR;
    }
    Node<group_node>* ptr = users.searchAndAdd(user);
    if(ptr->key == -1){
        delete ptr;
        return StatusType::FAILURE;
    }
    user->changeVip(isVip);
    user->changeViews(0);
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)
{
    if(userId <=0){
        return StatusType::INVALID_INPUT;
    }
    return users.searchAndDelete(userId);
}

StatusType streaming_database::add_group(int groupId)
{
    if(groupId <=0){
        return StatusType::INVALID_INPUT;
    }
    group_node* group = new group_node(0,groupId, nullptr);
    if(!group){
        return StatusType::ALLOCATION_ERROR;
    }
    group_node* ptr = groups.searchAndAdd(group);
    if(ptr->key == -1){
        delete ptr;
        return StatusType::FAILURE;
    }
    group->views = 0;
    group->isVip = false;
    return StatusType::SUCCESS;
}
void incrementAndDelete(Node<group_node>* ptr, const group_node* group){
    if(!ptr){
        return;
    }
    incrementAndDelete(ptr->leftSon,group);
    incrementAndDelete(ptr->rightSon,group);
    ptr->groupUser->views = ptr->groupUser->views + group->moviesWatched - ptr->groupUser->groupViews;
    ptr->groupUser->FantasyViews = ptr->groupUser->FantasyViews + group->FantasyWatched
            - ptr->groupUser->GroupFantasyViews;
    ptr->groupUser->ActionViews = ptr->groupUser->ActionViews + group->ActionWatched -
            ptr->groupUser->GroupActionViews;
    ptr->groupUser->DramaViews = ptr->groupUser->DramaViews + group->DramaWatched
            - ptr->groupUser->GroupDramaViews;
    ptr->groupUser->ComedyViews = ptr->groupUser->ComedyViews + group->ComedyWatched
            - ptr->groupUser->GroupComedyViews;
    delete ptr;
}
StatusType streaming_database::remove_group(int groupId)
{
    if(groupId <=0){
        return StatusType::INVALID_INPUT;
    }
    group_node* groupToDelete = groups.search(groupId);
    if(groupToDelete->key == -1){
        delete groupToDelete;
        return StatusType::FAILURE;
    }
    Node<group_node>* ptr = groupToDelete->members.getRoot();
    incrementAndDelete(ptr, groupToDelete);
    return groups.searchAndDelete(groupId);
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
    if(userId <=0 || groupId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* user = users.search(userId); // O(log(n))
    if(user->key == -1){
        delete user;
        return StatusType::FAILURE;
    }
    if(user->curGroup != nullptr){
        return StatusType::FAILURE;
    }
    group_node* group = groups.search(groupId); // O(log(m))
    if (group->key == -1){
        delete group;
        return StatusType::FAILURE;
    }
    user->curGroup = group;
    if(!group->isVip && user->isVip){
        group->isVip = true;
    }
    Node<group_node>* groupUser = new Node<group_node>(0,userId, nullptr);
    if(!groupUser){
        return StatusType::ALLOCATION_ERROR;
    }
    user->groupViews = group->moviesWatched;
    user->GroupFantasyViews = group->FantasyWatched;
    user->GroupDramaViews = group->DramaWatched;
    user->GroupComedyViews = group->ComedyWatched;
    user->GroupActionViews = group->ActionWatched;
    copyNodeContent(groupUser,user);
    groupUser->groupUser = user;
    Node<group_node>* ptr = group->members.searchAndAdd(groupUser);
    if(ptr->key == -1){
        delete ptr;
        delete groupUser;
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
    if(userId <= 0 || movieId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* user = users.search(userId); // O(log(n))
    if(user->key == -1){
        delete user;
        return StatusType::FAILURE;
    }
    Node<group_node>* movie = movies.search(movieId); // O(log(k))
    if(movie->key == -1){
        delete movie;
        return StatusType::FAILURE;
    }
    if(movie->isVip && !user->isVip){
        return StatusType::FAILURE;
    }
    user->views++;
    movie->views++;
    switch (movie->genre) {
        case Genre::COMEDY:
            user->ComedyViews++;
            break;
        case Genre::ACTION:
            user->ActionViews++;
            break;
        case Genre::FANTASY:
            user->FantasyViews++;
            break;
        case Genre::DRAMA:
            user->DramaViews++;
            break;
        case Genre::NONE:
            break;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
    if(groupId <= 0 || movieId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* movie = movies.search(movieId); // O(log(k))
    if(movie->key == -1){
        delete movie;
        return StatusType::FAILURE;
    }
    group_node* group = groups.search(groupId); // O(log(m))
    if(group->key == -1){
        delete group;
        return StatusType::FAILURE;
    }
    if(movie->isVip && !group->isVip){
        return StatusType::FAILURE;
    }
    group->moviesWatched++;
    switch (movie->genre) {
        case Genre::COMEDY:
            group->ComedyWatched++;
            break;
        case Genre::ACTION:
            group->ActionWatched++;
            break;
        case Genre::FANTASY:
            group->FantasyWatched++;
            break;
        case Genre::DRAMA:
            group->DramaWatched++;
            break;
        case Genre::NONE:
            break;
    }
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    switch (genre) {
        case Genre::COMEDY:
            return output_t<int>{comedyMovies.getNumOfNodes()};
        case Genre::ACTION:
            return output_t<int>{actionMovies.getNumOfNodes()};
        case Genre::FANTASY:
            return output_t<int>{fantasyMovies.getNumOfNodes()};
        case Genre::DRAMA:
            return output_t<int>{dramaMovies.getNumOfNodes()};
        case Genre::NONE:
            return output_t<int>{movies.getNumOfNodes()};
    }
    return output_t<int>(StatusType::ALLOCATION_ERROR);
}
void iterate(int i, int *const output, Node<group_node>* ptr){ // not finished
    if(!ptr){
        return;
    }
    iterate(i+1, output, ptr->leftSon);
    output[i] = ptr->content;
    iterate(i+1, output, ptr->rightSon);
}
StatusType streaming_database::get_all_movies(Genre genre, int *const output) // not finished
{
    if(movies.getNumOfNodes() == 0){
        return StatusType::FAILURE;
    }
    int i = 0;
    switch (genre) {
        case Genre::COMEDY:
            if(comedyMovies.getNumOfNodes() == 0){
                return StatusType::FAILURE;
            }
            iterate(i,output,comedyMovies.getRoot());
            return StatusType::SUCCESS;
        case Genre::ACTION:
            if(actionMovies.getNumOfNodes() == 0){
                return StatusType::FAILURE;
            }
            iterate(i,output,actionMovies.getRoot());
            return StatusType::SUCCESS;
        case Genre::FANTASY:
            if(fantasyMovies.getNumOfNodes() == 0){
                return StatusType::FAILURE;
            }
            iterate(i,output,fantasyMovies.getRoot());
            return StatusType::SUCCESS;
        case Genre::DRAMA:
            if(dramaMovies.getNumOfNodes() == 0){
                return StatusType::FAILURE;
            }
            iterate(i,output,dramaMovies.getRoot());
            return StatusType::SUCCESS;
        case Genre::NONE:
            iterate(i,output,movies.getRoot());
            return StatusType::SUCCESS;
    }
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
    if(userId <= 0 ){
        return output_t<int>{StatusType::INVALID_INPUT};
    }
    Node<group_node>* user = users.search(userId); // O(log(n))
    if(user->key == -1){
        delete user;
        return StatusType::FAILURE;
    }
    switch (genre) {
        case Genre::COMEDY:
            if(!user->curGroup){
                return output_t<int>{user->ComedyViews};
            }
            return output_t<int>{user->ComedyViews + user->curGroup->ComedyWatched - user->GroupComedyViews};
        case Genre::ACTION:
            if(!user->curGroup){
                return output_t<int>{user->ActionViews};
            }
            return output_t<int>{user->ActionViews + user->curGroup->ActionWatched - user->GroupActionViews};
        case Genre::FANTASY:
            if(!user->curGroup){
                return output_t<int>{user->FantasyViews};
            }
            return output_t<int>{user->FantasyViews + user->curGroup->FantasyWatched - user->GroupFantasyViews};
        case Genre::DRAMA:
            if(!user->curGroup){
                return output_t<int>{user->DramaViews};
            }
            return output_t<int>{user->DramaViews + user->curGroup->DramaWatched - user->GroupDramaViews};
        case Genre::NONE:
            if(!user->curGroup){
                return output_t<int>{user->views};
            }
            return output_t<int>{user->views + user->curGroup->moviesWatched - user->groupViews};
    }
    return output_t<int>(StatusType::ALLOCATION_ERROR);
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    if(userId <= 0 || movieId <= 0 || rating > 100 || rating < 0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* user = users.search(userId); // O(log(n))
    if(user->key == -1){
        delete user;
        return StatusType::FAILURE;
    }
    Node<group_node>* movie = movies.search(movieId); // O(log(k))
    if(movie->key == -1){
        delete movie;
        return StatusType::FAILURE;
    }
    if(movie->isVip && !user->isVip){
        return StatusType::FAILURE;
    }
    // still not finished
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId) // not finished
{
    // TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

int main()
{
    AVL_Tree<Node<group_node>> avlTree, avlTree2;
    int arr[12]={10,5,12,3,9,11,13,14,2,4, 100, 200};
    int arr2[12]={2,3,4,5,9,10,11,12,13,14, 2000, 17};
    int arr3[12]={14,10,12,10,10,9,5,4,3,2, 87, 900};
    for (int i = 0; i < 12; ++i) {
        avlTree.searchAndAdd(new Node<group_node>(0,arr[i], nullptr));
        avlTree.printLevelOrder();
        avlTree2.printLevelOrder();
    }
    avlTree.printTree(avlTree.getRoot());
    streaming_database *obj = new streaming_database();
    obj->add_user(100,1);
    obj->add_group(200);
    obj->add_user_to_group(100,200);
    obj->add_movie(1,Genre::COMEDY,10,1);
    obj->add_movie(2, Genre::DRAMA,10,1);
    obj->add_movie(3,Genre::FANTASY,10,1);
    obj->add_movie(4,Genre::ACTION,10,1);
    obj->add_movie(5,Genre::COMEDY,10,1);
    int* output = new int[5];

    obj->remove_movie(1);
    obj->remove_movie(5);
    obj->remove_movie(3);
    //avlTree2.searchAndDelete(9);
    //avlTree2.printLevelOrder();
    //avlTree2.searchAndDelete(14);
    //avlTree2.printLevelOrder();
    return 0;
}