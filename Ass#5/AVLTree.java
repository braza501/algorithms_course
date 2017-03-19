import java.util.HashMap;
import java.util.TreeMap;

/**
 * Created by Admin on 20.10.2015.
 */
public class AVLTree<Key extends Comparable<Key>, Value> {

    static final int OPERATION_TIME = 0;
    static final int HEIGHT = 1;
    Node root;

    class Node {
        Key key;
        Value val;
        Node left;
        Node right;
        int size;
        int height;

        public Node(Key key, Value val, int size, int height) {
            this.key = key;
            this.val = val;
            this.size = size;
            this.height = height;
        }
    }

    public void add(Key key, Value val) {
        root = add(root, key, val);
    }

    private Node add(Node x, Key key, Value val) {
        if (x == null) {
            return new Node(key, val, 1, 0);
        }
        int cmp = key.compareTo(x.key);
        if (cmp < 0) {
            x.left = add(x.left, key, val);
        } else if (cmp > 0)
            x.right = add(x.right, key, val);
        else
            x.val = val;

        int difference = height(x.left) - height(x.right);
        if (difference > 1) {
            if (height(x.left.left) >= height(x.left.right)) {
                return rotateRight(x);
            } else {
                x.left = rotateLeft(x.left);
                return rotateRight(x);
            }
        }
        if (difference < -1) {
            if (height(x.right.right) >= height(x.right.left)) {
                return rotateLeft(x);
            } else {
                x.right = rotateRight(x.right);
                return rotateLeft(x);
            }
        }
        x.size = size(x.left) + size(x.right) + 1;
        x.height = Math.max(height(x.left), height(x.right)) + 1;
        return x;
    }

    private Node rotateRight(Node x) {
        Node t = x.left;
        x.left = t.right;
        t.right = x;

        x.height = Math.max(height(x.left), height(x.right)) + 1;
        x.size = size(x.left) + size(x.right) + 1;
        t.height = Math.max(height(t.left), height(t.right)) + 1;
        t.size = size(t.left) + size(t.right) + 1;

        return t;
    }

    private Node rotateLeft(Node x) {
        Node t = x.right;
        x.right = t.left;
        t.left = x;

        x.height = Math.max(height(x.left), height(x.right)) + 1;
        x.size = size(x.left) + size(x.right) + 1;
        t.height = Math.max(height(t.left), height(t.right)) + 1;
        t.size = size(t.left) + size(t.right) + 1;

        return t;
    }

    public int height() {
        return height(root);
    }

    private int height(Node x) {
        if (x == null)
            return -1;

        return x.height;
    }

    private int size(Node x) {
        if (x == null)
            return 0;

        return x.size;
    }

    public int size() {
        return size(root);
    }

    public Key min() {
        return min(root).key;
    }

    private Node min(Node x) {
        if (x.left == null)
            return x;
        else
            return min(x.left);
    }

    public void delete(Key key) {
        root = delete(key, root);
    }

    private Node delete(Key key, Node x) {
        if (x == null)
            throw new IllegalArgumentException("There is no element with suck key!");

        int cmp = key.compareTo(x.key);
        if (cmp < 0) x.left = delete(key, x.left);
        else if (cmp > 0) x.right = delete(key, x.right);
        else {
            if (x.left == null) return x.right;
            if (x.right == null) return x.left;

            Node t = x;
            x = min(t.right);
            x.right = delete(x.key, t.right);
            x.left = t.left;
        }

        int difference = height(x.left) - height(x.right);
        if (difference > 1) {
            if (height(x.left.left) >= height(x.left.right)) {
                return rotateRight(x);
            } else {
                x.left = rotateLeft(x.left);
                return rotateRight(x);
            }
        }
        if (difference < -1) {
            if (height(x.right.right) >= height(x.right.left)) {
                return rotateLeft(x);
            } else {
                x.right = rotateRight(x.right);
                return rotateLeft(x);
            }
        }
        x.size = size(x.left) + size(x.right) + 1;
        x.height = Math.max(height(x.left), height(x.right)) + 1;

        return x;
    }


    static int log2(int number) {
        return (int) (Math.log(number) / Math.log(2));
    }

    public static void main(String[] args) {
        //int[] data = {1, 3, 5, 7, 8, 14, 17};

        AVLTree<Integer, Integer> bst = new AVLTree<>();
        HashMap<Integer, Long[]> statisticsInsertion = new HashMap<>();
        HashMap<Integer, Long[]> statisticsDeletion = new HashMap<>();

        for (int i = 0; i < 1000000; i++) {
            long start = System.currentTimeMillis();
            bst.add(i, i);
            long end = System.currentTimeMillis();
            Long[] pair = {end - start, Long.valueOf(bst.height())};
            statisticsInsertion.put(i, pair);

        }
        for (int i = 0; i < 1000000; i++) {
            long start = System.currentTimeMillis();
            bst.delete(i);
            long end = System.currentTimeMillis();
            Long[] pair = {end - start, Long.valueOf(bst.height())};
            statisticsDeletion.put(i, pair);
        }
        for (int i = 10; i <= 1000000; i *= 10) {
            Long[] pair = statisticsInsertion.get(i - 1);
            System.out.println("After insertion of " + i + " elements " + " operation time "
                    + pair[OPERATION_TIME] + " Height " + pair[HEIGHT] + " log2(" + i + ") " + log2(i));
        }
        System.out.println("Deletion in big range :");
        for (int i = 10; i <1000000 ; i *=10) {
            Long[] pair = statisticsDeletion.get(i - 1);
            System.out.println("After deletion of " + i + " elements " + " operation time "
                    + pair[OPERATION_TIME] + " Height " + pair[HEIGHT] + " log2(" + (1000000 - i) + ") " + log2(1000000 - i));
        }
        System.out.println("Deletion in small range :");
        for (int i = 970000; i <1000000 ; i += 5000) {
            Long[] pair = statisticsDeletion.get(i - 1);
            System.out.println("After deletion of " + i + " elements " + " operation time "
                    + pair[OPERATION_TIME] + " Height " + pair[HEIGHT] + " log2(" + (1000000 - i) + ") " + log2(1000000 - i));
        }
    }
}
