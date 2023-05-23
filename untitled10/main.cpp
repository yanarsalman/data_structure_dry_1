#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <queue>
#include <fstream>

//utilty

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







template<class T>
class Node {
public:
    int content;
    bool isVip;
    int views;
    int ComedyViews;
    int FantasyViews;
    int DramaViews;
    int moviesWatched;
    int ActionViews;
    int ComedyWatched;
    int ActionWatched;
    int FantasyWatched;
    int DramaWatched;
    double rating;
    int groupViews;
    int GroupFantasyViews;
    int GroupDramaViews;
    int GroupComedyViews;
    int GroupActionViews;
    Genre genre;
    int usersRated;
    
    Node<T>* leftSon;
    Node<T>* rightSon;
    T* curGroup;
    Node<T>* groupUser;
    
    Node<T>() {
        content = 0;
        isVip = false;
        views = 0;
        ComedyViews = 0;
        FantasyViews = 0;
        DramaViews = 0;
        moviesWatched = 0;
        ActionViews = 0;
        ComedyWatched = 0;
        ActionWatched = 0;
        FantasyWatched = 0;
        FantasyWatched = 0;
        DramaWatched = 0;
        leftSon = nullptr;
        rightSon = nullptr;
        curGroup = nullptr;
        groupViews = 0;
        GroupFantasyViews = 0;
        GroupDramaViews = 0;
        GroupComedyViews = 0;
        GroupActionViews = 0;
        genre = Genre::NONE;
        groupUser = nullptr;
        usersRated = 0;
        rating = 0;
    }
    Node<T>(int content1) {
        content = content1;
        isVip = false;
        views = 0;
        ComedyViews = 0;
        FantasyViews = 0;
        DramaViews = 0;
        moviesWatched = 0;
        ActionViews = 0;
        ComedyWatched = 0;
        ActionWatched = 0;
        FantasyWatched = 0;
        FantasyWatched = 0;
        DramaWatched = 0;
        leftSon = nullptr;
        rightSon = nullptr;
        curGroup = nullptr;
        groupViews = 0;
        GroupFantasyViews = 0;
        GroupDramaViews = 0;
        GroupComedyViews = 0;
        GroupActionViews = 0;
        genre = Genre::NONE;
        groupUser = nullptr;
        usersRated = 0;
        rating = 0;
    }
    Node& operator=(const Node<T>& other){
        content = other.content;
        isVip = other.isVip;
        views = other.views;
        ComedyViews = other.ComedyViews;
        FantasyViews = other.FantasyViews;
        DramaViews = other.DramaViews;
        moviesWatched = other.moviesWatched;
        ActionViews = other.ActionViews;
        ComedyWatched = other.ComedyWatched;
        ActionWatched = other.ActionWatched;
        FantasyWatched = other.FantasyWatched;
        DramaWatched = other.DramaWatched;
        leftSon = other.leftSon;
        rightSon = other.rightSon;
        curGroup = other.curGroup;
        groupViews = other.groupViews;
        GroupFantasyViews = other.GroupFantasyViews;
        GroupDramaViews = other.GroupDramaViews;
        GroupComedyViews = other.GroupComedyViews;
        GroupActionViews = other.GroupActionViews;
        genre = other.genre;
        groupUser = other.groupUser;
        usersRated = other.usersRated;
        rating = 0;
    }
};

template <class T>
void copyNodeContent(T* ptr1, const T* ptr2){
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
    ptr1->rating = ptr2->rating;
}







template<class T>
class AVL_Tree {
public:
    T* root;
    int numberOfNodes;
    AVL_Tree() {
        root = nullptr;
        numberOfNodes = 0;
    }
    int getHeight(T* r) {
        if (r == nullptr)
            return -1;
        else {
            int leftHeight = getHeight(r -> leftSon);
            int rightHeight = getHeight(r -> rightSon);
            
            if (leftHeight > rightHeight)
                return (leftHeight + 1);
            else return (rightHeight + 1);
        }
    }

    int getBalanceFactor(T* n) {
        if (n == nullptr)
            return -1;
        return getHeight(n -> leftSon) - getHeight(n -> rightSon);
    }

    T* rightRotate(T* ptr) {
        T* temp = ptr -> leftSon;
        T* temp2 = temp -> rightSon;
        temp -> rightSon = ptr;
        ptr -> leftSon = temp2;

        return temp;
    }

    T* leftRotate(T* ptr) {
        T* temp = ptr -> rightSon;
        T* temp2 = temp -> leftSon;
        temp -> leftSon = ptr;
        ptr -> rightSon = temp2;

        return temp;
    }

