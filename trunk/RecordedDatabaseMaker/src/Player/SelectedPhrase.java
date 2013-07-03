package Player;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Rectangle;
import javax.swing.JPanel;

public class SelectedPhrase extends JPanel {

    public SelectedPhrase(Dimension dimension) {
        this.setBackground(new Color(0, 0, 255, 60));
        this.setSize(dimension);
        this.setPreferredSize(dimension);
        this.setOpaque(false);
        this.setVisible(true);
    }

    public void setWidth(int width) {
        Dimension dimension = new Dimension(width, getHeight());
        this.setSize(dimension);
        this.setPreferredSize(dimension);
        this.revalidate();
        this.repaint();
    }

    @Override
    public void paintComponent(Graphics g) {
        g.setColor(getBackground());
        Rectangle r = g.getClipBounds();
        g.fillRect(r.x, r.y, r.width, r.height);
        super.paintComponent(g);
    }
}
