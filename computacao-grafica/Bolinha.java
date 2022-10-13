import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.Graphics;
import java.awt.event.ActionEvent;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.Timer;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

public class Bolinha {
    
    public static void main(final String[] args) {
        new Bolinha();
    }
    
    public Bolinha() {
        EventQueue.invokeLater(new Runnable() {
            
            @Override
            public void run() {
                try {
                    UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
                } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | UnsupportedLookAndFeelException ex) {
                }
                
                final JFrame frame = new JFrame("Circunferência se Movendo!!");
                frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                frame.setLayout(new BorderLayout());
                frame.add(new TestPane());
                frame.pack();
                frame.setLocationRelativeTo(null);
                frame.setVisible(true);
            }
        });
    }
    
    public class TestPane extends JPanel {
        
        private int x = 200;
        
        private final int y = 200;
        
        private final int radius = 20;
        
        private int xDelta = 2;
        
        public TestPane() {
            final Timer timer = new Timer(40, (final ActionEvent e) -> {
                
                TestPane.this.x += TestPane.this.xDelta;
                if (TestPane.this.x + (TestPane.this.radius * 2) > TestPane.this.getWidth()) {
                    TestPane.this.x = TestPane.this.getWidth() - (TestPane.this.radius * 2);
                    TestPane.this.xDelta *= -1;
                } else if (TestPane.this.x < 200) {
                    TestPane.this.x = 200;
                    TestPane.this.xDelta *= -1;
                }
                TestPane.this.repaint();
            });
            timer.start();
        }
        
        @Override
        public Dimension getPreferredSize() {
            return new Dimension(500, 500);
        }
        
        @Override
        protected void paintComponent(final Graphics g) {
            super.paintComponent(g);
            g.setColor(Color.RED);
            g.fillOval(this.x, this.y - this.radius, this.radius * 2, this.radius * 2);
        }
    }
    
}
