package Player;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.RenderingHints;
import java.awt.Stroke;
import java.io.File;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import javax.swing.JPanel;

public class GraphPainter extends JPanel {

    public static final int BUFFER_SIZE = 20001;
    public static final int BORDER_GAP = 20;
    private static final int GRAPH_POINT_WIDTH = 1;
    private static final int DEFAULT_MAX_SCORE = 30000;
    private static final Color GRAPH_COLOR = Color.BLACK;
    private static final Color GRAPH_POINT_COLOR = Color.BLACK;
    private static final Stroke GRAPH_STROKE = new BasicStroke(0.7f);
    private LinkedList<Integer> samples;
    private LinkedList<Integer> backup;
    private WavFile wavFile;
    private int Ox;
    private List<Point> points;
    private double xScale;
    private double yScale;
    private int currentOxLen;

    public GraphPainter(File waveFile, int width, int height) throws Exception {
        this.setBackground(Color.WHITE);
        this.setBorder(javax.swing.BorderFactory.createEtchedBorder());
        this.setSize(width, height);
        this.setVisible(true);

        wavFile = WavFile.openWavFile(waveFile);
        samples = new LinkedList<Integer>();
        backup = new LinkedList<Integer>();
        Ox = height / 2;
        currentOxLen = BUFFER_SIZE - 1;
        xScale = ((double) getWidth() - 2 * BORDER_GAP) / currentOxLen;
        yScale = ((double) getHeight() - 2 * BORDER_GAP) / (DEFAULT_MAX_SCORE - 1);
        points = new ArrayList<Point>();

        initGraph();
    }

    public WavFile getWavFile() {
        return wavFile;
    }

    public int[] getData(int numberFrames) {
        int[] a = new int[numberFrames];
        Iterator<Integer> it = samples.iterator();
        for (int i = 0; i < numberFrames; ++i) {
            if (it.hasNext()) {
                a[i] = it.next();
            } else {
                a[i] = 0;
            }
        }
        return a;
    }

    public void changeMaxScore(int level) {
        int maxScore = level * 10000 + DEFAULT_MAX_SCORE;
        yScale = ((double) getHeight() - 2 * BORDER_GAP) / (maxScore - 1);
        refresh();
    }

    public int getCurrentOxLen() {
        return currentOxLen;
    }

    public void changeXScale(int level) {
        currentOxLen = level * 5000 + BUFFER_SIZE - 1;
        xScale = ((double) getWidth() - 2 * BORDER_GAP) / currentOxLen;
        refresh();
    }

    public void moveGraphLeft(int numberFrames) throws Exception {
        for (int i = 0; i < numberFrames; ++i) {
            if (samples.isEmpty()) {
                break;
            }
            backup.addLast(samples.getFirst());
            samples.removeFirst();
        }

        numberFrames = Math.min(numberFrames, BUFFER_SIZE + 10000 - samples.size());
        if (numberFrames > 0) {
            int a[] = new int[numberFrames];
            numberFrames = wavFile.readFrames(a, numberFrames);

            for (int i = 0; i < numberFrames; ++i) {
                samples.addLast(a[i]);
            }
        }

        refresh();
    }

    public void moveGraphRight(int numberFrames) throws Exception {
        for (int i = 0; i < numberFrames; ++i) {
            if (backup.isEmpty()) {
                break;
            }
            samples.addFirst(backup.getLast());
            backup.removeLast();
        }

        refresh();
    }

    private void initGraph() throws Exception {
        int n = BUFFER_SIZE + 10000;
        int a[] = new int[n];

        n = wavFile.readFrames(a, n);
        for (int i = 0; i < n; ++i) {
            samples.add(a[i]);
        }

        refresh();
    }

    public void refresh() {
        this.revalidate();
        this.repaint();
    }

    public int getRemainFrames() {
        return samples.size();
    }

    public int getX(int frame) {
        return (int) (frame * xScale + BORDER_GAP);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        if (samples.size() <= 1) {
            return;
        }

        Object[] a = samples.toArray();

        Graphics2D g2 = (Graphics2D) g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        points.clear();
        for (int i = 0; i < a.length; ++i) {
            int val = (Integer) a[i];
            int x = (int) (i * xScale + BORDER_GAP);
            int y = (int) (Ox - val * yScale);
            points.add(new Point(x, y));
        }

        Stroke oldStroke = g2.getStroke();
        g2.setColor(GRAPH_COLOR);
        g2.setStroke(GRAPH_STROKE);
        for (int i = 0; i < points.size() - 1; i++) {
            int x1 = points.get(i).x;
            int y1 = points.get(i).y;
            int x2 = points.get(i + 1).x;
            int y2 = points.get(i + 1).y;
            g2.drawLine(x1, y1, x2, y2);
        }

        g2.setStroke(oldStroke);
        g2.setColor(GRAPH_POINT_COLOR);
        for (int i = 0; i < points.size(); i++) {
            int x = points.get(i).x - GRAPH_POINT_WIDTH / 2;
            int y = points.get(i).y - GRAPH_POINT_WIDTH / 2;
            int ovalW = GRAPH_POINT_WIDTH;
            int ovalH = GRAPH_POINT_WIDTH;
            g2.fillOval(x, y, ovalW, ovalH);
        }
    }
}
