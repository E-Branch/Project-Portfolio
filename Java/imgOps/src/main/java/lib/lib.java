package lib;

public class lib {
    // extracts the red component from a rgb int
    public static int rgbToRed(int rgb) {
        return (rgb & 0xff0000) >> 16; // third byte
    }

    // extracts the green component from rgb
    public static int rgbToGreen(int rgb) {
        return (rgb & 0xff00) >> 8; // second byte
    }

    // extracts the blue component from rgb
    public static int rgbToBlue(int rgb) {
        return (rgb & 0xff); // first 8 bits
    }

    // converts rbg int to greyscale (0,...,255)
    public static int rgbToGrey(int rgb) {
        int b = rgbToBlue(rgb);
        int g = rgbToGreen(rgb);
        int r = rgbToRed(rgb);

        return (int) Math.round(0.299 * r + 0.587 * g + 0.114 * b);
    }

    // converts 3 colour channels to a rgb int val
    public static int colsToRgb(int r, int g, int b) {
        int rb = (r << 16) & 0xff0000;
        int gb = g << 8 & 0xff00;
        int bb = b & 0xff;
        int a = 0xff000000;
        return (a | rb | gb | bb);
    }

    // counts the number of pixels at level l in channel "channel"
    // didn't use because its ridiculously inefficient
    public static int countLvls(int l, int[][] channel) {
        int w = channel.length;
        int h = channel[0].length;
        int count = 0;
        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                if (l == channel[x][y]) {
                    count += 1;
                    // System.out.println(count);
                }
            }
        }
        return count;
    }

    // scales the values in channel so that lowerst -> 0, highest -> 255
    // changes channel directly
    public static void scaleLvl(int upper, int lower, int[][] channel) {
        int w = channel.length;
        int h = channel[0].length;
        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                double l = (double) channel[x][y];

                l = ((l - (1 / 3) * lower) / (upper - lower)) * 255;

                int k = (int) Math.round(l);// round and make sure <255
                if (k > 255) {
                    k = 255;
                }
                channel[x][y] = k;
                // System.out.println(k);
            }
        }
    }
}
