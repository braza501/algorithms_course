import java.util.*;

/**
 * Created by Admin on 08.10.2015.
 */
public class MyTree<E> {
    static final int MIN_CAPACITY = 3;
    E[] tree = (E[]) new Object[1000];
    Integer k;
    int height = 0;
    Integer size = 0;


    MyTree(int k) {
        this.k = k;
    }

    MyTree(int k, int capacity) {
        this.k = k;
        tree = (E[]) new Object[capacity];
    }


    static MyTree MyTreeExpression(String exp) {

        HashMap<String, Integer> opPriority = new HashMap<>();
        Stack<MyTree> operands = new Stack<>();
        Stack<String> operators = new Stack<>();
        opPriority.put("+", 1);
        opPriority.put("-", 1);
        opPriority.put("*", 2);
        opPriority.put("/", 2);
        opPriority.put("(", 0);


        ArrayList<String> tokens = Expression.toArrayList(exp);

        for (String token : tokens) {
            if (token.equals("(")) {
                operators.push(token);
            } else if (opPriority.containsKey(token)) {
                int priority = opPriority.get(token);
                while (!operators.empty() && priority <= opPriority.get(operators.peek())) {
                    String op = operators.pop();
                    MyTree<String> right = operands.pop();
                    MyTree<String> left = operands.pop();
                    MyTree<String> newNode = new MyTree<>(op, left, right);
                    operands.push(newNode);
                }
                operators.push(token);
            } else if (token.equals(")")) {
                while (!operators.peek().equals("(")) {
                    String op = operators.pop();
                    MyTree<String> right = operands.pop();
                    MyTree<String> left = operands.pop();
                    MyTree<String> newNode = new MyTree<String>(op, left, right);
                    operands.push(newNode);
                }
                operators.pop();
            } else {
                MyTree<String> operand = new MyTree<String>(2, MIN_CAPACITY);
                operand.addRoot(token);
                operands.push(operand);
            }
        }
        while (!operators.empty()) {
            String op = operators.pop();
            MyTree<String> right = operands.pop();
            MyTree<String> left = operands.pop();
            MyTree<String> newNode = new MyTree<String>(op, left, right);
            operands.push(newNode);
        }
        return operands.pop();
    }

    public void addRoot(E element) {
        if (tree[0] != null) {
            throw new IllegalArgumentException("The root already exists!");
        }
        tree[0] = element;
    }

    public int size() {
        return size;
    }

    public boolean isEmty() {
        return size == 0;
    }

    public Integer getRoot() {
        if (tree[0] != null)
            return 0;

        return null;
    }

    public E getRootElement() {
        if (tree[0] != null)
            return tree[0];

        return null;
    }

    public ArrayList<E> getChildrenElements(int parent) {
        ArrayList<E> elements = new ArrayList<>();
        for (int i = k * parent + 1; i <= k * parent + k && tree[i] != null; i++) {
            elements.add(tree[i]);
        }
        return elements;
    }

    private MyTree(E element, MyTree<E> left, MyTree<E> right) {

        k = 2;
        attach(0, 1, left.tree);
        attach(0, 2, right.tree);

        tree[0] = element;
        size++;
    }

    private void attach(int oldPosition, int newPosition, E[] subTree) {
        if (subTree[oldPosition] == null)
            return;

        attach(oldPosition * k + 1, newPosition * k + 1, subTree);
        attach(oldPosition * k + 2, newPosition * k + 2, subTree);

        tree[newPosition] = subTree[oldPosition];
        subTree[oldPosition] = null;
    }

    public int numberOfChildren(int parent) {
        if (tree[parent] == null) {
            throw new IllegalArgumentException("No such parent");
        }
        int count = 0;
        for (int i = k * parent + 1; i <= k * parent + k; i++) {
            if (tree[i] != null)
                count++;
        }
        return count;
    }

