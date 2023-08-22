// package com.example;

import java.awt.*;
import java.awt.image.*;

import java.awt.event.*;
import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.filechooser.FileFilter;

import lib.*;

public class imgOps extends JPanel {

    // initialize some variables that are used in different functions
    static File imageFile = null;

    static BufferedImage origImage = null;
    static BufferedImage greyImage = null;
    static BufferedImage dithImage = null;
    static BufferedImage autoImage = null;

    static JFrame mainWindowFrame;
    static JPanel mainPanel;

    static int mode = 0;

    static File openFile() {

        JFileChooser fChooser = new JFileChooser();

        fChooser.setCurrentDirectory(new File(System.getProperty("user.home")));
        fChooser.setFileSelectionMode(JFileChooser.FILES_ONLY);

        // file filter so only directories and bmp files appear
        fChooser.setFileFilter(new FileFilter() {
            @Override
            public String getDescription() {
                return "bitmap file (*.bmp)";
            }

            @Override
            public boolean accept(File f) {
                String filename = f.getName().toLowerCase();
                return (filename.endsWith(".bmp") || f.isDirectory());
            }
        });

        int r = fChooser.showOpenDialog(mainWindowFrame);
        if (r == JFileChooser.APPROVE_OPTION) {
            File selectedFile = fChooser.getSelectedFile();
            if (selectedFile != null) {
                Path filePath = selectedFile.toPath();

                // intended to check the mimetype of the file
                // however a imposter (such as a pdf) can fool it
                String mimeType = "";
                try {

                    mimeType = Files.probeContentType(filePath);

                } catch (Exception e) {

                    System.out.println("Something went wrong. 2");
                    System.out.println(e.toString());

                }
                if (mimeType.compareToIgnoreCase("image/bmp") == 0) {

                    return selectedFile;

                } else {

                    System.out.println("error, invalid mimetype: ".concat(mimeType));
                    // erDialogue();
                    return null;

                }
            }
        }
        return null;
    }

    public void paintComponent(Graphics g) {
        if (mode == 0) { // first stage, initial image and greyscale image
            if (origImage != null) {

                g.drawImage(origImage, 0, 0, null);

            } else {

                g.setFont(new Font(Font.SANS_SERIF, Font.PLAIN, 50));
                g.drawString("no image uploaded,", 200, 460);
                g.drawString("start the program again", 200, 520);

            }
            if (greyImage != null) {
                g.drawImage(greyImage, origImage.getWidth(), 0, null);
            }
        } else if (mode == 1) { // second stage, greyscale and dithered image
            if (greyImage != null) {

                g.drawImage(greyImage, 0, 0, null);

            } else {

                g.setFont(new Font(Font.SANS_SERIF, Font.PLAIN, 50));
                g.drawString("no image uploaded,", 200, 460);
                g.drawString("start the program again", 200, 520);

            }
            if (dithImage != null) {
                g.drawImage(dithImage, origImage.getWidth(), 0, null);
            } else {
                g.drawString("error", (int) (origImage.getWidth() * 1.3), (int) (origImage.getHeight() * 0.9));
            }
        } else { // Third stage, regular and auto leveled image
            if (origImage != null) {

                g.drawImage(origImage, 0, 0, null);

            } else {

                g.setFont(new Font(Font.SANS_SERIF, Font.PLAIN, 50));
                g.drawString("no image uploaded,", 200, 460);
                g.drawString("start the program again", 200, 520);

            }
            if (autoImage != null) {
                g.drawImage(autoImage, origImage.getWidth(), 0, null);
            } else {
                g.drawString("error", (int) (origImage.getWidth() * 1.3), (int) (origImage.getHeight() * 0.9));
            }
        }
    }

    // convert the file to an image
    // if it fails, origImage is set to null, and shows an error
    static void imageConvert() {
        if (imageFile != null) {
            BufferedImage i = null;

            try {
                i = ImageIO.read(imageFile);
                mainWindowFrame.setSize(i.getWidth() * 2 + 10, i.getHeight() + 75 + 10);
                mainPanel.setBounds(5, 5, i.getWidth() * 2, i.getHeight());

            } catch (Exception e) {
                erDialogue();
                i = null;
            }
            origImage = i;

        }
    }

