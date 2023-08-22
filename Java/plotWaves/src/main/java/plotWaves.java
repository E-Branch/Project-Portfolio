import java.awt.*;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Color;
import java.awt.event.*;
import javax.swing.*;

//import java.lang.Integer.*;
//import java.lang.String.*;
//import java.lang.Math.*;

/*
 * max y for each x
 * 1 - 1
 * 2 - 2
 * 3 - 3
 * 4 - 4
 * 5 - 4
 * 6 - 5
 * 7 - 6
 * 8 - 7
 * 9 - 7
 * 10 - 8
 */

public class plotWaves extends JPanel {
    final static int maxY[] = { 1, 2, 3, 4, 4, 5, 6, 7, 7, 8 }; // max value needed for the y axis for the graph to fit,
                                                                // for each input value
    final static Color cols[] = { Color.RED, Color.GREEN, Color.BLUE, Color.ORANGE, Color.PINK, Color.MAGENTA,
            Color.CYAN, Color.YELLOW, new Color(138, 96, 63), new Color(145, 0, 201), new Color(92, 212, 0),
            new Color(0, 156, 132), new Color(154, 178, 217) };

    static int inputValue; // the input value

    static JFrame inputFrame;
    static JTextField inputField;

    // lots of variables and looks a bit messy
    // but it made the drawing stuff easier to understand & read
    static int canvasX = 1400;
    static int canvasY = 800;
    static int plotWidth = canvasX - 80;
    static int plotHeight = canvasY - 120;

    static int leftMarginX = 60;
    static int topMarginY = 20;
    static int rightMarginX = plotWidth + leftMarginX;
    static int bottomMarginY = plotHeight + topMarginY;

    static int plotCenter = ((plotHeight) / 2) + topMarginY;

    static int scaleX = (int) (plotWidth / (2 * (Math.PI)));
    static int scaleY = 0;

    static class twobit {
        boolean a = false;
        boolean b = false;

        twobit(int i) {
            if (i > 2) {
                i = 2;
            } else if (i < -1) {
                i = -1;
            }
            if (i == 2) {
                a = true;
                b = true;
            }
            if (i == 1) {
                a = true;
                b = false;
            }
            if (i == 0) {
                a = false;
                b = true;
            }
            if (i == -1) {
                a = false;
                b = false;
            }
        }

        twobit(boolean x, boolean y) {
            a = x;
            b = y;
        }

        int toInt() {
            int i = 0;
            if (a && b) {
                i = 2;
            }
            if (a && !b) {
                i = 1;
            }
            if (!a && b) {
                i = 0;
            }
            if (!a && !b) {
                i = -1;
            }
            return i;
        }
    }

    // draws the lines and lables of the x axis
    static void paintXAxis(Graphics g) {
        int q = (plotWidth / 4);

        g.drawLine(leftMarginX, topMarginY, leftMarginX, bottomMarginY);
        g.drawString("0", leftMarginX - 5, bottomMarginY + 20);

        g.drawLine((2 * q) + leftMarginX, topMarginY, (plotWidth / 2) + leftMarginX, bottomMarginY);
        g.drawString("π", (plotWidth / 2) + 55, bottomMarginY + 20);

        g.drawLine(q + leftMarginX, topMarginY, (plotWidth / 4) + leftMarginX, bottomMarginY);
        g.drawString("π/2", (plotWidth / 4) + 50, bottomMarginY + 20);

        g.drawLine((3 * q) + leftMarginX, topMarginY, (3 * plotWidth / 4) + 60, bottomMarginY);
        g.drawString("3π/2", (3 * plotWidth / 4) + 45, bottomMarginY + 20);

        g.drawLine(rightMarginX, topMarginY, rightMarginX, bottomMarginY);
        g.drawString("2π", rightMarginX - 15, bottomMarginY + 20);

    }

    // Draws the lines and lables of the y axis
    static void paintYAxis(Graphics g) {
        int max = maxY[inputValue - 1];
        float segmentSize = (float) (plotHeight) / (float) (2 * max);

        for (int k = 0; k <= (2 * max); k++) {

            g.drawLine(leftMarginX,
                    (int) (k * segmentSize) + topMarginY,
                    rightMarginX,
                    (int) (k * segmentSize) + topMarginY);

            g.drawString(String.valueOf(max - k),
                    leftMarginX - 20, (int) (k * segmentSize) + topMarginY + 5);

        }
    }

