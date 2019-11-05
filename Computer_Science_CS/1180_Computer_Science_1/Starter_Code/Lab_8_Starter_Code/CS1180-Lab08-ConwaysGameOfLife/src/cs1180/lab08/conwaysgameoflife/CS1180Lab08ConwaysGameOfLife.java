package cs1180.lab08.conwaysgameoflife;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;
import javafx.util.Duration;

/**
 *
 * @author Doom
 */
public class CS1180Lab08ConwaysGameOfLife extends Application {

    // CS 1180 Note:  Feel free to change these values during testing, but 
    // return them to the initial provided values in your final program.
    public static final int GAME_BOARD_WIDTH_IN_CELLS = 50;
    public static final int GAME_BOARD_HEIGHT_IN_CELLS = 50;
    public static final int CELL_SIZE_IN_PIXELS = 10;
    public static int tickNum = 0;
    private static Rectangle[][] graphicCells = new Rectangle[GAME_BOARD_WIDTH_IN_CELLS][GAME_BOARD_HEIGHT_IN_CELLS];
    private static Boolean[][] gameCellAlive = new Boolean[GAME_BOARD_WIDTH_IN_CELLS][GAME_BOARD_HEIGHT_IN_CELLS];
    private static final double gameUpdatesPerSecond = 0.5;

    /**
     * This method updates the game board according to the rules:  <BR>
     * 1. If a live cell has fewer than 2 live neighbors, it dies  <BR>
     * 2. If a live cell has more than 3 live neighbors, it dies   <BR>
     * 3. If a live cell has 2 live neighbors stays alive/dead (no change) <BR>
     * 4. If a dead cell has exactly 3 live neighbors, it comes to life  <BR>
     *
     * @param gameCellAlive a 2D Boolean array which contains TRUE if the cell
     * at that board location is live and FALSE if the cell at that board
     * location is dead. This method updates this array for the next cycle of
     * the simulation according to rules for Conway's game of life (listed
     * above).
     *
     * CS1180 NOTE: YOU NEED TO IMPLEMENT THIS METHOD!
     */
    public static void updateLife(Boolean[][] gameCellAlive) {

        // METHOD STUB - This method needs to be implemented!
    } // end method updateLife

    /**
     *
     * @param gameBoard A 2D boolean array containing the current life status of
     * each cell at each x,y coordinate on the board. true indicates that the
     * cell is alive. false indicates no life in that cell.
     * @param colIndex The x position of the cell in the game board whose
     * neighbors are to be counted.
     * @param rowIndex The y position of the cell in the game board whose
     * neighbors are to be counted.
     * @return the number of cells adjacent to the cell at the specified row and
     * column that contain life. This value ranges between 0 (no adjacent cells
     * contain life) and 8 (all adjacent cells contain life).
     *
     * CS1180 Note: YOU NEED TO IMPLEMENT THIS METHOD
     */
    public static int getLifeNeighborCount(Boolean[][] gameBoard, int colIndex, int rowIndex) {
        // METHOD STUB - THIS METHOD NEEDS TO BE IMPLEMENTED
        int neighborCount = 0;
        return neighborCount;
    } // end method getLifeNeighborCount

