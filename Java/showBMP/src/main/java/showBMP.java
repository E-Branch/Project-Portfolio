// package com.example;

import java.awt.*;

import java.awt.event.*;
import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.filechooser.FileFilter;

public class showBMP extends JPanel {

    // initialize some variables that are used in different functions
    static File imageFile = null;
    static Image image = null;
    static JFrame frame;
    static JPanel panel;

    static File openFileAction() {

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

        int r = fChooser.showOpenDialog(frame);
        if (r == JFileChooser.APPROVE_OPTION) {
            File selectedFile = fChooser.getSelectedFile();
            if (selectedFile != null) {
                Path filePath = selectedFile.toPath();

                // intended to check the mimetype of the file
                // wow probeContentType seems not very good, at least on my computer,
                // a imposer (such as a pdf) fools it completely
                // online mime type checkers can figure out the correct mimetype, so it should
                // be possible
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
        if (image != null) {

            g.drawImage(image, 0, 0, null);

        } else {

            g.setFont(new Font(Font.SANS_SERIF, Font.PLAIN, 50));
            g.drawString("no image uploaded", 250, 480);

        }
    }

    // convert the file to an image
    static void imageConvert() {
        if (imageFile != null) {
            Image i = null;

            try {
                i = ImageIO.read(imageFile);
                frame.setSize(i.getWidth(null), i.getHeight(null));

            } catch (Exception e) {
                erDialogue();
                i = null;
            }
            image = i;

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

    public static void main(String[] args) {

        // create the main window
        frame = new JFrame("Show BMP");

        panel = new showBMP();
        panel.setBounds(5, 5, 990, 990);
        panel.setBorder(BorderFactory.createLineBorder(Color.BLACK, 5));

        // create the menu bar
        JMenuBar menuBar = new JMenuBar();
        JMenu fileMenu = new JMenu("File");
        JMenuItem openMenuItem = new JMenuItem("Open File"); // , openFileAction

        JMenu exitMenu = new JMenu("Exit");
        JMenuItem exitMenuItem = new JMenuItem("Exit Program");

        openMenuItem.addActionListener(new ActionListener() { // openfile menu behaviour
            public void actionPerformed(ActionEvent e) {

                File bmpFile = openFileAction();

                if (bmpFile != null) {

                    imageFile = bmpFile;
                    imageConvert(); // converts the file to an image object, then paints it on panel

                    panel.repaint();

                } else {

                    erDialogue();

                }
            }
        });

        exitMenuItem.addActionListener(new ActionListener() { // exit menu item behavior
            public void actionPerformed(ActionEvent e) {
                frame.setVisible(false);
                frame.dispose();
            }
        });

        // add everything to the main window and open it

        frame.add(panel);

        frame.setJMenuBar(menuBar);
        menuBar.add(fileMenu);
        fileMenu.add(openMenuItem);
        menuBar.add(exitMenu);
        exitMenu.add(exitMenuItem);

        frame.setSize(1000, 1000);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}
