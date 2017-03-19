public class PointSET {

    private SET<Point2D> set;

    public PointSET()                               // construct an empty set of points
    {
        set = new SET<Point2D>();
    }

    public boolean isEmpty()                      // is the set empty?
    {
        return set.isEmpty();
    }

    public int size()                         // number of points in the set
    {
        return set.size();
    }

    public void insert(Point2D p)              // add the point to the set (if it is not already in the set)
    {
        if (p == null) throw new NullPointerException("called contains() with a null key");

        if (set.contains(p) == false)
            set.add(p);
    }

    public boolean contains(Point2D p)            // does the set contain point p?
    {
        if (p == null) throw new NullPointerException("called contains() with a null key");
        return set.contains(p);
    }

    public void draw()                         // draw all points to standard draw
    {
        for (Point2D p : set)
            p.draw();
    }

    public Iterable<Point2D> range(RectHV rect)             // all points that are inside the rectangle
    {
        Queue<Point2D> q = new Queue<Point2D>();
        for (Point2D p : set)
            if (rect.contains(p))
                q.enqueue(p);

        return q;
    }

    public Point2D nearest(Point2D p)             // a nearest neighbor in the set to point p; null if the set is empty
    {

        Point2D min = null;
        for (Point2D point : set) {

            if (min == null)
                min = point;
            else if (point.distanceSquaredTo(p) < min.distanceSquaredTo(p))
                min = point;
        }
        return min;
    }

    public static void main(String[] args)                  // unit testing of the methods (optional)
    {
    }
}