    T* searchAndAdd(T* Root, T* toInsert, StatusType& status) {
        if (Root == nullptr) {
            Root = toInsert;
            numberOfNodes++;
            return Root;
        }

        if (toInsert -> content < Root -> content) {
            Root -> leftSon = searchAndAdd(Root -> leftSon, toInsert,status);
        } else if (toInsert -> content > Root -> content) {
            Root -> rightSon = searchAndAdd(Root -> rightSon, toInsert,status);
        } else {
            status = StatusType::FAILURE;
            return Root;
        }

        int bf = getBalanceFactor(Root);
        // Left Left Case  
        if (bf > 1 && toInsert->content < Root->leftSon->content)
            return rightRotate(Root);

        // Right Right Case  
        if (bf < -1 && toInsert->content > Root->rightSon->content)
            return leftRotate(Root);

        // Left Right Case  
        if (bf > 1 && toInsert->content > Root->leftSon->content) {
            Root->leftSon = leftRotate(Root->leftSon);
            return rightRotate(Root);
        }

        // Right Left Case  
        if (bf < -1 && toInsert->content < Root->rightSon->content) {
            Root->rightSon = rightRotate(Root->rightSon);
            return leftRotate(Root);
        }
        return Root;

    }
    T* searchAndAddRating(T* Root, T* toInsert, StatusType& status) {
        if (Root == nullptr) {
            Root = toInsert;
            numberOfNodes++;
            return Root;
        }

        if (toInsert->rating < Root->rating) {
            Root->leftSon = searchAndAdd(Root->leftSon, toInsert,status);
        } else if (toInsert->rating > Root->rating) {
            Root->rightSon = searchAndAdd(Root->rightSon, toInsert,status);
        } else if (toInsert->views < Root->views) {
            Root->rightSon = searchAndAdd(Root->leftSon, toInsert,status);
        } else if (toInsert->views > Root->views) {
            Root->rightSon = searchAndAdd(Root->rightSon, toInsert,status);
        } else if (toInsert->content > Root->content) {
            Root -> rightSon = searchAndAdd(Root -> leftSon, toInsert,status);
        } else if (toInsert -> content < Root -> content) {
            Root -> rightSon = searchAndAdd(Root -> rightSon, toInsert,status);
        } else {
            status = StatusType::FAILURE;
            return Root;
        }

        int bf = getBalanceFactor(Root);

        if (bf > 1){
            if(toInsert->rating < Root->leftSon->rating){
                return rightRotate(Root);
            }
            if(toInsert->rating > Root->leftSon->rating){
                Root->leftSon = leftRotate(Root->leftSon);
                return rightRotate(Root);
            }
            if(toInsert->views < Root->leftSon->views){
                return rightRotate(Root);
            }
            if(toInsert->views > Root->leftSon->views){
                Root->leftSon = leftRotate(Root->leftSon);
                return rightRotate(Root);
            }
            if(toInsert->content > Root->leftSon->content){
                return rightRotate(Root);
            }
            if(toInsert->content < Root->leftSon->content){
                Root->leftSon = leftRotate(Root->leftSon);
                return rightRotate(Root);
            }
        }
        if(bf < -1){
            if(toInsert->rating > Root->rightSon->rating){
                return leftRotate(Root);
            }
            if(toInsert->rating < Root->rightSon->rating){
                Root->rightSon = rightRotate(Root->rightSon);
                return leftRotate(Root);
            }
            if(toInsert->views > Root->rightSon->views){
                return leftRotate(Root);
            }
            if(toInsert->views < Root->rightSon->views){
                Root->rightSon = rightRotate(Root->rightSon);
                return leftRotate(Root);
            }
            if(toInsert->content < Root->rightSon->content){
                return leftRotate(Root);
            }
            if(toInsert->content > Root->rightSon->content){
                Root->rightSon = rightRotate(Root->rightSon);
                return leftRotate(Root);
            }
        }
        return Root;

    }

    T* getMin(T* node) {
        T* current = node;
        if(!current){
            return nullptr;
        }
        while (current -> leftSon != nullptr) {
            current = current -> leftSon;
        }
        return current;
    }
    T* getMax() {
        T* current = root;
        if(!current){
            return nullptr;
        }
        while (current->rightSon != nullptr) {
            current = current->rightSon;
        }
        return current;
    }

    T* searchAndDelete(T* node, int content, StatusType& status) {
        if (node == nullptr) {
            status = StatusType::FAILURE;
            return nullptr;
        }
        else if (content < node -> content) {
            node -> leftSon = searchAndDelete(node -> leftSon, content, status);
        }
        else if (content > node -> content) {
            node -> rightSon = searchAndDelete(node -> rightSon, content, status);
        }
        else {
            // node with only one child or no child 
            if (node -> leftSon == nullptr) {
                T* temp = node -> rightSon;
                delete node;
                numberOfNodes--;
                return temp;
            } else if (node -> rightSon == nullptr) {
                T* temp = node -> leftSon;
                delete node;
                numberOfNodes--;
                return temp;
            } else {
                T* temp = getMin(node -> rightSon);
                copyNodeContent(node, temp);
                node->rightSon = searchAndDelete(node -> rightSon, temp -> content,status);
            }
        }

        int bf = getBalanceFactor(node);
        // Left Left Imbalance/Case or Right rotation 
        if (bf == 2 && getBalanceFactor(node -> leftSon) >= 0)
            return rightRotate(node);
            // Left Right Imbalance/Case or LR rotation 
        else if (bf == 2 && getBalanceFactor(node -> leftSon) == -1) {
            node -> leftSon = leftRotate(node -> leftSon);
            return rightRotate(node);
        }
            // Right Right Imbalance/Case or Left rotation	
        else if (bf == -2 && getBalanceFactor(node -> rightSon) <= 0)
            return leftRotate(node);
            // Right Left Imbalance/Case or RL rotation 
        else if (bf == -2 && getBalanceFactor(node -> rightSon) == 1) {
            node -> rightSon = rightRotate(node -> rightSon);
            return leftRotate(node);
        }
        return node;
    }