    /**
     * Set up initial game state
     *
     * @param gameCellAlive A 2D Boolean array representing the cells of the
     * game board. Live cells are set to true, dead cells are set to false. This
     * method sets a subset of gameCellAlive to true/alive to create the initial
     * life form for the simulation.
     *
     * CS 1180 Note: You may modify this method.
     */
    private static void setupInitialGameState(Boolean[][] gameCellAlive) {

        // Initialize board so that all cells are dead
        for (int i = 0; i < gameCellAlive.length; i++) {
            for (int j = 0; j < gameCellAlive[0].length; j++) {
                gameCellAlive[i][j] = false;
            } // end for each cell in row
        } // end for each row of cells

        // CS1180 notes - Three initial lifeforms are included to help with
        // testing.  The block just sits there, unchanging.  Test that one
        // first.
        int x = GAME_BOARD_WIDTH_IN_CELLS / 2;
        int y = GAME_BOARD_HEIGHT_IN_CELLS / 2;

        // Place initial lifeform Block
        gameCellAlive[x][y] = true;
        gameCellAlive[x][y+1] = true;
        gameCellAlive[x+1][y] = true;
        gameCellAlive[x+1][y+1] = true;
        
        // Place initial lifeform Blinker
//        gameCellAlive[x][y] = true;
//        gameCellAlive[x][y+1] = true;
//        gameCellAlive[x][y+2] = true;
        
        // Place initial lifeform glider
//        x = 0; 
//        y = 0;
//        gameCellAlive[x][y] = false;
//        gameCellAlive[x][y+1] = true;
//        gameCellAlive[x][y+2] = false;
//        gameCellAlive[x+1][y] = false;
//        gameCellAlive[x+1][y+1] = false;
//        gameCellAlive[x+1][y+2] = true;
//        gameCellAlive[x+2][y] = true;
//        gameCellAlive[x+2][y+1] = true;
//        gameCellAlive[x+2][y+2] = true;
        
        // Place initial lifeform R-pentomino
//        gameCellAlive[x][y] = false;
//        gameCellAlive[x][y + 1] = true;
//        gameCellAlive[x][y + 2] = true;
//        gameCellAlive[x + 1][y] = true;
//        gameCellAlive[x + 1][y + 1] = true;
//        gameCellAlive[x + 1][y + 2] = false;
//        gameCellAlive[x + 2][y] = false;
//        gameCellAlive[x + 2][y + 1] = true;
//        gameCellAlive[x + 2][y + 2] = false;

    }  // end method setupInitialGameState

    /**
     * This method sets up the graphics/window environment.
     *
     * CS1180 note: You do not need to understand this method. Do not modify
     * this method.
     */
    @Override
    public void start(Stage primaryStage) {

        // Display game window
        Pane window = new Pane();
        int windowWidth = GAME_BOARD_WIDTH_IN_CELLS * CELL_SIZE_IN_PIXELS;
        int windowHeight = GAME_BOARD_HEIGHT_IN_CELLS * CELL_SIZE_IN_PIXELS;
        Scene scene = new Scene(window, windowWidth, windowHeight);
        primaryStage.setTitle("CS 1180 Conway's Game Of Life");
        primaryStage.setScene(scene);
        primaryStage.show();

        // Create cells for window/graphical visualization
        for (int x = 0; x < GAME_BOARD_WIDTH_IN_CELLS; x++) {
            for (int y = 0; y < GAME_BOARD_HEIGHT_IN_CELLS; y++) {
                Rectangle r = new Rectangle(x * CELL_SIZE_IN_PIXELS, y * CELL_SIZE_IN_PIXELS, CELL_SIZE_IN_PIXELS, CELL_SIZE_IN_PIXELS);
                graphicCells[x][y] = r;
                window.getChildren().add(r);
            } // end for each cell in row
        } // end for each row

        // Start animation
        KeyFrame speed = new KeyFrame(Duration.millis(1000 * gameUpdatesPerSecond), e -> gameTick());
        Timeline animation = new Timeline(speed);
        animation.setCycleCount(Timeline.INDEFINITE);
        animation.play();
    } // end method start

    /**
     * This method is automatically called by the animation routine once every
     * game tick to update the graphical display. This method sets the cells in
     * the 2D graphical display to WHITE or BLACK based on the whether the
     * corresponding cell in the 2D boolean array gameCellAlive is TRUE or FALSE
     * (respectively).
     *
     * CS 1180 note: You do not need to understand this method. Do not modify
     * this method.
     */
    private void gameTick() {
        for (int x = 0; x < GAME_BOARD_WIDTH_IN_CELLS; x++) {
            for (int y = 0; y < GAME_BOARD_HEIGHT_IN_CELLS; y++) {
                if (gameCellAlive[x][y] == true) {
                    graphicCells[x][y].setFill(Color.WHITE);
                } else {
                    graphicCells[x][y].setFill(Color.BLACK);
                }
            } // end for each cell in row
        } // end for each row
        tickNum++;
        System.out.println("---- end of tick #" + tickNum + " ----");
        updateLife(gameCellAlive);
    } // end method gameTick

    /**
     *
     * CS 1180 Note: Do not modify this method.
     */
    public static void main(String[] args) {
        setupInitialGameState(gameCellAlive);
        launch(args);
    } // end method main

} // end class ConwaysGameOfLife
