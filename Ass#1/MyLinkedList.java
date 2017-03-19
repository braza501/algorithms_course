package innopolis;

import java.util.Iterator;

/**
 * Created by Admin on 01.09.2015.
 */
public class MyLinkedList<Item> implements Iterable<Item> {
    @Override
    public Iterator<Item> iterator() {
        return new ListIterator();
    }

    private class ListIterator implements Iterator<Item>
    {
        private Node<Item> current = tail.getNext();
        int i=size;
        public boolean hasNext() { return i>0; }
        public void remove() { }
        public Item next()
        {
            Item item = current.getVertex();
            current = current.next;
            i--;
            return item;
        }
    }
    static private class Node<Item> {
        private Item vertex;
        private Node<Item> next;

        public Node(Item vertex, Node<Item> next) {
            this.vertex = vertex;
            this.next = next;
        }
        public Node<Item> getNext(){
            return next;
        }
        public void setNext(Node<Item> newNode){
            next=newNode;
        }
        public Item getVertex(){
            return vertex;
        }
    }

    private Node<Item> tail;
    private int size;

    public boolean isEmpty(){
            return size==0;
    }
    public Item getFirst(){
        return tail.getNext().getVertex();
    }
    public Item getLast(){return tail.getVertex();}
    public void rotate() {
         if (tail != null)
             tail = tail.getNext();
    }
    public void addFirst(Item vertex) {
      if (size == 0) {
          tail = new Node<>(vertex, null);
          tail.setNext(tail);
      } else {
          Node<Item> newNode = new Node<>(vertex, tail.getNext());
          tail.setNext(newNode);
      }
        size++;
    }
    public void addLast(Item vertex) {
        addFirst(vertex);
        tail = tail.getNext();
    }
    public Item removeFirst() {
        if (isEmpty()) {
          return null;
        }
        Node<Item> head = tail.getNext();
        if (head == tail) {
            tail = null;
        }
        else {
            tail.setNext(head.getNext());
        }
        size--;

        return head.getVertex();
    }
}
