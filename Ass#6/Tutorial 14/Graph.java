/**
 * Created by Admin on 26.11.2015.
 */

import java.io.*;
import java.util.*;


public class Graph<TDataValue extends Comparable, TWeight extends Comparable> {

    DoublyLinkedList<Vertex> vertices = new DoublyLinkedList<>();
    DoublyLinkedList<Edge> edges = new DoublyLinkedList<>();
    static int vertexNumber = 0;

    public class Vertex {
        int number;
        TDataValue value;
        DoublyLinkedList.Node<Vertex> listPosition;
        DoublyLinkedList<Edge> incidents = new DoublyLinkedList<>();


        public List<Vertex> adjacent() {

            List<Vertex> result = new ArrayList<>();

            for (Edge edge : incidents) {
                if (edge.from != this) {
                    result.add(edge.from);
                } else {
                    result.add(edge.to);
                }
            }
            return result;
        }
    }

    public Edge getEdge(Vertex u, Vertex v) {
        for (Edge edge : u.incidents) {
            if (edge.from == u && edge.to == v) {
                return edge;
            } else if (edge.from == v && edge.to == u) {
                return edge;
            }
        }
        throw new IllegalArgumentException("smth goes wrong=)");
    }

    public class Edge {
        TWeight weight;
        Vertex from;
        Vertex to;
        DoublyLinkedList.Node<Edge> listPosition;
        DoublyLinkedList.Node<Edge> adjListPosTo;
        DoublyLinkedList.Node<Edge> adjListPosFrom;
    }

    void addVertex(TDataValue value) {
        Vertex vertex = new Vertex();
        vertex.value = value;
        vertex.listPosition = vertices.addLast(vertex);
        vertex.number = vertexNumber++;
    }

    void removeVertex(Vertex vertex) {
        for (Edge e : vertex.incidents) {
            removeEdge(e);
        }
        vertices.remove(vertex.listPosition);
    }

    public void addEdge(Vertex from, Vertex to, TWeight weight) {


        Edge e = new Edge();
        e.weight = weight;
        e.from = from;
        e.to = to;

        e.listPosition = edges.addLast(e);
        e.adjListPosFrom = from.incidents.addLast(e);
        e.adjListPosTo = to.incidents.addLast(e);
    }

    public Vertex opposite(Vertex u, Edge e) {
        if (e.from != u) {
            return e.from;
        } else {
            return e.to;
        }
    }

    public void removeEdge(Edge e) {
        Vertex from = e.from;
        Vertex to = e.to;
        from.incidents.remove(e.adjListPosFrom);
        to.incidents.remove(e.adjListPosTo);
        edges.remove(e.listPosition);
    }
    public void serialize(String file) throws IOException {
        FileWriter fileWriter = new FileWriter(file);
        for (Vertex vertex : vertices) {
            fileWriter.write(vertex.value.toString() + " ");
        }
        fileWriter.write("\n");
        for (Edge edge : edges) {
            String first = edge.from.value.toString();
            String second = edge.to.value.toString();
            String weight = edge.weight.toString();
            fileWriter.write(first + " " + second + " " + weight + " ");
        }
        fileWriter.close();
    }

    public static void main(String[] args) throws IOException {

    }

}