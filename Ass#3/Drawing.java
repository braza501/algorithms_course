import javax.swing.*;
import java.awt.*;
import java.awt.geom.Line2D;


/**
 * Created by Admin on 01.09.2015.
 */
public class Drawing extends JFrame {

    private static final int CANVAS_DEFAULT_SIZE = 512;
    private int r = 15;

    private BST bst;

    Drawing(BST bst) {
        this.bst = bst;
        setTitle("BST");
        setSize(CANVAS_DEFAULT_SIZE, CANVAS_DEFAULT_SIZE);
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }

    public void paint(Graphics g) {
        g.setColor(getBackground());
        g.fillRect(0, 0, getWidth(), getHeight());
        g.setColor(getForeground());
        Graphics2D g2 = (Graphics2D) g;
        drawNode(256, 70, g2, bst.root,100,80);
    }

    public void drawNode(int x, int y, Graphics2D g2, BST.Node node,int x_incr,int y_incr) {

        g2.drawOval(x - r, y - 2 * r, 2 * r, 2 * r);
        g2.drawString(node.val.toString(), x - 8, y - 13);


        if (node.left != null) {

            int newX = x - x_incr;
            int newY = y + y_incr;
            Shape line = new Line2D.Double(x - 3, y, newX, newY - 2 * r);
            g2.draw(line);

            drawNode(newX, newY, g2, node.left,x_incr-40,y_incr-10);
        }
        if (node.right != null) {

            int newX = x + x_incr;
            int newY = y + y_incr;
            Shape line = new Line2D.Double(x, y, newX, newY - 2 * r);
            g2.draw(line);

            drawNode(newX, newY, g2, node.right,x_incr-40,y_incr-10);
        }
    }

    public static void main(String[] args) {
        int[] data = {1, 3, 5, 7, 8, 14, 17};
        BST<Integer, Integer> bst = new BST<>();
        for (int i : data) {
            BST.binarySearch(bst, data, i);
        }
        Drawing dr = new Drawing(bst);

    }
}