    // paints the lines of sin(x), sin(2x), ... , sin((n-1)x), and sin (n*x)
    static void paintLine(Graphics g, int n) {

        double[] sinArray = new double[canvasX - 20 - leftMarginX - 1];
        sinArray[0] = 0.0;

        for (int x = 1; x < canvasX - 20 - leftMarginX - 1; x++) {

            sinArray[x] = Math.sin(n * ((double) x / (double) scaleX)); // memoization
            // System.out.println(String.valueOf(Math.sin(n * ((double) x / (double)
            // scaleX))));

            g.drawLine(
                    x + leftMarginX, // (x-1) + leftMarginX + 1
                    (int) (-1 * sinArray[x - 1] * scaleY) + plotCenter,
                    x + leftMarginX + 1,
                    (int) (-1 * sinArray[x] * scaleY) + plotCenter);

        }
    }

    // paints the line sin(x) + sin(2x) + ... + sin(n*x)
    static void paintLinesSum(Graphics g, int n) {

        double[] sinArray = new double[canvasX - 20 - leftMarginX - 1];
        sinArray[0] = 0.0;

        for (int x = 1; x < canvasX - 20 - leftMarginX - 1; x++) {

            for (int k = 1; k <= n; k++) {
                sinArray[x] = sinArray[x] + Math.sin((k * x) / (double) scaleX);
            }

            g.drawLine(
                    (x - 1) + leftMarginX + 1,
                    (int) (-1 * (sinArray[x - 1] * scaleY)) + plotCenter,
                    x + leftMarginX + 1,
                    (int) (-1 * (sinArray[x] * scaleY)) + plotCenter);

        }
    }

    // takes a quantized sample of sin(n*x) 10 times per second (pi) and stores it
    // in 2 bits (twobit) then draws it on the graph
    static void paintQuantSamp(Graphics g, int n) {
        twobit[] sinArray = new twobit[21];
        sinArray[0] = new twobit(0);
        // samples taken at (canvasX - 20 - leftMarginX - 1)/20 intervals

        for (int k = 1; k < 21; k++) {

            int x = k * (canvasX - 20 - leftMarginX - 1) / 20;
            int xp = (k - 1) * (canvasX - 20 - leftMarginX - 1) / 20;

            sinArray[k] = new twobit((int) (4 * Math.sin(n * ((double) x / (double) scaleX)))); // memoization

            g.drawLine(
                    xp + leftMarginX + 1,
                    (int) (-1 * (double) (sinArray[k - 1].toInt()) / 4 * (double) scaleY) + plotCenter,
                    x + leftMarginX + 1,
                    (int) (-1 * (double) (sinArray[k].toInt()) / 4 * (double) scaleY) + plotCenter);
        }
    }

    // paint
    public void paint(Graphics g) {
        Graphics2D g2 = (Graphics2D) g;

        // set the painting setting
        g.setColor(Color.BLACK);
        g2.setStroke(new BasicStroke(2));
        g.setFont(new Font(Font.SANS_SERIF, Font.PLAIN, 20));

        g.drawRect(leftMarginX, topMarginY, plotWidth, plotHeight); // border

        paintXAxis(g);

        paintYAxis(g);

        g2.setStroke(new BasicStroke(3)); // increase the line width

        int c;
        for (c = 1; c <= inputValue; c++) {
            g.setColor(cols[c - 1]); // set a new colour for each line
            paintLine(g, c);
        }

        g.setColor(cols[c]);
        paintQuantSamp(g, c);

        g.setColor(cols[c + 1]);
        paintLinesSum(g, inputValue); // draw the last line

    }

    public static void main(String[] args) {
        // create the frame to take the user input
        inputFrame = new JFrame("Plot Waves");
        inputField = new JTextField();
        inputField.setBounds(10, 10, 150, 50);
        JButton inputButton = new JButton("plot!");
        inputButton.setBounds(10, 70, 120, 50);

        inputFrame.add(inputField);
        inputFrame.add(inputButton);

        inputFrame.setSize(200, 200);
        inputFrame.setLayout(null);
        inputFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        inputFrame.setVisible(true); // activate the frame

        // add the action for when the user presses ok
        inputButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                // take the input and then open a window for plotting

                inputValue = 0;

                try {
                    inputValue = Integer.parseInt(inputField.getText());
                } catch (NumberFormatException E) { // if invalid text is entered, catch
                    inputValue = 1;
                }

                if (inputValue > 10) { // if values are out of range, set to edge
                    inputValue = 10;
                } else if (inputValue < 1) {
                    inputValue = 1;
                }
                scaleY = (int) ((plotHeight) / (2 * maxY[inputValue - 1]));

                // get rid of the input frame
                inputFrame.setVisible(false);
                inputFrame.dispose();

                // create a new frame, with a panel to draw oni, and open it
                JFrame plotFrame = new JFrame("Plot Waves");

                JPanel plotPanel = new plotWaves();
                plotPanel.setBounds(0, 0, canvasX, canvasY);
                plotPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK, 5));

                plotFrame.add(plotPanel);
                plotFrame.setSize(1400, 800);
                plotFrame.setLayout(null);
                plotFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

                plotFrame.setVisible(true);

            }
        });
    }

}