    public void addChild(int parent, E element) {

        if (tree[parent] == null) {
            throw new IllegalArgumentException("No such parent");
        }
        int count = numberOfChildren(parent);
        if (count == k) {
            throw new IllegalArgumentException("No free space for child");
        }
        if (count == 0) {
            height++;
        }
        tree[parent * k + count + 1] = element;
        size++;
    }

    public void addChild(int parent, E element, int iThChild) {

        if (tree[parent] == null) {
            throw new IllegalArgumentException("No such parent");
        }
        int count = numberOfChildren(parent);
        if (count == k) {
            throw new IllegalArgumentException("No free space for child");
        }
        if (count == 0) {
            height++;
        }
        tree[parent * k + iThChild] = element;
        size++;
    }

    public E parent(int child) {
        if (tree[child] == null) {
            throw new IllegalArgumentException("No such child");
        }
        return tree[(child - 1) / k];
    }

    public void set(int position, E element) {
        if (tree[position] == null) {
            throw new IllegalArgumentException("No such position");
        }
        tree[position] = element;
    }

    public void arrayfilled(E[] data) {
        if (data.length > 1000) {
            throw new IllegalArgumentException("Too big data set");
        }
        int i = 0;

        for (E element : data) {
            tree[i++] = element;
            size++;
        }
    }

    public int height() {
        return height = height(getRoot());
    }

    private int height(int position) {

        int h = 0;
        for (int i = k * position + 1; i <= k * position + k && tree[i] != null; i++) {
            if (tree[i] != null) {
                h = Math.max(h, 1 + height(i));
            }
        }
        return h;
    }

    public void visit(int position) {
        System.out.print(" " + tree[position].toString() + " ");
    }

    public int evaluate() {
        return evaluate(getRoot());
    }

    private int evaluate(int position) {
        if (numberOfChildren(position) == 0)
            return Integer.valueOf(tree[position].toString());
        else
            return perfomOperation(evaluate(k * position + 1), evaluate(k * position + 2), tree[position].toString());
    }

    public void preOrder() {
        preOrder(getRoot());
    }

    private int perfomOperation(int one, int two, String op) {
        if (op.equals("+")) return one + two;
        else if (op.equals("-")) return one - two;
        else if (op.equals("*")) return one * two;
        else return one / two;
    }

    private void preOrder(int position) {
        if (position >= 1000)
            return;
        if (tree[position] == null)
            return;
        visit(position);
        for (int i = k * position + 1; i <= k * position + k; i++) {
            preOrder(i);
        }
    }

    public void postOrder() {
        postOrder(getRoot());
    }

    private void postOrder(int position) {
        if (position >= 1000)
            return;
        if (tree[position] == null)
            return;

        for (int i = k * position + 1; i <= k * position + k; i++) {
            postOrder(i);
        }
        visit(position);
    }

    public void inOrder() {
        if (k != 2) {
            throw new IllegalArgumentException("Only for binary trees!");
        }
        inOrder(getRoot());
    }

    private void inOrder(int position) {
        if (position >= 1000)
            return;
        if (tree[position] == null)
            return;
        inOrder(2 * position + 1);
        visit(position);
        inOrder(2 * position + 2);
    }

    public void breadthfirst() {
        LinkedList<Integer> q = new LinkedList<>();
        q.addLast(0);
        while (!q.isEmpty()) {
            int position = q.poll();
            visit(position);
            for (int i = k * position + 1; i <= k * position + k; i++) {
                if (tree[i] != null)
                    q.addLast(i);
            }
        }
    }

    public static void main(String[] args) {
        try {
            MyTree<String> kAryTree = MyTreeExpression("20 + 15 - 10 * 29");
            System.out.println(kAryTree.evaluate());
            System.out.println(kAryTree.height());
        } catch (Exception ex) {
            System.out.println(" Smth goes wrong! Check input. Hint: " + ex.getMessage());
            ex.printStackTrace();

        }
    }
}
