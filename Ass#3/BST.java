/**
 * Created by Admin on 19.10.2015.
 */
public class BST<Key extends Comparable,Value> {

    Node root;

    class Node {
        Key key;
        Value val;
        Node left;
        Node right;
        int size;

        public Node(Key key, Value val, int size) {
            this.key = key;
            this.val = val;
            this.size = size;
        }
    }

    public Value find(Key key) {
        Node x = find(root, key);
        if (x == null) return null;
        else return x.val;
    }

    private Node find(Node x, Key key) {
        if (x == null)
            return null;
        int cmp = key.compareTo(x.key);
        if (cmp < 0) {
            return find(x.left, key);
        } else if (cmp > 0) {
            return find(x.right, key);
        }
        return x;
    }
    public void add(Key key, Value val) {
        root = add(root, key, val);
    }

    private Node add(Node x, Key key, Value val) {
        if (x == null) {
            return new Node(key, val, 1);
        }
        int cmp = key.compareTo(x.key);
        if (cmp < 0) {
            x.left = add(x.left, key, val);
        } else if (cmp > 0)
            x.right = add(x.right, key, val);
        else
            x.val = val;

        x.size = size(x.left) + size(x.right) + 1;
        return x;
    }
    private int size(Node x) {
        if (x == null)
            return 0;

        return x.size;
    }

    public int size() {
        return size(root);
    }

    public void delete(Key key) {
        root = delete(key,root);
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
            x.right = deleteMin(t.right);
            x.left = t.left;
        }
        x.size = 1 + size(x.left) + size(x.right);
        return x;
    }
    private Node deleteMin(Node x) {
        if (x.left == null)
            return x.right;
        x.left = deleteMin(x.left);

        x.size = 1 + size(x.left) + size(x.right);
        return x;
    }
    private Node min(Node x) {
        if (x.left == null)
            return x;
        else
            return min(x.left);
    }
    public static void binarySearch(BST<Integer, Integer> bst, int[] data, int val) {
        int lo = 0;
        int hi = data.length;

        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (data[mid] < val) {
                bst.add(data[mid], data[mid]);
                lo = mid + 1;
            } else if (data[mid] > val) {
                bst.add(data[mid], data[mid]);
                hi = mid - 1;
            } else {
                bst.add(data[mid], data[mid]);
                return;
            }
        }
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
    public static void main(String[] args) {
        int[] data = {1, 3, 5, 7, 8, 14, 17};
        BST<Integer, Integer> bst = new BST<>();
        for (int i : data) {
            binarySearch(bst, data, i);
        }
        System.out.println(bst.height());

        BST<Integer, Integer> bst2 = new BST<>();
        for (int i : data) {
            bst2.add(i, i);
        }
        System.out.println(bst2.height());
    }
}

