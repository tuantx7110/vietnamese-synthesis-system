package signalanalysis;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.RenderingHints;
import java.awt.Stroke;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import javax.swing.JPanel;

public class GraphPainter extends JPanel {

    public static final int BORDER_GAP = 100;
    private static final int GRAPH_POINT_WIDTH = 1;
    private static final Color GRAPH_COLOR = Color.BLACK;
    private static final Color GRAPH_POINT_COLOR = Color.BLACK;
    private static final Stroke GRAPH_STROKE = new BasicStroke(0.7f);
    private LinkedList<Long> samples;
    private int Ox;
    private List<Point> points;
    private double xScale;
    private double yScale;

    public GraphPainter(Dimension dimension) {
        this.setBackground(Color.WHITE);
        this.setBorder(javax.swing.BorderFactory.createEtchedBorder());
        this.setSize(dimension);
        this.setPreferredSize(dimension);
        this.setVisible(true);
        samples = new LinkedList<Long>();
        points = new ArrayList<Point>();
        Ox = (int) (dimension.getHeight() / 2);
    }

    public void refresh() {
        this.revalidate();
        this.repaint();
    }

    public void drawGraph(int data[]) {
        long a[] = new long[data.length];
        for (int i = 0; i < data.length; ++i) {
            a[i] = data[i];
        }
        drawGraph(a);
    }

    public void drawGraph(long data[]) {
        long vmax = Long.MIN_VALUE;
        samples.clear();
        for (int i = 0; i < data.length; ++i) {
            if (vmax < Math.abs(data[i])) {
                vmax = Math.abs(data[i]);
            }
            samples.add(data[i]);
        }
        System.out.println("Samples = " + samples.size());
        xScale = ((double) getWidth() - 2 * BORDER_GAP) / (data.length - 1);
        yScale = ((double) getHeight() - 2 * BORDER_GAP) / (vmax - 1);
        refresh();
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
            long val = (Long) a[i];
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
