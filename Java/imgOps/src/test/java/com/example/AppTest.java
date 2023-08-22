package com.example;

import static org.junit.Assert.assertTrue;

import org.junit.Test;
import lib.*;

/**
 * Unit test for simple App.
 */
public class AppTest {
    /**
     * Rigorous Test :-)
     */
    @Test
    public void shouldAnswerWithTrue() {
        assertTrue(true);
        assertTrue(
                0xffffff == lib.colsToRgb(lib.rgbToRed(0xffffff), lib.rgbToGreen(0xffffff), lib.rgbToBlue(0xffffff)));
    }
}
