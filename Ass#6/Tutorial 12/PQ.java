import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

/**
 * Created by Admin on 10.11.2015.
 */
public class PQ<Key extends Comparable<Key>> {

    public static boolean LESS = false;
    public static boolean GREAT = true;

    private Key[] pq = (Key[]) new Comparable[16];
    private int N = 0;
    private boolean priority;

    public PQ(Key[] list, boolean priority) {
        this.priority = priority;
        N = list.length;
        pq = list;
        for (int k = (N - 2) / 2; k >= 0; k--) {
            sink(k);
        }
    }

    public PQ(boolean priority) {
        this.priority = priority;
    }

    public boolean isEmpty() {
        return N == 0;
    }

    private void resize(int cap) {
        Key[] temp = (Key[]) new Comparable[cap];
        for (int i = 0; i < N; i++) {
            temp[i] = pq[i];
        }
        pq = temp;

    }

    public void insert(Key key) {
        if (N == pq.length)
            resize(pq.length * 2);
        pq[N] = key;
        swim(N++);
    }


    public Key max() {
        return pq[0];
    }

    public Key delMax() {
        Key max = pq[0];
        swap(0, --N);
        sink(0);
        pq[N] = null;

        if (N > 0 && N == pq.length / 4)
            resize(pq.length / 2);
        return max;
    }

    private void swim(int k) {
        while (k > 0 && op((k - 1) / 2, k)) {
            swap((k - 1) / 2, k);
            k = (k - 1) / 2;
        }
    }

    private void sink(int k) {
        while (2 * k + 1 < N) {
            int j = 2 * k + 1;
            if (j < N - 1 && op(j, j + 1)) j++;
            if (!op(k, j)) break;
            swap(k, j);
            k = j;
        }
    }

    private boolean op(int i, int j) {
        if (priority == GREAT)
            return pq[i].compareTo(pq[j]) < 0;

        return pq[i].compareTo(pq[j]) > 0;
    }

    private void swap(int i, int j) {
        Key t = pq[i];
        pq[i] = pq[j];
        pq[j] = t;
    }

    public static void main(String[] args) throws IOException {

        Integer[] r = {2, 3, 10, 7, 1, 5, 0};
        PQ<Integer> pq = new PQ<Integer>(r, LESS);

        while (!pq.isEmpty()) {
            System.out.println(pq.delMax().toString());
        }


        Integer[] a = {2, 3, 10, 7, 1, 5, 0};
        QuickSort.sort(a);
        for (int i : a) {
            System.out.print(i + " ");
        }

        System.out.println();
        Integer[] k = {2, 3, 10, 7, 1, 5, 0};
        HeapSort.sort(k);
        for (int i : k) {
            System.out.print(i + " ");
        }

    }
}
