import java.awt.*;
import java.util.*;

public class Animation {
 final static Scanner hehe = new Scanner(System.in); //global scanner
 public static int displayedShapes; //shapes to display
 public static int movements; //number of frames in animation
 public static String[] shapes = new String[20]; //= {"Square", "Circle"}; //"EC-Triangle"
 public static int[] shapeSizes = new int[20];//int array of size of every shape
 public static String[] shapeColors = new String[20];//string array with colors of every shape, enumerate possible values?
 public static int[] direction = new int[20]; //int array of direction for every shape
 public static int[] speed = new int [20];//int array of speed of every shape
 public static int[] xPos = new int[20];//int array of x value for top-left pos of every shape
 public static int[] yPos = new int [20];//int array of y value for top-left pos of every shape
 
 
 public static void main(String[] args) {
  System.out.println("UTSA - Fall 2021 - CS1083 - Section 002 - Project 3 - Written by Georgy Vinogradov\n");
  System.out.println("Please input width, height of the panel, # of shapes, # of times to move followed by the shape, size, color, direction, and speed of every shape: ");
  int panelWidth = hehe.nextInt(); //x-value of panel
  int panelHeight = hehe.nextInt(); //y-value of panel
  displayedShapes = hehe.nextInt(); //number of shape objects to store
  movements = hehe.nextInt(); //number of frames to animate
  
  //System.out.println("loop"); //testing
  
  getShapeInformation(); 
  DrawingPanel panel = new DrawingPanel(panelWidth, panelHeight); //instantiates a drawing panel object to be used in all methods
  initialPosition(panel);
  showShapesMoving(panel);
  
  Graphics g = panel.getGraphics(); //instantiates graphics for farewell shenanigans
  g.setColor(Color.PINK);//hehe
  g.drawString("Animated by Georgy Vinogradov" , panelWidth - 175, panelHeight); //farewell message

 }
 public static void getShapeInformation(){ //gathers user input for every shape to display in drawing panel, with a maximum of 20 unique shape objects
  for (int x = 0; x < displayedShapes; x++) 
  {
   shapes[x] = hehe.next();
   shapeSizes[x] = hehe.nextInt();
   shapeColors[x] = hehe.next();
   direction[x] = hehe.nextInt();
   speed[x] = hehe.nextInt();
   //System.out.println("one cycle"); //testing
  }
 }
 
 public static void initialPosition(DrawingPanel p){ //sets and displays every shape object's position to the center of the drawing panel, then pauses the panel for 100 ms
  for (int x = 0; x < displayedShapes; x++) 
  {
   xPos[x] = p.getWidth() / 2 - shapeSizes[x] / 2;
   yPos[x] = p.getHeight() / 2 - shapeSizes[x] / 2;
  }
  showShapes(p, true);
  p.sleep(100);
 }
 
 public static void showShapesMoving(DrawingPanel p){ //animation!
  for(int x = 0; x < movements; x++) {
   showShapes(p, false); //displays the shapes initial position on the panel for a frame
   changePositions(); //changes the shapes positions for a frame
   showShapes(p, true); //displays the shapes changed position for a frame
   p.sleep(100); //pauses panel for 100 ms
  }
  
  
 }
 
 public static void changePositions(){ //changes position of shape objects by their given direction and speed
  for(int x = 0; x < displayedShapes; x++) 
  {
   switch(direction[x]) 
   {
   case 0:
    xPos[x] = xPos[x] - speed[x]; //moves left
    break;
   case 2: 
    yPos[x] = yPos[x] - speed[x]; //moves up
    break;
   case 4: 
    xPos[x] = xPos[x] + speed[x]; //moves right
    break;
   case 6: 
    yPos[x] = yPos[x] + speed[x]; //moves down
    break;
   
   }
  }
 }
 
 public static void showShapes(DrawingPanel p, boolean idk){ //displays shape on panel
  for (int x = 0; x < displayedShapes; x++) {
   if(idk)
    graphicsSetColor(p, x);
   else
    setNoColor(p);
   
   if(shapes[x].equals("Square"))
    showSquare(p, x, idk);
   else
    showCircle(p, x, idk);
  }
 }
 
 public static void setNoColor(DrawingPanel p){ //sets color of "pen" to white
  Graphics g = p.getGraphics();
  g.setColor(Color.WHITE);
 }
 
 public static void graphicsSetColor(DrawingPanel p, int iter){ //sets color of a given shape object to the color received from input
  Graphics g = p.getGraphics();
  if(shapeColors[iter].equals("Red"))
   g.setColor(Color.RED);
  else if(shapeColors[iter].equals("Blue"))
   g.setColor(Color.BLUE);
  else if(shapeColors[iter].equals("Pink"))
   g.setColor(Color.PINK);
  else if(shapeColors[iter].equals("Yellow"))
   g.setColor(Color.YELLOW);
  else if(shapeColors[iter].equals("Green"))
   g.setColor(Color.GREEN);
  else if(shapeColors[iter].equals("Magenta"))
   g.setColor(Color.MAGENTA);
  else if(shapeColors[iter].equals("Cyan"))
   g.setColor(Color.CYAN);
  else if(shapeColors[iter].equals("Orange"))
   g.setColor(Color.ORANGE);
  else if(shapeColors[iter].equals("Dark_gray"))
   g.setColor(Color.DARK_GRAY);
  else if(shapeColors[iter].equals("Light_gray"))
   g.setColor(Color.LIGHT_GRAY);
  else if(shapeColors[iter].equals("Gray"))
   g.setColor(Color.GRAY);
  else
   g.setColor(Color.BLACK);
  
 }
 
 public static void showSquare(DrawingPanel p, int iter, boolean idk){ //draws a rectangle with its predetermined color and gives it a black outline if idk == true
  Graphics g = p.getGraphics();
  g.fillRect(xPos[iter], yPos[iter], shapeSizes[iter], shapeSizes[iter]);
  if(idk)
   g.setColor(Color.BLACK);
  g.drawRect(xPos[iter], yPos[iter], shapeSizes[iter], shapeSizes[iter]);
 }
 
 public static void showCircle(DrawingPanel p, int iter, boolean idk){ //draws a circle with its predetermined color from input and gives it a black outline if idk == true
  Graphics g = p.getGraphics();
  g.fillOval(xPos[iter], yPos[iter], shapeSizes[iter], shapeSizes[iter]);
  if(idk)
   g.setColor(Color.BLACK);
  g.drawOval(xPos[iter], yPos[iter], shapeSizes[iter], shapeSizes[iter]);
 }
}
