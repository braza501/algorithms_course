import java.util.Random;

/**
 * Created by Admin on 16.11.2015.
 */
public class QuickSort {
    private static void shuffle(Comparable[] a){
        Random rand = new Random();
        int N = a.length;
        for (int i = 1; i < N; i++)
        {
            int r = rand.nextInt(i + 1);
            swap(a, i, r);
        }
    }
    public static void sort(Comparable[] a) {
        shuffle(a);
        sort(a, 0, a.length - 1);
    }

    private static void sort(Comparable[] a, int lo, int hi) {
        if (hi <= lo) return;
        int leftArrow = lo, rightArrow = hi;
        Comparable v = a[lo];
        int i = lo;
        while (i <= rightArrow) {
            int cmp = a[i].compareTo(v);
            if      (cmp < 0) swap(a, leftArrow++, i++);
            else if (cmp > 0) swap(a, i, rightArrow--);
            else              i++;
        }

        sort(a, lo, leftArrow-1);
        sort(a, rightArrow+1, hi);

    }


    private static boolean less(Comparable v, Comparable w) {
        return v.compareTo(w) < 0;
    }

    private static void swap(Object[] a, int i, int j) {
        Object swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }

}
