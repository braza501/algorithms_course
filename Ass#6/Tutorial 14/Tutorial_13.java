
import java.io.*;
import java.util.*;



public class Tutorial_13 {


    Graph<String, Integer> graph = new Graph<>();
    Graph<String, Integer>.Vertex startVertex;
    LinkedList<String> list = new LinkedList<>();
    int dfsSum = 0;
    int bfsSum = 0;
    int mstSum = 0;

    public Tutorial_13(String file) throws IOException {

        InputStreamReader reader = new InputStreamReader(
                new FileInputStream(file), "UTF-8");
        ArrayList<String> arr = new ArrayList<>();
        BufferedReader bufReader = new BufferedReader(reader);

        HashMap<String, Integer> map = new HashMap<>();

        String[] cities = bufReader.readLine().split(" ");


        int i = 0;
        for (String str : cities) {
            map.put(str, i++);
            graph.addVertex(str);
            if (str.equals("Moscow"))
                startVertex = graph.vertices.last();
        }
        cities = bufReader.readLine().split(" ");
        for (int j = 0; j < cities.length - 2; j += 3) {

                int vertex1 = map.get(cities[j]);
                int vertex2 = map.get(cities[j + 1]);
                graph.addEdge(graph.vertices.get(vertex1), graph.vertices.get(vertex2), Integer.valueOf(cities[j + 2]));

                String k = cities[j];
                String r = cities[j + 1];
        }
    }

    public void dfs() {
        boolean[] marked = new boolean[graph.vertices.size()];
        list = new LinkedList<>();
        dfs(startVertex, marked);
    }

    private void dfs(Graph<String, Integer>.Vertex v, boolean[] marked) {
        marked[v.number] = true;
        for (Graph<String, Integer>.Vertex w : v.adjacent())
            if (!marked[w.number]) {
                dfsSum += graph.getEdge(v, w).weight;
                list.addLast(" <- " + v.value + " - " + w.value + " -> ");
                dfs(w, marked);
            }
    }

    public void bfs() {
        boolean[] marked = new boolean[graph.vertices.size()];
        list = new LinkedList<>();
        bfs(startVertex, marked);
    }


    private void bfs(Graph<String, Integer>.Vertex startVertex, boolean[] marked) {
        LinkedList<Graph<String, Integer>.Vertex> q = new LinkedList<>();
        q.addLast(startVertex);
        marked[startVertex.number] = true;
        while (!q.isEmpty()) {
            Graph<String, Integer>.Vertex v = q.pollFirst();
            for (Graph<String, Integer>.Vertex w : v.adjacent()) {
                if (!marked[w.number]) {
                    q.addLast(w);
                    bfsSum += graph.getEdge(v, w).weight;
                    marked[w.number] = true;
                    list.addLast(" <- " + v.value + " - " + w.value + " -> ");
                }
            }
        }
    }

    private static class ByWeight implements Comparator<Graph.Edge> {
        @Override
        public int compare(Graph.Edge x, Graph.Edge y) {

            if (x.weight.compareTo(y.weight) < 0) {
                return -1;
            }
            if (x.weight.compareTo(y.weight) > 0) {
                return 1;
            }
            return 0;
        }
    }

    public void mst() {
        Comparator<Graph.Edge> comparator = new ByWeight();
        list = new LinkedList<>();
        PriorityQueue<Graph.Edge> pq = new PriorityQueue<>(comparator);
        for (Graph.Edge e : graph.edges)
            pq.add(e);
        UF uf = new UF(graph.vertices.size());
        while (!pq.isEmpty() && list.size() < graph.vertices.size() - 1) {
            Graph.Edge e = pq.poll();
            int v = e.from.number, w = e.to.number;
            if (!uf.connected(v, w)) {
                uf.union(v, w);
                mstSum +=(Integer)e.weight;
                list.addLast(" <- " + e.from.value + " - " + e.to.value + " -> ");
            }
        }
    }

    public static void main(String[] args) throws IOException {

        Tutorial_13 tutorial_13 = new Tutorial_13("distances2.txt");

        //DFS
        tutorial_13.dfs();
        FileWriter fileWriter = new FileWriter("dfs_ouput.txt");
        fileWriter.write("DFS sum - " + tutorial_13.dfsSum + "\n");
        for (String str : tutorial_13.list) {
            fileWriter.write(str + "\n");
        }
        fileWriter.close();

        //BFS
        tutorial_13.bfs();
        fileWriter = new FileWriter("bfs_ouput.txt");
        fileWriter.write("BFS sum - " + tutorial_13.bfsSum + "\n");
        for (String str : tutorial_13.list) {
            fileWriter.write(str + "\n");
        }
        fileWriter.close();

        //MST
        tutorial_13.mst();
        fileWriter = new FileWriter("mst_ouput.txt");
        fileWriter.write("MST sum - " + tutorial_13.mstSum + "\n");
        for (String str : tutorial_13.list) {
            fileWriter.write(str + "\n");
        }
        fileWriter.close();
    }
}

