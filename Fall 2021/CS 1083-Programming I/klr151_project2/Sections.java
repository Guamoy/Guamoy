import java.util.*;

public class Sections
{
  final static Scanner gIN = new Scanner(System.in); //global scanner to be used in every method that takes user input
  public static int gClassSize; //number limiting size of class array throughout entire program lifespan
  public static double[] gGrades = new double[100]; //array containing grades of each class member, limited by gClassSize and accessed in every method
  
  public static void main(String[] args)
  {
    
    int loopCon;
    System.out.println("UTSA - Fall2021 - CS1083 - Section 002 - Project 2 - Written by Georgy Vinogradov");
    System.out.println("Please, enter the class size : ");
    gClassSize = gIN.nextInt(); //effective class size received from user
    //System.out.println(gClassSize);
    //add a bounds check for class size
    
    
    loopCon = 5; //sets loopCon to not enter switch and still be true                                    
    while(loopCon != 0) 
    {
      System.out.println("MAIN MENU\n0 – Exit, 1 – List, 2 – Report, 3 – Add/Modify Grade, 4 – Swap Grades\nSelect an option : ");  
      loopCon = gIN.nextInt(); //receives user input 
      if (loopCon > 4 || loopCon < 0) //validates user input
      {
        System.out.println("Value out of range, please, try again");
        continue;
      }
      switch(loopCon) //calls a method or breaks loop depending on user input
      {
        case 0:
          System.out.println("Thank you for using this program");
          break;
        case 1:
          listGrades();
          break;
        case 2:
          report();
          break;
        case 3:
          addModifyGrade();
          break;
        case 4:
          swapGrades();
          break;
      }
    }
  }
    public static void listGrades() //displays all grades of class from 0 to gClassSize - 1 in order
    {
      //System.out.println("list grades is working");
      //System.out.println(gClassSize);
      System.out.println("LIST OF GRADES");
      for(int x = 0; x < gClassSize; x++)
      {
        System.out.println("Grade[" + x + "] : " + gGrades[x]);
      }
        
      return;
    }
    
    public static void report() //displays distribution of student grades to letters in class from F to A
    {
      //shows number of grades per letter (A-F) in the array
      //System.out.println("report is working!!!!!!");
      System.out.println("GRADES REPORT");
      int[] grades = getGradesLetter("A");
      System.out.println("F : " + grades[0] + "\nD : " + grades[1] + "\nC : " + grades[2] + "\nB : " + grades[3] + "\nA : " + grades[4]);
      
      return;
    }
    
    public static int[] getGradesLetter(String letter) //calculates number of students per letter grade
    {
      letter = "I'm leaving this value unused because this method works and the alternative seems slower";
      int[] gradesArray = new int[5]; //array that corresponds to letters, 0 - F, 5 - A.
      for(int x = 0; x < gClassSize; x++) //checks which letter a grade corresponds to, then iterates given letter
      {
        if (gGrades[x] < 60)
          gradesArray[0] = gradesArray[0] + 1;
        else if (gGrades[x] < 70 && gGrades[x] >= 60)
          gradesArray[1] = gradesArray[1] + 1;
        else if (gGrades[x] < 80 && gGrades[x] >= 70)
          gradesArray[2] = gradesArray[2] + 1;
        else if (gGrades[x] < 90 && gGrades[x] >= 80)
          gradesArray[3] = gradesArray[3] + 1;
        else if (gGrades[x] <= 100 && gGrades[x] >= 90)
          gradesArray[4] = gradesArray[4] + 1;
      }
      return gradesArray;
    }
    
    public static void addModifyGrade()
    {
      //adds or modify a grade of a validated value (0 - 100) corresponding to a valid index
      //System.out.println("addModifyGrade is working yeeeee");
      System.out.println("Enter the index (0 to " + (gClassSize - 1) + ")");
      int loopCheat = 0; //hehe
      int indexInput = 0;
      while(loopCheat != 1)
      {
        indexInput = gIN.nextInt(); //receives user input for which student grade to access
        if(indexInput >= 0 && indexInput < gClassSize) //validates user input
        {
          System.out.println("The current value of the grade in index " + indexInput + " is : " + gGrades[indexInput] + "\nEnter the grade you want to assign (0.00 - 100.00) : ");
          break;
        }
        else
        {
          System.out.println("Value out of range, please try again.");
        }
      }
      
      while(loopCheat != 1)
      {
        double inputGrade = gIN.nextDouble();
        if(inputGrade >= 0 && inputGrade <= 100) //validates user input
        {
          gGrades[indexInput] = inputGrade; //changes grade of assigned student
          break;
        }
        else
        {
          System.out.println("Value out of range, please try again.");
        }
      }
      return;
    }
    
    public static void swapGrades() 
    {
      // swap grades between two valid indexes
      //System.out.println("swapGrades is doing a thing");
      int loopCheat = 0; // .-.
      int firstIndexSwap = 0;
      int secondIndexSwap = 0;
      
      System.out.println("Enter the index from (0 to " + (gClassSize - 1) + ")");
      while(loopCheat != 1)
      {
        firstIndexSwap = gIN.nextInt();
        if(firstIndexSwap >= 0 && firstIndexSwap < gClassSize) //validates user input
        {
          break;
        }
        else
        {
          System.out.println("Value out of range, please try again.");
        }
      }
      
      System.out.println("Enter the index to (0 to " + (gClassSize - 1) + ") that is not " + firstIndexSwap + " :");
      while(loopCheat != 1)
      {
        secondIndexSwap = gIN.nextInt();
        if(secondIndexSwap >= 0 && secondIndexSwap < gClassSize && secondIndexSwap != firstIndexSwap) //validates user input
        {
          swapValues(firstIndexSwap, secondIndexSwap); //calls method to swap values
          break;
        }
        else
        {
          System.out.println("Value out of range, please try again.");
        }
      }
      return;
    }
    
    public static void swapValues(int f, int t)
    {
      //swaps values between input values of f - "from" and t - "to" in gGrades array.
      double placeHolder = 0.0;
      placeHolder = gGrades[f];
      gGrades[f] = gGrades[t];
      gGrades[t] = placeHolder;
      return;
    }
}