    // show an error popup
    static void erDialogue() {

        final JDialog jd = new JDialog();
        jd.setTitle("Error");
        jd.setSize(300, 140);

        JLabel erLabel = new JLabel("Something went wrong.");

        JButton okButton = new JButton("ok");

        Container contentPane = jd.getContentPane();
        contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.PAGE_AXIS));

        okButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                jd.setVisible(false);
                jd.dispose();
            }
        });

        // just ui stuff
        contentPane.add(erLabel);
        Box.createHorizontalStrut(10);
        contentPane.add(okButton);
        Box.createHorizontalStrut(20);

        erLabel.setAlignmentX(CENTER_ALIGNMENT);
        okButton.setAlignmentX(CENTER_ALIGNMENT);

        erLabel.setMinimumSize(new Dimension(50, 60));
        erLabel.setMaximumSize(new Dimension(170, 60));
        okButton.setMinimumSize(new Dimension(100, 30));
        okButton.setMaximumSize(new Dimension(100, 30));

        jd.setVisible(true);
    }

    // PART 2
    // if origImage is not null, generates a greyscale image, and stores the image
    // in greyImage
    static void generateGreyImage() {
        if (origImage != null) {
            int w = origImage.getWidth();
            int h = origImage.getHeight();
            BufferedImage i = new BufferedImage(w, h, BufferedImage.TYPE_BYTE_GRAY);

            for (int x = 0; x < w; x++) {
                for (int y = 0; y < h; y++) {
                    i.setRGB(x, y, origImage.getRGB(x, y));
                }
            }

            greyImage = i;

        }
    }

    // PART 3
    // if greyimage is not null, generates a dithered (binary) image, and stores the
    // image in dithImage
    static void generateDithImage() {
        if (greyImage != null) {
            
            final int[][] matrix = { { 0, 8, 2, 10 }, { 12, 4, 14, 6 }, { 3, 11, 1, 9 }, { 15, 7, 13, 5 } }; //dithering matrix
            int w = origImage.getWidth();
            int h = origImage.getHeight();
            BufferedImage i = new BufferedImage(w, h, BufferedImage.TYPE_BYTE_BINARY);

            for (int x = 0; x < w; x++) {
                for (int y = 0; y < h; y++) {
                    int val = lib.rgbToGrey(greyImage.getRGB(x, y)) / 16;
                    if (val >= matrix[x % 4][y % 4]) {
                        i.setRGB(x, y, 0xffffff);
                    } else {
                        i.setRGB(x, y, 0x0);
                    }
                }
            }
            dithImage = i;
        }
    }

    // PART 4
    // if origImage is not null, generates an auto leveled image, and stores it in
    // the static variable autoImage
    static void generateAutoImage() {
        if (origImage != null) {
            int w = origImage.getWidth();
            int h = origImage.getHeight();
            int[][] rChannel = new int[w][h];

            int[][] bChannel = new int[w][h];

            int[][] gChannel = new int[w][h];
            int[] greyCount = new int[256];

            BufferedImage i = new BufferedImage(w, h, origImage.getType()); // start with the original image
            // int avgCount = 0;
            for (int x = 0; x < w; x++) {
                for (int y = 0; y < h; y++) {
                    int rgb = origImage.getRGB(x, y);
                    int r = lib.rgbToRed(rgb);
                    int b = lib.rgbToBlue(rgb);
                    int g = lib.rgbToGreen(rgb);

                    rChannel[x][y] = r;
                    bChannel[x][y] = b;
                    gChannel[x][y] = g;
                    greyCount[lib.rgbToGrey(rgb)] += 1;
                    // avgCount += 1;
                }
            }
            int lmax = 0;
            int lmin = w * h;
            int count = 0;
            for (int l = 0; l < 256; l++) {
                count = count + greyCount[l];
                if (count <= (w * h) / 10) {// find the range between rmin and rmax that contains most of the levels in
                                            // the image
                    lmin = l;
                } else if (count <= (w * h) * (9) / 10) {
                    lmax = l;
                }

            }

            lib.scaleLvl(lmax, lmin, rChannel);
            lib.scaleLvl(lmax, lmin, bChannel);
            lib.scaleLvl(lmax, lmin, gChannel);

            for (int x = 0; x < w; x++) {
                for (int y = 0; y < h; y++) {
                    int r = rChannel[x][y];
                    int b = bChannel[x][y];
                    int g = gChannel[x][y];

                    i.setRGB(x, y, lib.colsToRgb(r, g, b));
                }
            }
            autoImage = i;
        }

    }

    public static void main(String[] args) {

        // main window
        mainWindowFrame = new JFrame("Image Operations");
        mainWindowFrame.setSize(1000, 1000);
        Container mainContentPane = mainWindowFrame.getContentPane();

        mainPanel = new imgOps();
        mainPanel.setBounds(5, 5, 800, 800);
        // mainPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK, 5));

        JButton nextButton = new JButton("next");

        // menu bar
        JMenuBar menuBar = new JMenuBar();
        JMenu exitMenu = new JMenu("Exit");
        JMenuItem exitMenuItem = new JMenuItem("Exit Program");

        exitMenuItem.addActionListener(new ActionListener() { // exit menu item behavior
            public void actionPerformed(ActionEvent e) {
                mainWindowFrame.setVisible(false);
                mainWindowFrame.dispose();
            }
        });

        // add everything to the main window
        mainContentPane.setLayout(new BoxLayout(mainContentPane, BoxLayout.PAGE_AXIS));

        mainContentPane.add(mainPanel);
        Box.createVerticalStrut(30);
        mainContentPane.add(nextButton);
        Box.createVerticalStrut(30);
        nextButton.setMinimumSize(new Dimension(120, 50));
        nextButton.setMaximumSize(new Dimension(120, 50));
        nextButton.setAlignmentX(CENTER_ALIGNMENT);

        mainWindowFrame.setSize(1000, 1000);
        mainWindowFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // add to menu bar
        mainWindowFrame.setJMenuBar(menuBar);
        menuBar.add(exitMenu);
        exitMenu.add(exitMenuItem);

        // the main body of what the programs doing
        File file1 = openFile();

        if (file1 != null) { // check if valid, and convert
            imageFile = file1;// converts to an image object and paint
            imageConvert();
            mainPanel.repaint();
        } else {
            erDialogue(); // error with file opening
        }

        // image generation

        mainWindowFrame.setVisible(true); // set visible before generating, in case it takes a long time so it doesnt
                                          // look
        // like its broken
        generateGreyImage();
        generateDithImage();
        generateAutoImage();

        mainPanel.repaint(); // panel is painted once its done generating to show greyscale image

        // set frame to visible
        mainWindowFrame.setVisible(true);
        nextButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) { // cycles through the stages
                mode += 1;
                if (mode > 2) {
                    mode = 0;
                }
                mainPanel.repaint();
            }
        });

    }
}
