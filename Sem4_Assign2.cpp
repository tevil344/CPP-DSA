#include <iostream>
using namespace std;

struct Player {
    int player_id;
    int score;
    Player* left;
    Player* right;
    int height;
};

class AVLTree {
public:
    Player* root;
    
    AVLTree() { root = nullptr; }
    
    int getHeight(Player* node) {
        return node ? node->height : 0;
    }
    
    int getBalanceFactor(Player* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }
    
    Player* createPlayer(int player_id, int score) {
        Player* newPlayer = new Player();
        newPlayer->player_id = player_id;
        newPlayer->score = score;
        newPlayer->left = newPlayer->right = nullptr;
        newPlayer->height = 1;
        return newPlayer;
    }
    
    Player* rotateRight(Player* y) {
        Player* x = y->left;
        Player* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        
        return x;
    }
    
    Player* rotateLeft(Player* x) {
        Player* y = x->right;
        Player* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        
        return y;
    }
    
    Player* insertPlayer(Player* node, int player_id, int score) {
        if (!node) return createPlayer(player_id, score);
        
        if (score < node->score)
            node->left = insertPlayer(node->left, player_id, score);
        else if (score > node->score)
            node->right = insertPlayer(node->right, player_id, score);
        else
            return node;
        
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        
        int balance = getBalanceFactor(node);
        
        if (balance > 1 && score < node->left->score)
            return rotateRight(node);
        if (balance < -1 && score > node->right->score)
            return rotateLeft(node);
        if (balance > 1 && score > node->left->score) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && score < node->right->score) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }
    
    Player* minValueNode(Player* node) {
        Player* current = node;
        while (current->left) current = current->left;
        return current;
    }
    
    Player* deletePlayer(Player* root, int score) {
        if (!root) return root;
        
        if (score < root->score)
            root->left = deletePlayer(root->left, score);
        else if (score > root->score)
            root->right = deletePlayer(root->right, score);
        else {
            if (!root->left || !root->right) {
                Player* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                delete temp;
            } else {
                Player* temp = minValueNode(root->right);
                root->score = temp->score;
                root->right = deletePlayer(root->right, temp->score);
            }
        }
        
        if (!root) return root;
        
        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
        int balance = getBalanceFactor(root);
        
        if (balance > 1 && getBalanceFactor(root->left) >= 0)
            return rotateRight(root);
        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (balance < -1 && getBalanceFactor(root->right) <= 0)
            return rotateLeft(root);
        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
        return root;
    }
    
    void inOrder(Player* root) {
        if (root) {
            inOrder(root->right);
            cout << "Player ID: " << root->player_id << " Score: " << root->score << endl;
            inOrder(root->left);
        }
    }
    
    void registerPlayer(int player_id, int score) {
        root = insertPlayer(root, player_id, score);
    }
    
    void displayLeaderboard() {
        cout << "Leaderboard (High to Low):\n";
        inOrder(root);
    }
    
    void removePlayer(int score) {
        root = deletePlayer(root, score);
    }
};

int main() {
    AVLTree game;
    game.registerPlayer(1, 50);
    game.registerPlayer(2, 70);
    game.registerPlayer(3, 30);
    game.registerPlayer(4, 90);
    
    game.displayLeaderboard();
    
    cout << "\nRemoving Player with score 70\n";
    game.removePlayer(70);
    game.displayLeaderboard();
    
    return 0;
}
