/**
 * 
 * AVL Tree implementation
 * 
 * AVL Tree is a self-balancing binary search tree. It was the first such data structure to be invented.
 * In an AVL tree, the heights of the two child subtrees of any node differ by at most one.
 * 
 * <p> AVL Tree has the following methods: </p>
 * 
 * <ul>
 * <li> {@link #insert(Stock)}: Inserts a new stock to the tree. </li>
 * <li> {@link #delete(String)}: Deletes a stock from the tree. </li>
 * <li> {@link #search(String)}: Searches for a stock in the tree. </li>
 * <li> {@link #preOrderTraversal()}: Traverses the tree in pre-order. </li>
 * <li> {@link #postOrderTraversal()}: Traverses the tree in post-order. </li>
 * <li> {@link #inOrderTraversal()}: Traverses the tree in in-order. </li>
 * </ul>
 */

public class AVLTree {
    /**
     * Node class (private class dont show in the javadoc)
     * 
     * <p> The class has the following attributes: </p>
     * <ul>
     * <li> {@link #stock}: Stock object </li>
     * <li> {@link #left}: Left child node </li>
     * <li> {@link #right}: Right child node </li>
     * <li> {@link #height}: Height of the node </li>
     * </ul>
     */
    private class Node {
        Stock stock;
        Node left, right;
        int height;

        Node(Stock stock) {
            this.stock = stock;
            this.height = 1;
        }
    }

    private Node root; // Root of the AVL Tree


    private Node insert(Node node, Stock stock) {
        // Implementation of AVL Tree insertion logic (we have two parts: insertion and balancing)

        // Insertion
        if (node == null)
            return new Node(stock); // if the node is in leaf
        if (stock.getSymbol().compareTo(node.stock.getSymbol()) < 0)
            node.left = insert(node.left, stock); // if the stock is smaller than the root
        else if (stock.getSymbol().compareTo(node.stock.getSymbol()) > 0)
            node.right = insert(node.right, stock); // if the stock is greater than the root
        else
            return node;

        // Balancing
        node.height = 1 + Math.max(height(node.left), height(node.right)); // We should update the height of the each subtrees till the root.

        // Balance factor calculation 
        int balance = getBalance(node);
        
        if (balance > 1 && node.left != null && getBalance(node.left) >= 0) // Left Left Case
            return rightRotate(node);
        if (balance < -1 && node.right != null && getBalance(node.right) <= 0) // Right Right Case
            return leftRotate(node);
        if (balance > 1 && node.left != null && getBalance(node.left) < 0) { // Left Right Case
            node.left = leftRotate(node.left);
            return rightRotate(node);
        }
        if (balance < -1 && node.right != null && getBalance(node.right) > 0) { // Right Left Case
            node.right = rightRotate(node.right);
            return leftRotate(node);
        }
        return node;
    }

    /**
     * Inserts a new stock to the tree.
     * <br>
     * Inserion is done recursively and has two parts: insertion and balancing.
     * <br>
     * First, we insert the node to the tree.
     * <br>
     * Then, we calculate the balance factor of the each subtrees root node.
     * <br>
     * If the balance factor is greater than 1 or less than -1, we need to balance the tree.
     * <br>
     * We have four cases for balancing:
     * <p>
     * 1. Left Left Case : Condition: balance > 1 && getBalance(node.left) > 0
     *  - Right rotation
     * </p>
     * <p>
     * 2. Right Right Case : Condition: balance < -1 && getBalance(node.right) < 0
     * - Left rotation
     * </p>
     * <p>
     * 3. Left Right Case : Condition: balance > 1 && getBalance(node.left) < 0
     * - Left rotation on left child and right rotation on root
     * </p>
     * <p>
     * 4. Right Left Case : Condition: balance < -1 && getBalance(node.right) > 0
     * - Right rotation on right child and left rotation on root
     * 
     * @param node the node to be inserted
     * @param stock the stock to be inserted
     */
    public void insert(Stock stock) {
        root = insert(root, stock);
    }

    /**
     * Height of the node
     * 
     * @param node the node to calculate the height
     */
    private int height(Node node) {
        return (node == null) ? 0 : node.height;
    }

    /**
     * Balance factor of the node
     * 
     * @param node the node to calculate the balance factor
     */
    private int getBalance(Node node) {
        return (node == null) ? 0 : height(node.left) - height(node.right);
    }

    /**
     * Right rotation : Rotate the node to right
     * 
     * @param node the node to be rotated
     * @return the new root of the subtree
     */
    private Node rightRotate(Node node){
        Node left = node.left;
        Node leftRight = left.right;
        left.right = node;
        node.left = leftRight;
        node.height = 1 + Math.max(height(node.left), height(node.right));
        left.height = 1 + Math.max(height(left.left), height(left.right));
        return left;
    }

    /**
     * Left rotation : Rotate the node to left
     * 
     * @param node the node to be rotated
     * @return the new root of the subtree
     */
    private Node leftRotate(Node node){
        Node right = node.right;
        Node rightLeft = right.left;
        right.left = node;
        node.right = rightLeft;
        node.height = 1 + Math.max(height(node.left), height(node.right));
        right.height = 1 + Math.max(height(right.left), height(right.right));
        return right;
    }