    T* searchAndDeleteRating(T* node, T* toDelete, StatusType& status) {
        if (node == nullptr) {
            status = StatusType::FAILURE;
            return nullptr;
        }
        else if (toDelete->rating < node->rating) {
            node->leftSon = searchAndDeleteRating(node->leftSon, toDelete, status);
        }
        else if (toDelete->rating > node->rating) {
            node->rightSon = searchAndDeleteRating(node->rightSon, toDelete,status);
        }
        else if (toDelete->views < node->views) {
            node->rightSon = searchAndDeleteRating(node->leftSon, toDelete,status);
        }
        else if (toDelete->views > node->views) {
            node->rightSon = searchAndDeleteRating(node->rightSon, toDelete,status);
        }
        else if (toDelete->content > node->content) {
            node->rightSon = searchAndDeleteRating(node->leftSon, toDelete,status);
        }
        else if (toDelete->content < node->content) {
            node->rightSon = searchAndDeleteRating(node->rightSon, toDelete,status);
        }
        else {
            // node with only one child or no child 
            if (node -> leftSon == nullptr) {
                T* temp = node -> rightSon;
                delete node;
                numberOfNodes--;
                return temp;
            } else if (node -> rightSon == nullptr) {
                T* temp = node -> leftSon;
                delete node;
                numberOfNodes--;
                return temp;
            } else {
                // node with two children: Get the inorder successor (smallest 
                // in the right subtree) 
                T* temp = getMin(node -> rightSon);
                // Copy the inorder successor's content to this node
                copyNodeContent(node, temp);
                // Delete the inorder successor 
                node->rightSon = searchAndDelete(node -> rightSon, temp -> content,status);
                //searchAndDelete(r->rightSon, temp->content); 
            }
        }

        int bf = getBalanceFactor(node);
        // Left Left Imbalance/Case or Right rotation 
        if (bf == 2 && getBalanceFactor(node -> leftSon) >= 0)
            return rightRotate(node);
            // Left Right Imbalance/Case or LR rotation 
        else if (bf == 2 && getBalanceFactor(node -> leftSon) == -1) {
            node -> leftSon = leftRotate(node -> leftSon);
            return rightRotate(node);
        }
            // Right Right Imbalance/Case or Left rotation	
        else if (bf == -2 && getBalanceFactor(node -> rightSon) <= 0)
            return leftRotate(node);
            // Right Left Imbalance/Case or RL rotation 
        else if (bf == -2 && getBalanceFactor(node -> rightSon) == 1) {
            node -> rightSon = rightRotate(node -> rightSon);
            return leftRotate(node);
        }
        return node;
    }




    T* search(int content) {
        T* ptr = root;
        while (ptr){
            if (content == ptr->content){
                return ptr;
            }
            if (content < ptr->content){
                ptr = ptr->leftSon;
                continue;
            }
            if (content > ptr->content){
                ptr = ptr->rightSon;
                continue;
            }
        }
        return ptr;
    }
    T* searchRating(T* node){
        T* ptr = root;
        while (ptr){
            if(ptr->content == node->content){
                return ptr;
            }
            if (node->rating < ptr->rating){
                ptr = ptr->leftSon;
                continue;
            }
            if (node->rating > ptr->rating){
                ptr = ptr->rightSon;
                continue;
            }
            if(node->views < ptr->views){
                ptr = ptr->leftSon;
                continue;
            }
            if (node->views > ptr->views){
                ptr = ptr->rightSon;
                continue;
            }
            if(node->content < ptr->content){
                ptr = ptr->leftSon;
                continue;
            }
            if (node->content > ptr->content){
                ptr = ptr->rightSon;
                continue;
            }
        }
        return ptr;
    }
};















































//group_node
class group_node
{
public:
    int content;
    group_node* leftSon;
    group_node* rightSon;
    int numOfRightSons;
    int numOfLeftSons;
    bool isVip;
    int views;
    int ComedyViews;
    int FantasyViews;
    int DramaViews;
    int moviesWatched;
    int ActionViews;
    int ComedyWatched;
    int ActionWatched;
    int FantasyWatched;
    int DramaWatched;
    AVL_Tree<Node<group_node>> members;
    Genre genre;
    int groupViews;
    int GroupFantasyViews;
    int GroupDramaViews;
    int GroupComedyViews;
    int GroupActionViews;
    int curGroup;
    int rating;

    group_node():content(0),leftSon(nullptr),rightSon(nullptr)
        ,numOfRightSons(0),numOfLeftSons(0), isVip(false),
        views(0), ComedyViews(0), FantasyViews(0), DramaViews(0), moviesWatched(0) , ActionViews(0)
        ,ComedyWatched(0), ActionWatched(0), FantasyWatched(0),DramaWatched(0)
    {members = AVL_Tree<Node<group_node>>();}
    group_node(int content):content(content),leftSon(nullptr),rightSon(nullptr)
        ,numOfRightSons(0),numOfLeftSons(0), isVip(false),
        views(0), ComedyViews(0), FantasyViews(0), DramaViews(0), moviesWatched(0), ActionViews(0)
        ,ComedyWatched(0), ActionWatched(0), FantasyWatched(0),DramaWatched(0)
        {members = AVL_Tree<Node<group_node>>();}
    ~group_node()=default;
    group_node(group_node&)=default;
    group_node& operator=(const group_node& other)= default;
};

















