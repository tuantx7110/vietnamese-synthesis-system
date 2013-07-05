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
    private List<Integer> samples;
    private WavFile wavFile;
    private int startFrame;
    private int finishFrame;
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
        samples = new ArrayList<Integer>();
        Ox = height / 2;
        currentOxLen = BUFFER_SIZE - 1;
        xScale = ((double) getWidth() - 2 * BORDER_GAP) / currentOxLen;
        yScale = ((double) getHeight() - 2 * BORDER_GAP) / (DEFAULT_MAX_SCORE - 1);
        points = new ArrayList<Point>();
        startFrame = 0;
        finishFrame = 0;

        initGraph();
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
            samples.remove(0);
            startFrame++;
        }

        int a[] = new int[numberFrames];
        numberFrames = wavFile.readFrames(a, numberFrames);

        for (int i = 0; i < numberFrames; ++i) {
            samples.add(a[i]);
            finishFrame++;
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

        setStartFrame(0);
        setFinishFrame(n - 1);

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

        Graphics2D g2 = (Graphics2D) g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        points.clear();
        for (int i = 0; i < samples.size(); ++i) {
            int x = (int) (i * xScale + BORDER_GAP);
            int y = (int) (Ox - samples.get(i) * yScale);
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

    /**
     * @return the startFrame
     */
    public int getStartFrame() {
        return startFrame;
    }

    /**
     * @param startFrame the startFrame to set
     */
    public void setStartFrame(int startFrame) {
        this.startFrame = startFrame;
    }

    /**
     * @return the finishFrame
     */
    public int getFinishFrame() {
        return finishFrame;
    }

    /**
     * @param finishFrame the finishFrame to set
     */
    public void setFinishFrame(int finishFrame) {
        this.finishFrame = finishFrame;
    }
}
