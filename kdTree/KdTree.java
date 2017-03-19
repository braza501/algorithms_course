public class KdTree {
    private Node root;             // root of BST
    private int N;                     // size of KdTree

    private static class Node {
        private Point2D p;      // the point
        private RectHV rect;    // the axis-aligned rectangle corresponding to this node
        private Node lb;        // the left/bottom subtree
        private Node rt;        // the right/top subtree

        public Node(Point2D point) {
            p = point;
        }

    }

    public KdTree()                               // construct an empty set of points
    {
        root = null;
        N = 0;
    }

    public boolean isEmpty()                      // is the set empty?
    {
        return N == 0;
    }

    public int size()                         // number of points in the set
    {
        return N;
    }

    public void insert(Point2D p)              // add the point to the set (if it is not already in the set)
    {
        if (contains(p))
            return;
        root = insert(root, p, 0, null, 0);
    }

    //1 - left, 2 right, 3 up , 4 down
    private Node insert(Node x, Point2D point, int dir, Node parent, int orientation) {
        if (x == null) {

            x = new Node(point);

            if (N == 0)
                x.rect = new RectHV(0, 0, 1, 1);
            else if (dir == 1)
                x.rect = new RectHV(parent.rect.xmin(), parent.rect.ymin(), parent.p.x(), parent.rect.ymax());

            else if (dir == 2)
                x.rect = new RectHV(parent.p.x(), parent.rect.ymin(), parent.rect.xmax(), parent.rect.ymax());

            else if (dir == 4)
                x.rect = new RectHV(parent.rect.xmin(), parent.rect.ymin(), parent.rect.xmax(), parent.p.y());

            else if (dir == 3)
                x.rect = new RectHV(parent.rect.xmin(), parent.p.y(), parent.rect.xmax(), parent.rect.ymax());

            N++;
            return x;
        }
        if (orientation == 0) {

            if (point.x() < x.p.x())
                x.lb = insert(x.lb, point, 1, x, 1);
            else
                x.rt = insert(x.rt, point, 2, x, 1);

        } else {

            if (point.y() < x.p.y())
                x.lb = insert(x.lb, point, 4, x, 0);
            else
                x.rt = insert(x.rt, point, 3, x, 0);


        }
        return x;
    }

    public boolean contains(Point2D p)            // does the set contain point p?
    {
        return contains(root, p, 0);
    }

    private boolean contains(Node x, Point2D point, int orientation) {
        if (x == null) return false;

        if (point.x() == x.p.x() && point.y() == x.p.y())
            return true;

        if (orientation == 0) {


            if (point.x() < x.p.x())
                return contains(x.lb, point, 1);
            else
                return contains(x.rt, point, 1);

        } else {

            if (point.y() < x.p.y())
                return contains(x.lb, point, 0);
            else
                return contains(x.rt, point, 0);

        }
    }

    public void draw()                         // draw all points to standard draw
    {
        inorder(root, 0);
    }

    private void inorder(Node x, int orientation) {

        if (x == null) return;
        inorder(x.lb, ((orientation + 1) % 2));

        if (orientation == 0) {
            StdDraw.setPenColor(StdDraw.RED);
            StdDraw.setPenRadius();
            StdDraw.line(x.p.x(), x.rect.ymin(), x.p.x(), x.rect.ymax());
        } else {
            StdDraw.setPenColor(StdDraw.BLUE);
            StdDraw.setPenRadius();
            StdDraw.line(x.rect.xmin(), x.p.y(), x.rect.xmax(), x.p.y());
        }
        inorder(x.rt, (orientation + 1) % 2);
        StdDraw.setPenColor(StdDraw.BLACK);
        StdDraw.setPenRadius(.01);
        x.p.draw();
    }

    public Iterable<Point2D> range(RectHV rect)             // all points that are inside the rectangle
    {

        Queue<Point2D> q = new Queue<Point2D>();
        range(root, rect, q);

        return q;

    }

    private void range(Node x, RectHV rect, Queue<Point2D> q) {
        if (x == null)
            return;
        if (!rect.intersects(x.rect))
            return;


        if (rect.contains(x.p))
            q.enqueue(x.p);

        range(x.lb, rect, q);
        range(x.rt, rect, q);
    }

    public Point2D nearest(Point2D p)             // a nearest neighbor in the set to point p; null if the set is empty
    {
        if (N == 0)
            return null;

        Point2D champ = root.p;

        return nearest(root, p, champ, 0);


    }

    private Point2D nearest(Node x, Point2D p, Point2D champ, int orient) {
        if (x == null)
            return champ;
        if (p.distanceSquaredTo(champ) < x.rect.distanceSquaredTo(p))
            return champ;

        if (x.p.distanceSquaredTo(p) < champ.distanceSquaredTo(p))
            champ = x.p;


        if (orient == 0) {
            if (p.x() < x.p.x()) {

                champ = nearest(x.rt, p, nearest(x.lb, p, champ, 1), 1);
            } else {

                champ = nearest(x.lb, p, nearest(x.rt, p, champ, 1), 1);
            }

        } else {
            if (p.y() < x.p.y()) {

                champ = nearest(x.rt, p, nearest(x.lb, p, champ, 0), 0);
            } else {

                champ = nearest(x.lb, p, nearest(x.rt, p, champ, 0), 0);
            }

        }

        return champ;
    }

    public static void main(String[] args)                  // unit testing of the methods (optional)
    {


    }
}