//streamingdtb.h
class streaming_database {
private:
    AVL_Tree<Node<group_node>> users;
    AVL_Tree<group_node> groups;
    AVL_Tree<Node<group_node>> movies;
    AVL_Tree<Node<group_node>> comedyMovies;
    AVL_Tree<Node<group_node>> actionMovies;
    AVL_Tree<Node<group_node>> dramaMovies;
    AVL_Tree<Node<group_node>> fantasyMovies;
    AVL_Tree<Node<group_node>> moviesRating;
    Node<group_node>* maxRatingComedyMovie;
    Node<group_node>* maxRatingActionMovie;
    Node<group_node>* maxRatingDramaMovie;
    Node<group_node>* maxRatingFantasyMovie;



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
































//streamingddtb.cpp
streaming_database::streaming_database() : maxRatingActionMovie(nullptr), maxRatingDramaMovie(nullptr),
                                           maxRatingFantasyMovie(nullptr), maxRatingComedyMovie(nullptr)
{
    movies = AVL_Tree<Node<group_node>>();
    users = AVL_Tree<Node<group_node>>();
    groups = AVL_Tree<group_node>();
    comedyMovies = AVL_Tree<Node<group_node>>();
    actionMovies = AVL_Tree<Node<group_node>>();
    fantasyMovies = AVL_Tree<Node<group_node>>();
    dramaMovies = AVL_Tree<Node<group_node>>();
    moviesRating = AVL_Tree<Node<group_node>>();
}

int max_view_in_group(int action, int drama, int comedy, int fantasy) {
    if (action > comedy) {
        if (action > drama) {
            if (action >= fantasy) //action > fantasy > drama > comedy
            {
                return (int) Genre::ACTION;
            }
            return (int) Genre::FANTASY;//fantasy > action > drama > comedy
        }

        if (drama >= fantasy) {
            return (int) Genre::DRAMA; //drama > fantasy > action >  comedy
        }
        return (int) Genre::FANTASY; //fantasy > drama > action > comedy
    }
    if (comedy >= drama) {
        if (comedy >= fantasy) //comedy > fantasy > drama > action
        {
            return (int) Genre::COMEDY;
        }
        return (int) Genre::FANTASY;//fantasy > action > drama > comedy
    }
    if (drama >= fantasy)
        return (int) Genre::DRAMA;
    return (int) Genre::FANTASY;
}






template<class T>
void deleteTree(T* ptr){
    if(ptr == nullptr){
        return;
    }
    deleteTree(ptr->leftSon);
    deleteTree(ptr->rightSon);
    delete ptr;
    ptr = nullptr;
}

void deleteGroups(group_node* ptr){
    if(ptr == nullptr){
        return;
    }
    deleteGroups(ptr->leftSon);
    deleteGroups(ptr->rightSon);
    deleteTree(ptr->members.root);
    ptr->members.root = nullptr;
}



streaming_database::~streaming_database()
{
    deleteGroups(groups.root);
    deleteTree(users.root);
    users.root = nullptr;
    deleteTree(groups.root);
    groups.root = nullptr;
    deleteTree(movies.root);
    movies.root = nullptr;
    deleteTree(comedyMovies.root);
    comedyMovies.root = nullptr;
    deleteTree(actionMovies.root);
    actionMovies.root = nullptr;
    deleteTree(fantasyMovies.root);
    fantasyMovies.root = nullptr;
    deleteTree(dramaMovies.root);
    dramaMovies.root = nullptr;
    deleteTree(moviesRating.root);
    moviesRating.root = nullptr;
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    if(movieId <= 0 || genre == Genre::NONE || views < 0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* movie;
    movie = new Node<group_node>();
    movie->content = movieId;
    if(!movie){
        return StatusType::ALLOCATION_ERROR;
    }
    StatusType status = StatusType::SUCCESS;
    movies.root = movies.searchAndAdd(movies.root,movie,status);
    if(status != StatusType::SUCCESS){
        delete movie;
        return status;
    }
    Node<group_node>* genreMovie = new Node<group_node>();
    if(!genreMovie){
        movies.root = movies.searchAndDelete(movies.root, movie->content ,status);
        return StatusType::ALLOCATION_ERROR;
    }
    Node<group_node>* ratingMovie = new Node<group_node>();
    if(!ratingMovie){
        movies.root = movies.searchAndDelete(movies.root, movie->content ,status);
        delete genreMovie;
        return StatusType::ALLOCATION_ERROR;
    }
    movie->isVip = vipOnly;
    movie->genre = genre;
    movie->views = views;
    copyNodeContent(genreMovie, movie);
    copyNodeContent(ratingMovie, movie);
    moviesRating.root = moviesRating.searchAndAddRating(moviesRating.root,ratingMovie,status);
    //moviesRating.printLevelOrder();
    switch (genre) {
        case Genre::COMEDY:
            comedyMovies.root = comedyMovies.searchAndAddRating(comedyMovies.root,genreMovie, status);
            maxRatingComedyMovie = comedyMovies.getMax();
            return StatusType::SUCCESS;
        case Genre::ACTION:
            actionMovies.root = actionMovies.searchAndAddRating(actionMovies.root,genreMovie,status);
            maxRatingActionMovie = actionMovies.getMax();
            return StatusType::SUCCESS;
        case Genre::FANTASY:
            fantasyMovies.root = fantasyMovies.searchAndAddRating(fantasyMovies.root,genreMovie,status);
            maxRatingFantasyMovie = fantasyMovies.getMax();
            return StatusType::SUCCESS;
        case Genre::DRAMA:
            dramaMovies.root = dramaMovies.searchAndAddRating(dramaMovies.root,genreMovie,status);
            maxRatingDramaMovie = dramaMovies.getMax();
            return StatusType::SUCCESS;
        default:
            return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
    if(movieId <=0){
        return StatusType::INVALID_INPUT;
    }
    StatusType status = StatusType::SUCCESS;
    Node<group_node>* curMovie = movies.search(movieId);
    if(!curMovie){
        return StatusType::FAILURE;
    }
    moviesRating.root = moviesRating.searchAndDeleteRating(moviesRating.root,curMovie,status);
    if(status != StatusType::SUCCESS){
        return status;
    }
    switch (curMovie->genre){
        case Genre::COMEDY:
            comedyMovies.root = comedyMovies.searchAndDeleteRating(comedyMovies.root,curMovie,status);
            maxRatingComedyMovie = comedyMovies.getMax();
            break;
        case Genre::ACTION:
            actionMovies.root = actionMovies.searchAndDeleteRating(actionMovies.root,curMovie,status);
            maxRatingActionMovie = actionMovies.getMax();
            break;
        case Genre::FANTASY:
            fantasyMovies.root = fantasyMovies.searchAndDeleteRating(fantasyMovies.root,
                                                                     curMovie,status);
            maxRatingFantasyMovie = fantasyMovies.getMax();
            break;
        case Genre::DRAMA:
            dramaMovies.root = dramaMovies.searchAndDeleteRating(dramaMovies.root,curMovie,status);
            maxRatingDramaMovie = dramaMovies.getMax();
            break;
        default:
            return StatusType::FAILURE;
    }
    movies.root = movies.searchAndDelete(movies.root,movieId,status);
    return status;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
    if(userId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* user = new Node<group_node>(userId);
    if(!user){
        return StatusType::ALLOCATION_ERROR;
    }
    StatusType status = StatusType::SUCCESS;
    users.root = users.searchAndAdd(users.root,user,status);
    if(status != StatusType::SUCCESS){
        delete user;
        return status;
    }
    user->isVip = isVip;
    user->views = 0;
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)
{
    if(userId <=0){
        return StatusType::INVALID_INPUT;
    }
    StatusType status = StatusType::SUCCESS;
    Node<group_node>* user = users.search(userId); //O(log(n))
    if(!user){
        return StatusType::FAILURE;
    }
    if(user->curGroup)
    {
        user->curGroup->members.root = user->curGroup->members.searchAndDelete(user->curGroup->members.root
                ,userId,status); //O(log(n))
    }
    users.root = users.searchAndDelete(users.root,userId,status);
    return status;
}

StatusType streaming_database::add_group(int groupId)
{
    if(groupId <=0){
        return StatusType::INVALID_INPUT;
    }
    group_node* group = new group_node(groupId);
    if(!group){
        return StatusType::ALLOCATION_ERROR;
    }
    StatusType status = StatusType::SUCCESS;
    groups.root = groups.searchAndAdd(groups.root,group,status);
    if(status != StatusType::SUCCESS){
        delete group;
        return status;
    }
    group->views = 0;
    group->isVip = false;
    return StatusType::SUCCESS;
}

void incrementAndDelete(Node<group_node>* ptr, group_node* group){
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
    ptr->groupUser->curGroup = nullptr;
    delete ptr;
}
StatusType streaming_database::remove_group(int groupId)
{
    if(groupId <=0){
        return StatusType::INVALID_INPUT;
    }
    group_node* groupToDelete = groups.search(groupId);
    if(!groupToDelete){
        return StatusType::FAILURE;
    }
    Node<group_node>* ptr = groupToDelete->members.root;
    incrementAndDelete(ptr, groupToDelete);
    StatusType status = StatusType::SUCCESS;
    groups.root = groups.searchAndDelete(groups.root,groupId,status);
    return status;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
    if(userId <=0 || groupId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* user = users.search(userId); // O(log(n))
    if(!user){
        return StatusType::FAILURE;
    }
    if(user->curGroup != nullptr){
        return StatusType::FAILURE;
    }
    group_node* group = groups.search(groupId); // O(log(m))
    if(!group){
        return StatusType::FAILURE;
    }
    user->curGroup = group;
    if(!group->isVip && user->isVip){
        group->isVip = true;
    }
    Node<group_node>* groupUser = new Node<group_node>(userId);
    if(!groupUser){
        return StatusType::ALLOCATION_ERROR;
    }

    StatusType status = StatusType::SUCCESS;
    group->members.root = group->members.searchAndAdd(group->members.root,groupUser,status);
    if(status != StatusType::SUCCESS){
        delete groupUser;
        return status;
    }

    user->groupViews = group->moviesWatched;
    user->GroupFantasyViews = group->FantasyWatched;
    user->GroupDramaViews = group->DramaWatched;
    user->GroupComedyViews = group->ComedyWatched;
    user->GroupActionViews = group->ActionWatched;
    copyNodeContent(groupUser,user);
    groupUser->groupUser = user;
    user->groupUser = groupUser;
    group->views+=user->views;
    group->ComedyViews+= user->ComedyViews;
    group->DramaViews+= user->DramaViews;
    group->ActionViews+= user->ActionViews;
    group->FantasyViews+= user->FantasyViews;
    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
    if(userId <= 0 || movieId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* user = users.search(userId); // O(log(n))
    if(!user){
        return StatusType::FAILURE;
    }
    Node<group_node>* movie = movies.search(movieId); // O(log(k))
    if(!movie){
        return StatusType::FAILURE;
    }
    if(movie->isVip && !user->isVip){
        return StatusType::FAILURE;
    }
    Node<group_node>* curMovie2 = new Node<group_node>();
    if(!curMovie2){
        return StatusType::ALLOCATION_ERROR;
    }
    copyNodeContent(curMovie2,movie);
    curMovie2->views++;

    StatusType status = StatusType::SUCCESS;
    moviesRating.root = moviesRating.searchAndDeleteRating(moviesRating.root,movie,status);
    if(status != StatusType::SUCCESS){
        return status;
    }
    //moviesRating.printLevelOrder();
    user->views++;


    moviesRating.root = moviesRating.searchAndAddRating(moviesRating.root,curMovie2,status);
    if(status != StatusType::SUCCESS){
        delete curMovie2;
        return status;
    }


    Node<group_node>* curMovie = new Node<group_node>();
    copyNodeContent(curMovie,movie);
    curMovie->views++;
    switch (movie->genre) {
        case Genre::COMEDY:
            user->ComedyViews++;
            comedyMovies.root = comedyMovies.searchAndDeleteRating(comedyMovies.root,movie,status);
            comedyMovies.root = comedyMovies.searchAndAddRating(comedyMovies.root,curMovie,status);
            if(user->curGroup)
            {
                user->curGroup->ComedyViews++;
                user->curGroup->views++;
            }
            break;
        case Genre::ACTION:
            user->ActionViews++;
            actionMovies.root = actionMovies.searchAndDeleteRating(actionMovies.root,movie,status);
            actionMovies.root = actionMovies.searchAndAddRating(actionMovies.root,curMovie,status);
            maxRatingActionMovie = actionMovies.getMax();
            if(user->curGroup)
            {
                user->curGroup->ActionViews++;
                user->curGroup->views++;
            }
            break;
        case Genre::FANTASY:
            user->FantasyViews++;
            fantasyMovies.root = fantasyMovies.searchAndDeleteRating(fantasyMovies.root,movie,status);
            fantasyMovies.root = fantasyMovies.searchAndAddRating(fantasyMovies.root,curMovie,status);
            maxRatingFantasyMovie = fantasyMovies.getMax();
            if(user->curGroup)
            {
                user->curGroup->FantasyViews++;
                user->curGroup->views++;
            }
            break;
        case Genre::DRAMA:
            user->DramaViews++;
            dramaMovies.root = dramaMovies.searchAndDeleteRating(dramaMovies.root,movie,status);
            dramaMovies.root = dramaMovies.searchAndAddRating(dramaMovies.root,curMovie,status);
            maxRatingDramaMovie = dramaMovies.getMax();
            if(user->curGroup)
            {
                user->curGroup->DramaViews++;
                user->curGroup->views++;
            }
            break;
        case Genre::NONE:
            break;
    }
    movie->views++;
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
    if(groupId <= 0 || movieId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* movie = movies.search(movieId); // O(log(k))
    if(!movie){
        return StatusType::FAILURE;
    }
    group_node* group = groups.search(groupId); // O(log(m))
    if(!group){
        return StatusType::FAILURE;
    }
    if(movie->isVip && !group->isVip){
        return StatusType::FAILURE;
    }
    if(group->members.numberOfNodes == 0){
        return StatusType::FAILURE;
    }
    Node<group_node>* curMovie2 = new Node<group_node>();
    if(!curMovie2){
        return StatusType::ALLOCATION_ERROR;
    }
    copyNodeContent(curMovie2,movie);
    curMovie2->views+=group->members.numberOfNodes;

    Node<group_node>* curMovie = new Node<group_node>();
    if(!curMovie){
        delete curMovie2;
        return StatusType::ALLOCATION_ERROR;
    }
    copyNodeContent(curMovie,movie);
    curMovie->views+=group->members.numberOfNodes;

    StatusType status = StatusType::SUCCESS;
    moviesRating.root = moviesRating.searchAndDeleteRating(moviesRating.root,movie,status);
    if(status != StatusType::SUCCESS){
        delete curMovie;
        delete curMovie2;
        return status;
    }


    moviesRating.root = moviesRating.searchAndAddRating(moviesRating.root,curMovie2,status);
    if(status!= StatusType::SUCCESS){
        delete curMovie2;
        delete curMovie;
        return status;
    }
    //moviesRating.printLevelOrder();

    group->moviesWatched++;
    switch (movie->genre) {
        case Genre::COMEDY:
            group->ComedyWatched++;
            comedyMovies.root = comedyMovies.searchAndDeleteRating(comedyMovies.root,movie,status);
            comedyMovies.root = comedyMovies.searchAndAddRating(comedyMovies.root, curMovie, status);
            maxRatingComedyMovie = comedyMovies.getMax();
            group->ComedyViews += group->members.numberOfNodes;
            break;
        case Genre::ACTION:
            group->ActionWatched++;
            actionMovies.root = actionMovies.searchAndDeleteRating(actionMovies.root,movie,status);
            actionMovies.root = actionMovies.searchAndAddRating(actionMovies.root, curMovie, status);
            maxRatingActionMovie = actionMovies.getMax();
            group->ActionViews += group->members.numberOfNodes;
            break;
        case Genre::FANTASY:
            group->FantasyWatched++;
            fantasyMovies.root = fantasyMovies.searchAndDeleteRating(fantasyMovies.root,movie,status);
            fantasyMovies.root = fantasyMovies.searchAndAddRating(fantasyMovies.root,curMovie,status);
            maxRatingFantasyMovie = fantasyMovies.getMax();
            group->FantasyViews += group->members.numberOfNodes;
            break;
        case Genre::DRAMA:
            group->DramaWatched++;
            dramaMovies.root = dramaMovies.searchAndDeleteRating(dramaMovies.root,movie,status);
            dramaMovies.root = dramaMovies.searchAndAddRating(dramaMovies.root, curMovie, status);
            maxRatingDramaMovie = dramaMovies.getMax();
            group->DramaViews += group->members.numberOfNodes;
            break;
        case Genre::NONE:
            break;
    }
    movie->views+=group->members.numberOfNodes;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    switch (genre) {
        case Genre::COMEDY:
            return output_t<int>{comedyMovies.numberOfNodes};
        case Genre::ACTION:
            return output_t<int>{actionMovies.numberOfNodes};
        case Genre::FANTASY:
            return output_t<int>{fantasyMovies.numberOfNodes};
        case Genre::DRAMA:
            return output_t<int>{dramaMovies.numberOfNodes};
        case Genre::NONE:
            return output_t<int>{movies.numberOfNodes};
    }
    return output_t<int>(StatusType::ALLOCATION_ERROR);
}
void iterate(int* i, int *const output, Node<group_node>* ptr){ // not finished
    if(!ptr){
        return;
    }
    iterate(i, output, ptr->rightSon);
    output[i[0]] = ptr->content;
    i[0]++;
    iterate(i, output, ptr->leftSon);
}
StatusType streaming_database::get_all_movies(Genre genre, int *const output) // not finished
{
    if(movies.numberOfNodes == 0){
        return StatusType::FAILURE;
    }
    int* i = new int[1];
    i[0] = 0;
    switch (genre) {
        case Genre::COMEDY:
            if(comedyMovies.numberOfNodes == 0){
                delete i;
                return StatusType::FAILURE;
            }
            iterate(i,output,comedyMovies.root);
            delete i;
            return StatusType::SUCCESS;
        case Genre::ACTION:
            if(actionMovies.numberOfNodes == 0){
                delete i;
                return StatusType::FAILURE;
            }
            iterate(i,output,actionMovies.root);
            delete i;
            return StatusType::SUCCESS;
        case Genre::FANTASY:
            if(fantasyMovies.numberOfNodes == 0){
                delete i;
                return StatusType::FAILURE;
            }
            iterate(i,output,fantasyMovies.root);
            delete i;
            return StatusType::SUCCESS;
        case Genre::DRAMA:
            if(dramaMovies.numberOfNodes == 0){
                delete i;
                return StatusType::FAILURE;
            }
            iterate(i,output,dramaMovies.root);
            delete i;
            return StatusType::SUCCESS;
        case Genre::NONE:
            iterate(i,output,moviesRating.root);
            delete i;
            return StatusType::SUCCESS;
    }
    delete i;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
    if(userId <= 0 ){
        return output_t<int>{StatusType::INVALID_INPUT};
    }
    Node<group_node>* user = users.search(userId); // O(log(n))
    if(!user){
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
    if(!user){
        return StatusType::FAILURE;
    }
    Node<group_node>* movie = movies.search(movieId); // O(log(k))
    if(!movie){
        return StatusType::FAILURE;
    }
    if(movie->isVip && !user->isVip){
        return StatusType::FAILURE;
    }
    double oldRating = movie->rating;
    movie->rating*=movie->usersRated;
    movie->rating+=rating;
    movie->usersRated++;
    movie->rating/=movie->usersRated;
    double newRating = movie->rating;
    movie->rating = oldRating;

    Node<group_node>* curMovie2 = new Node<group_node>();
    if(!curMovie2){
        return StatusType::ALLOCATION_ERROR;
    }
    StatusType status = StatusType::SUCCESS;
    moviesRating.root = moviesRating.searchAndDeleteRating(moviesRating.root,movie,status);
    if(status != StatusType::SUCCESS){
        return status;
    }
    copyNodeContent(curMovie2,movie);
    curMovie2->rating = newRating;

    moviesRating.root = moviesRating.searchAndAddRating(moviesRating.root, curMovie2, status);
    if(status != StatusType::SUCCESS){
        delete curMovie2;
        return status;
    }

    Node<group_node>* curMovie = new Node<group_node>();
    copyNodeContent(curMovie,movie);
    curMovie->rating = newRating;
    switch (movie->genre) {
        case Genre::COMEDY:
            comedyMovies.root = comedyMovies.searchAndDeleteRating(comedyMovies.root,movie,status);
            comedyMovies.root = comedyMovies.searchAndAddRating(comedyMovies.root,curMovie,status);
            maxRatingComedyMovie = comedyMovies.getMax();
            break;
        case Genre::ACTION:
            actionMovies.root = actionMovies.searchAndDeleteRating(actionMovies.root,movie,status);
            actionMovies.root = actionMovies.searchAndAddRating(actionMovies.root,curMovie,status);
            maxRatingActionMovie = actionMovies.getMax();
            break;
        case Genre::FANTASY:
            fantasyMovies.root = fantasyMovies.searchAndDeleteRating(fantasyMovies.root,movie,status);
            fantasyMovies.root = fantasyMovies.searchAndAddRating(fantasyMovies.root,curMovie,status);
            maxRatingFantasyMovie = fantasyMovies.getMax();
            break;
        case Genre::DRAMA:
            dramaMovies.root = dramaMovies.searchAndDeleteRating(dramaMovies.root,movie,status);
            dramaMovies.root = dramaMovies.searchAndAddRating(dramaMovies.root, curMovie, status);
            maxRatingDramaMovie = dramaMovies.getMax();
            break;
        case Genre::NONE:
            break;
    }
    movie->rating = newRating;
    return StatusType::SUCCESS;
}




output_t<int> streaming_database::get_group_recommendation(int groupId) // not finished
{
    if(groupId <= 0){
        return StatusType::INVALID_INPUT;
    }
    group_node* group = groups.search(groupId); // O(log(m))
    if(!group){
        delete group;
        return StatusType::FAILURE;
    }
    if(group->members.numberOfNodes == 0){
        return StatusType::FAILURE;
    }
    int groupFavorite = max_view_in_group(group->ActionViews,group->DramaViews,
                                          group->ComedyViews,group->FantasyViews);
    switch (groupFavorite) {
        case 0:
            if(comedyMovies.numberOfNodes == 0){
                return StatusType::FAILURE;
            }
            return maxRatingComedyMovie->content;
        case 1:
            if(dramaMovies.numberOfNodes == 0){
                return StatusType::FAILURE;
            }
            return maxRatingDramaMovie->content;
        case 2:
            if(actionMovies.numberOfNodes==0)
            {
                return StatusType::FAILURE;
            }
            return maxRatingActionMovie->content;
        case 3:
            if(fantasyMovies.numberOfNodes==0)
            {
                return StatusType::FAILURE;
            }
            return maxRatingFantasyMovie->content;
    }
    return StatusType::FAILURE;
}




















// main
using namespace std;


string OUTPUT_FILE_LOCATION = "C:/Users/yanar/OneDrive/Desktop/DataSturcures_HW1-main/outPut.txt";

void print(string cmd, StatusType res);
void print(string cmd, output_t<int> res);
void query_get_all_movies(string cmd, streaming_database *obj, Genre genre);

int main()
{
    std::ofstream myfile(OUTPUT_FILE_LOCATION); // Without append
    myfile.open (OUTPUT_FILE_LOCATION,ios::app);
    int d1, d2, d3, g1;
    string b1;
    bool b;

    // Init
    streaming_database *obj = new streaming_database();

    // Execute all commands in file
    string op;
    while (cin >> op)
    {
        if (!op.compare("add_movie")) {
            cin >> d1 >> g1 >> d2 >> b1;
            if (!b1.compare("True")) {
                b = true;
            }
            else if (!b1.compare("False")) {
                b = false;
            }
            else {
                myfile << "Invalid input format" << endl;
                return -1;
            }
            print(op, obj->add_movie(d1, (Genre) g1, d2, b));
        } else if (!op.compare("remove_movie")) {
            cin >> d1;
            print(op, obj->remove_movie(d1));
        } else if (!op.compare("add_user")) {
            cin >> d1 >> b1;
            if (!b1.compare("True")) {
                b = true;
            }
            else if (!b1.compare("False")) {
                b = false;
            }
            else {
                myfile << "Invalid input format" << endl;
                return -1;
            }
            print(op, obj->add_user(d1, b));
        } else if (!op.compare("remove_user")) {
            cin >> d1;
            print(op, obj->remove_user(d1));
        } else if (!op.compare("add_group")) {
            cin >> d1;
            print(op, obj->add_group(d1));
        } else if (!op.compare("remove_group")) {
            cin >> d1;
            print(op, obj->remove_group(d1));
        } else if (!op.compare("add_user_to_group")) {
            cin >> d1 >> d2;
            print(op, obj->add_user_to_group(d1, d2));
        } else if (!op.compare("get_all_movies_count")) {
            cin >> g1;
            print(op, obj->get_all_movies_count((Genre) g1));
        } else if (!op.compare("get_all_movies")) {
            cin >> g1;
            query_get_all_movies(op, obj, (Genre) g1);
        } else if (!op.compare("user_watch")) {
            cin >> d1 >> d2;
            print(op, obj->user_watch(d1, d2));
        } else if (!op.compare("group_watch")) {
            cin >> d1 >> d2;
            print(op, obj->group_watch(d1, d2));
        } else if (!op.compare("get_num_views")) {
            cin >> d1 >> g1;
            print(op, obj->get_num_views(d1, (Genre) g1));
        } else if (!op.compare("rate_movie")) {
            cin >> d1 >> d2 >> d3;
            print(op, obj->rate_movie(d1, d2, d3));
        } else if (!op.compare("get_group_recommendation")) {
            cin >> d1;
            print(op, obj->get_group_recommendation(d1));
        } else {
            myfile << "Unknown command: " << op << endl;
            return -1;
        }
        // Verify no faults
        if (cin.fail()){
            myfile << "Invalid input format" << endl;
            return -1;
        }
    }

    // Quit
    delete obj;
    return 0;
}

// Helpers
static const char *StatusTypeStr[] =
        {
                "SUCCESS",
                "ALLOCATION_ERROR",
                "INVALID_INPUT",
                "FAILURE"
        };

void print(string cmd, StatusType res)
{
    std::ofstream myfile;
    myfile.open (OUTPUT_FILE_LOCATION,ios::app);
    myfile << cmd << ": " << StatusTypeStr[(int) res] << endl;
}

void print(string cmd, output_t<int> res)
{
    std::ofstream myfile;
    myfile.open (OUTPUT_FILE_LOCATION,ios::app);
    if (res.status() == StatusType::SUCCESS) {
        myfile << cmd << ": " << StatusTypeStr[(int) res.status()] << ", " << res.ans() << endl;
    } else {
        myfile << cmd << ": " << StatusTypeStr[(int) res.status()] << endl;
    }
}

void query_get_all_movies(string cmd, streaming_database *obj, Genre genre)
{
    std::ofstream myfile;
    myfile.open (OUTPUT_FILE_LOCATION,ios::app);
    output_t<int> count = obj->get_all_movies_count(genre);
    int to_alloc = count.ans();
    if (to_alloc == 0)
    {
        //if there are no movies we will allocate 1 so that we will get failure instead of invalid input
        ++to_alloc;
    }
    // Allocate if okay
    int *out_mem = nullptr;
    if (count.status() == StatusType::SUCCESS)
    {
        out_mem = new int[to_alloc];
        for (int i = 0; i < to_alloc; ++i) out_mem[i] = -1;
    }
    // Call function
    StatusType status = obj->get_all_movies(genre, out_mem);
    print(cmd, status);
    if (status == StatusType::SUCCESS) {
        for (int i = 0; i < to_alloc; ++i)
        {
            myfile << out_mem[i] << endl;
        }
    }
    delete[] out_mem;
}
