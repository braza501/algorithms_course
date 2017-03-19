package innopolis;

import javafx.geometry.Point2D;

/**
 * Created by Admin on 07.09.2015.
 */
public class CrossNumberAlgo {

    public static boolean intersects(Point2D a, Point2D b, Point2D c, Point2D d) {
        // We describe the section AB as A+(B-A)*u and CD as C+(D-C)*v
        // then we solve A + (B-A)*u = C + (D-C)*v
        // let's use Kramer's rule to solve the task (Ax = B) were x = (u, v)^T
        // build a matrix for the equation
        double[][] A = new double[2][2];
        A[0][0] = b.getX() - a.getX();
        A[1][0] = b.getY() - a.getY();
        A[0][1] = c.getX() - d.getX();
        A[1][1] = c.getY() - d.getY();
        // calculate determinant
        double det0 = A[0][0] * A[1][1] - A[1][0] * A[0][1];
        // substitute columns and calculate determinants
        double detU = (c.getX() - a.getX()) * A[1][1] - (c.getY() - a.getY()) * A[0][1];
        double detV = A[0][0] * (c.getY() - a.getY()) - A[1][0] * (c.getX() - a.getX());
        // calculate the solution
        // even if det0 == 0 (they are parallel) this will return NaN and comparison will fail -> false
        double u = detU / det0;
        double v = detV / det0;
        return u > 0 && u < 1 && v > 0 && v < 1;
    }
    public static boolean myIntersection(Point2D one,Point2D two,Point2D query ){
        if (one.getY()<query.getY() && two.getY()>=query.getY()
                || two.getY()<query.getY()  && one.getY()>=query.getY() ) {
            if (one.getX() + ((query.getY() - one.getY()) / (two.getY() - one.getY())) * (two.getX() - one.getX()) < query.getX()) {
                return true;
            }
        }
        return false;
    }

    static boolean inside(MyLinkedList<Point2D> polygon, Point2D point)
    {
        boolean IsOdd = false;
        Point2D prev = polygon.getLast();

        for(Point2D current: polygon){
            if(CrossNumberAlgo.myIntersection(prev, current,new Point2D(point.getX(), point.getY()))){
                IsOdd=!IsOdd;
            }
            prev=current;
        }
        return IsOdd;
    }
}
