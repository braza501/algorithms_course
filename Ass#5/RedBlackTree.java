import java.io.IOException;
import java.util.HashMap;
import java.util.Map;



public class RedBlackTree<Key extends Comparable<Key>> {
    // constants for maintaining colors
    private static final int RED = 1;
    private static final int BLACK = 0;

    Node root; // root of the tree

    /**
     * Node structure, containing key,
     * parent's and children's  links and color
     */
    class Node {
        public Key key;
        public Node left;
        public Node right;
        public Node parent;
        public int color;

        public Node(Key key, int nodeColor) {
            this.key = key;
            this.color = nodeColor;
            this.parent = null;
        }


        public Node grandparent() {
            return parent.parent;
        }

        // get another node with the same parent
        public Node sibling() {
            if (this == parent.left)
                return parent.right;
            else
                return parent.left;
        }

        // get sibling of the parent node
        public Node uncle() {
            return parent.sibling();
        }

    }

    public RedBlackTree() {
        root = null;
    }

    // check for colors
    private int nodeColor(Node currentNode) {
        return currentNode == null ? BLACK : currentNode.color;
    }

    /**
     * left rotation of the tree rooted at the currentNode
     * with proper parent relinking
     *
     * @param currentNode
     */

    private void rotateLeft(Node currentNode) {
        Node t = currentNode.right;
        parentRelink(currentNode, t);
        currentNode.right = t.left;
        if (t.left != null) {
            t.left.parent = currentNode;
        }
        t.left = currentNode;
        currentNode.parent = t;
    }

    public int height() {
        return height(root);
    }

    private int height(Node x) {
        int h = 0;
        if (x.left != null)
            h = Math.max(h, 1 + height(x.left));
        if (x.right != null)
            h = Math.max(h, 1 + height(x.right));

        return h;
    }

    /**
     * right rotation of the tree rooted at the currentNode
     * with proper parent relinking
     *
     * @param currentNode
     */
    private void rotateRight(Node currentNode) {
        Node t = currentNode.left;
        parentRelink(currentNode, t);
        currentNode.left = t.right;
        if (t.right != null) {
            t.right.parent = currentNode;
        }
        t.right = currentNode;
        currentNode.parent = t;
    }

    /**
     * takes parent link from oldNode and
     * gives them to newNode, changing
     * parent's child link
     *
     * @param oldNode the node from which we take
     * @param newNode the node which is given
     */
    private void parentRelink(Node oldNode, Node newNode) {
        if (oldNode.parent == null) {
            root = newNode;
        } else {
            if (oldNode == oldNode.parent.left)
                oldNode.parent.left = newNode;
            else
                oldNode.parent.right = newNode;
        }
        if (newNode != null) {
            newNode.parent = oldNode.parent;
        }
    }

    /**
     * Inserts the key into the symbol table
     *
     * @param key the key
     */
    public void insert(Key key) {
        Node newNode = new Node(key, RED);
        if (root == null) {
            root = newNode;
        } else {
            Node currentNode = root;
            while (true) {
                int cmp = key.compareTo(currentNode.key);
                if (cmp == 0) {
                    return;
                } else if (cmp < 0) {
                    if (currentNode.left == null) {
                        currentNode.left = newNode;
                        break;
                    } else {
                        currentNode = currentNode.left;
                    }
                } else {
                    if (currentNode.right == null) {
                        currentNode.right = newNode;
                        break;
                    } else {
                        currentNode = currentNode.right;
                    }
                }
            }
            newNode.parent = currentNode;
        }
        checkProperties(newNode);

    }

    /**
     * checks red-black tree properties with given node.
     * makes some rebalance and color flips to achieve
     * essential properties, if needed
     *
     * @param currentNode
     */
    private void checkProperties(Node currentNode) {
        if (currentNode.parent == null)
            currentNode.color = BLACK;
        else {
            if (nodeColor(currentNode.parent) == BLACK)
                return;
            else
                flipColorsOrRotation(currentNode);
        }
    }

    /**
     * makes color flip or invokes rotation routine
     *
     * @param currentNode
     */
    void flipColorsOrRotation(Node currentNode) {

        if (nodeColor(currentNode.uncle()) == RED) {
            currentNode.parent.color = BLACK;
            currentNode.uncle().color = BLACK;
            currentNode.grandparent().color = RED;
            checkProperties(currentNode.grandparent());
        } else {
            intermediateRotation(currentNode);
        }
    }

    /**
     * makes initial rotation to reduce to easier cases,
     * defining rotation cases (LL,LR,RR,LR), if needed
     *
     * @param currentNode
     */
    void intermediateRotation(Node currentNode) {
        if (currentNode == currentNode.parent.right && currentNode.parent == currentNode.grandparent().left) {
            rotateLeft(currentNode.parent);
            currentNode = currentNode.left;
        } else if (currentNode == currentNode.parent.left && currentNode.parent == currentNode.grandparent().right) {
            rotateRight(currentNode.parent);
            currentNode = currentNode.right;
        }
        finalRotation(currentNode);
    }

    /**
     * applies left or right rotation
     * resulting in restoring initial
     * properties of  current red black tree
     *
     * @param currentNode
     */
    void finalRotation(Node currentNode) {
        currentNode.parent.color = BLACK;
        currentNode.grandparent().color = RED;
        if (currentNode == currentNode.parent.left && currentNode.parent == currentNode.grandparent().left) {
            rotateRight(currentNode.grandparent());
        } else {
            rotateLeft(currentNode.grandparent());
        }
    }

    /**
     * Returns the Node object associated with the given key.
     *
     * @param key the key
     * @return the Node object associated with the given key if the key is in the symbol table
     * and null if the key is not in the symbol table
     */
    public Node find(Key key) {
        return find(root, key);
    }

    private Node find(Node currentNode, Key key) {
        if (currentNode == null)
            return null;
        int cmp = key.compareTo(currentNode.key);
        if (cmp < 0) {
            return find(currentNode.left, key);
        } else if (cmp > 0) {
            return find(currentNode.right, key);
        }
        return currentNode;
    }


      public static int log2(int i) {
        return (int) (Math.log(i) / Math.log(2));
    }

    public static void main(String[] args) throws IOException {
        RedBlackTree<Integer> bst = new RedBlackTree<>();
        HashMap<Integer, Long[]> statisticsInsertion = new HashMap<>();
        long start = System.currentTimeMillis();
        for (int i = 0; i < 1000000; i++) {
            bst.insert(i);
            if (i == 999 || i == 9999 | i == 99999 || i == 999999) {
                long end = System.currentTimeMillis();
                Long[] pair = {end - start, Long.valueOf(bst.height())};
                statisticsInsertion.put(i, pair);
            }
        }
        for (Map.Entry<Integer, Long[]> x : statisticsInsertion.entrySet()) {
            System.out.println("After " + (x.getKey() + 1) + " Insertion consumed time: " + x.getValue()[0] + " height : " + x.getValue()[1]);
        }
    }
}