    /**
     * Deletes a stock from the tree.
     * <br>
     * Deletion is done recursively and has two parts: deletion and balancing.
     * <br>
     * First, we delete the node from the tree.
     * <br>
     * Then, we calculate the balance factor of the each subtrees root node.
     * <br>
     * If the balance factor is greater than 1 or less than -1, we need to balance the tree.
     * <br>
     * We have four cases for balancing:
     * <p>
     * 1. Left Left Case : Condition: balance > 1 && getBalance(node.left) > 0
     * - Right rotation
     * </p>
     * <p>
     * 2. Right Right Case : Condition: balance < -1 && getBalance(node.right) < 0
     * - Left rotation
     * </p>
     * <p>
     * 3. Left Right Case : Condition: balance > 1 && getBalance(node.left) < 0
     * - Left rotation on left child and right rotation on root
     * </p>
     * <p>
     * 4. Right Left Case : Condition: balance < -1 && getBalance(node.right) > 0
     * - Right rotation on right child and left rotation on root
     * </p>
     * 
     * @param symbol the symbol of the stock to be deleted
     */
    public void delete(String symbol) {
        root = delete(root, symbol);
    }

    private Node delete(Node node, String symbol) {
        // Implementation of AVL Tree deletion logic
        if (node == null)
            return null;
        if (symbol.compareTo(node.stock.getSymbol()) < 0)
            node.left = delete(node.left, symbol);
        else if (symbol.compareTo(node.stock.getSymbol()) > 0)
            node.right = delete(node.right, symbol);
        else {
            if (node.left == null || node.right == null) {
                Node temp = (node.left == null) ? node.right : node.left;
                if (temp == null) {
                    temp = node;
                    node = null;
                } else
                    node = temp;
            } else {
                Node temp = findMin(node.right);
                node.stock = temp.stock;
                node.right = delete(node.right, temp.stock.getSymbol());
            }
        }

        // Balancing
        if (node == null)
            return null;
        node.height = 1 + Math.max(height(node.left), height(node.right));
        int balance = getBalance(node);
        if (balance > 1 && getBalance(node.left) >= 0)
            return rightRotate(node);
        if (balance < -1 && getBalance(node.right) <= 0)
            return leftRotate(node);
        if (balance > 1 && getBalance(node.left) < 0) {
            node.left = leftRotate(node.left);
            return rightRotate(node);
        }
        if (balance < -1 && getBalance(node.right) > 0) {
            node.right = rightRotate(node.right);
            return leftRotate(node);
        }
        return node;
    }

    /**
     * Finds the minimum node in the tree
     * 
     * @param node the node to start the search
     * @return the minimum node
     */
    private Node findMin(Node node) {
        Node current = node;
        while (current.left != null)
            current = current.left;
        return current;
    }

    /**
     * Searches for a stock in the tree.
     * Algoritnm is similar to the binary search tree search.
     * 
     * 
     * @param node the node to start the search
     * @param symbol the symbol of the stock to be searched
     * @return the stock if found, null otherwise
     */
    private Node search(Node node, String symbol) {
        // Implementation of AVL Tree search logic
        if (node == null)
            return null;
        if (symbol.compareTo(node.stock.getSymbol()) < 0)
            return search(node.left, symbol);
        else if (symbol.compareTo(node.stock.getSymbol()) > 0)
            return search(node.right, symbol);
        return node;
    }

    /**
     * Searches for a stock in the tree.
     * 
     * @param symbol the symbol of the stock to be searched
     * @return the stock if found, null otherwise
     */
    public Stock search(String symbol) {
        Node result = search(root, symbol);
        return (result != null) ? result.stock : null;
    }
    /**
     * Traverses the tree in pre-order.
     * 
     * @param node the node to start the traversal
     */
    private void preOrderTraversal(Node node) {
        if (node == null)
            return;
        System.out.println(node.stock);
        preOrderTraversal(node.left);
        preOrderTraversal(node.right);
    }

    /**
     * Traverses the tree in post-order.
     * 
     * @param node the node to start the traversal
     */

    private void postOrderTraversal(Node node) {
        if (node == null)
            return;
        postOrderTraversal(node.left);
        postOrderTraversal(node.right);
        System.out.println(node.stock);
    }

    /**
     * Traverses the tree in in-order.
     * 
     * @param node the node to start the traversal
     */

    private void inOrderTraversal(Node node) {
        if (node == null)
            return;
        inOrderTraversal(node.left);
        System.out.println(node.stock);
        inOrderTraversal(node.right);
    }

    /**
     * Traverses and prints the tree in pre-order.
    */
    public void preOrderTraversal() {
        preOrderTraversal(root);
    }

    /**
     * Traverses and prints the tree in post-order.
    */
    public void postOrderTraversal() {
        postOrderTraversal(root);
    }

    /**
     * Traverses and prints the tree in in-order.
    */
    public void inOrderTraversal() {
        inOrderTraversal(root);
    }

    //public static void main(String[] args) {
    //    AVLTree tree = new AVLTree();
    //    for (int i = 3; i < 10; i++) {
    //        Stock stock = new Stock("Stock" + i, 100.0 + i, 1000 + i, 10000 + i);
    //        tree.insert(stock);
    //    }
    //    tree.insert(new Stock("Stock0", 100.0, 1000, 10000));
    //    tree.insert(new Stock("Stock2", 100.0, 1000, 10000));
    //    tree.insert(new Stock("Stock1", 100.0, 1000, 10000));
    //    tree.inOrderTraversal();
    //    
    //}

}
