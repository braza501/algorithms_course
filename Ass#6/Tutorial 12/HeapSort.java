/**
 * Created by Admin on 10.11.2015.
 */
public class HeapSort {

    private static void sink(Comparable[] a, int k, int N) {
        while (2 * k + 1 <= N) {
            int j = 2 * k + 1;
            if (j < N && less(a, j, j + 1)) j++;
            if (!less(a, k, j)) break;
            swap(a, k, j);
            k = j;
        }
    }

    private static boolean less(Comparable[] a, int i, int j) {
        return a[i].compareTo(a[j]) < 0;
    }

    private static void swap(Comparable[] a, int i, int j) {
        Comparable t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    public static void sort(Comparable[] target) {
        int N = target.length - 1;
        for (int k = (N - 1) / 2; k >= 0; k--) {
            sink(target, k, N);
        }
        while (N > 0) {
            swap(target, 0, N--);
            sink(target, 0, N);
        }
    }

}
