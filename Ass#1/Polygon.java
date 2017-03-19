package innopolis;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Line2D;
import javafx.geometry.Point2D;

import java.util.Random;

/**
 * Created by Admin on 01.09.2015.
 */
public class Polygon extends JFrame {

    private static final int CANVAS_DEFAULT_SIZE = 512;
    private static final int QUERY_POINTS_CREATED = 10000;
    private static final int PARTITION = 11;
    private int x=250;
    private int y=250;
    private int r=120;

    Polygon(){
        setTitle("Polygon");
        setSize(CANVAS_DEFAULT_SIZE, CANVAS_DEFAULT_SIZE);
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }
    public void paint(Graphics g){
        Graphics2D g2 = (Graphics2D) g;

        g2.drawOval(x-r,y-r,2*r,2*r);
        float scaledPenRadius = (float) (0.005 * 512);
        BasicStroke stroke = new BasicStroke(scaledPenRadius , BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);
        g2.setStroke(stroke); ;
        g2.setColor(Color.RED);

        MyLinkedList<Point2D> list = new MyLinkedList<Point2D>();
        double angle = 2*Math.PI/PARTITION;
        double rotate = angle;

        for(int i =0;i<PARTITION;i++){
            double x_ = x+ r*Math.cos(rotate);
            double y_ = y+ r*Math.sin(rotate);

            Point2D newPoint = new Point2D(x_,y_);
            list.addLast(newPoint);
            rotate+=angle;
        }

        Point2D prev = list.getLast();
        for(Point2D vertex: list){

            g2.setColor(Color.BLUE);
            Shape l = new Line2D.Double(prev.getX(),prev.getY(),vertex.getX(),vertex.getY());
            g2.draw(l);
            prev = vertex;
        }
        scaledPenRadius = (float) (0.01 * 512);
        stroke = new BasicStroke(scaledPenRadius , BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);
        g2.setStroke(stroke);
        g2.setColor(Color.RED);

        for(Point2D vertex: list){
            g2.setColor(Color.BLACK);
            Shape line = new Line2D.Double(vertex.getX(),vertex.getY(),vertex.getX(),vertex.getY());
            g2.draw(line);
        }

        Random random = new Random();
        for(int i =0; i<QUERY_POINTS_CREATED;i++){

            Point2D query = new Point2D(1 + random.nextInt()%CANVAS_DEFAULT_SIZE, 1 + random.nextInt()%CANVAS_DEFAULT_SIZE);

            if(CrossNumberAlgo.inside(list,query)){
                g2.setColor(Color.GREEN);
            }
            else{
                g2.setColor(Color.RED);
            }
            Shape line = new Line2D.Double(query.getX(),query.getY(),query.getX(),query.getY());
            g2.draw(line);
        }
    }

    public static void main(String[] args){
        Polygon t = new Polygon();
    }
}
