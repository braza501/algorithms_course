import MyBST.for_assignment.BST;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Line2D;


/**
 * Created by Admin on 01.09.2015.
 */
public class Drawing extends JFrame {

    private static final int CANVAS_DEFAULT_SIZE = 512;
    private int r = 15;

    private AVLTree bst;

    Drawing(AVLTree bst) {
        this.bst = bst;
        setTitle("MyBST.for_assignment.BST");
        setSize(CANVAS_DEFAULT_SIZE, CANVAS_DEFAULT_SIZE);
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }

    public void paint(Graphics g) {
        g.setColor(getBackground());
        g.fillRect(0, 0, getWidth(), getHeight());
        g.setColor(getForeground());
        Graphics2D g2 = (Graphics2D) g;
        drawNode(256, 70, g2, bst.root, 100, 80);
    }

    public void drawNode(int x, int y, Graphics2D g2, AVLTree.Node node, int x_incr, int y_incr) {

        //g2.drawOval(x - r, y - 2 * r, 2 * r, 2 * r);
        g2.drawString(node.val.toString(), x - 8, y - 13);


        if (node.left != null) {

            int newX = x - x_incr;
            int newY = y + y_incr;
            Shape line = new Line2D.Double(x - 3, y, newX, newY - 2 * r);
            g2.draw(line);

            drawNode(newX, newY, g2, node.left, x_incr - 40, y_incr - 10);
        }
        if (node.right != null) {

            int newX = x + x_incr;
            int newY = y + y_incr;
            Shape line = new Line2D.Double(x, y, newX, newY - 2 * r);
            g2.draw(line);

            drawNode(newX, newY, g2, node.right, x_incr - 40, y_incr - 10);
        }
    }

    public static void main(String[] args) {

        AVLTree<String, String> bst = new AVLTree<>();
        //March, May, November, August, April, January, December, July, February, June, October, September.
        bst.add("March", "March");
        bst.add("May", "May");
        bst.add("November", "November");
        bst.add("August", "August");
        bst.add("April", "April");
        bst.add("January", "January");
        bst.add("December", "December");
        bst.add("July", "July");
        bst.add("February", "February");
        bst.add("June", "June");
        bst.add("October", "October");
        bst.add("September", "September");
        bst.delete("April");
        bst.delete("August");
        bst.delete("December");
        Drawing dr = new Drawing(bst);


    }
}

