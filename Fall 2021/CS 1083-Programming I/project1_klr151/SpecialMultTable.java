import java.util.Scanner; //imports scanner
import java.io.File; //imports package to create files
import java.io.FileWriter; //imports package to write to, edit, and append files
import java.io.IOException; //imports package to handle exceptions involving file methods

// This program will take a base number, a starting number, end number, increment, and a number for which its multiples will be skipped as input.
// Given user input, the program will output a multiplication table where each row is the current value alongside its product with the input base number.
// The table rows starts from the input starting number and increases by the input increment until the row value reaches the input end number
// Everytiume a row's product of base and value is a multiple of the input multiple to skip, the row will show a "Skipped" sign.

public class SpecialMultTable
{
 public static void main(String[] args)
 {
   
   try 
   {
      File output = new File("SpecialMultTableOutput.txt"); 
       //Troubleshooting portion, not necessary for final product
      if (output.createNewFile()) //checks if the output file does not already exists
      { 
        System.out.println("File created: " + output.getName()); //prints notification message
      } 
      else //checks if output does exists
      {
        System.out.println("File already exists."); //prints notification message
      }
      
   } 
   catch (IOException e) //catches exceptions thrown while accessing methods from file packages, necessary everytime a file is accessed or edited for some reason
    {
      System.out.println("An error occurred.");
      //The file methods dont work without the try catch thing, so I just went with the robust approach for file exceptions
    }
   
    
   System.out.println("UTSA - FALL2021 - CS1083 - Section 2 - Prj 1 - Written by Georgy Vinogradov - klr151\n"); //prints header
   try 
   {
      FileWriter oh = new FileWriter("SpecialMultTableOutput.txt"); //opens output file
      oh.write("UTSA - FALL2021 - CS1083 - Section 2 - Prj 1 - Written by Georgy Vinogradov - klr151\n\n"); //overwrites current contents of output file with header 
      oh.close(); //closes output file
      //System.out.println("Successfully wrote to the file.");
   } 
   catch (IOException e) 
   {
      System.out.println("An error occurred.");
   }
   Scanner CONSOLE = new Scanner(System.in); //initializes scanner CONSOLE
   
   System.out.println("Input base number (bn): "); //prompts for user input
   int baseNumber = CONSOLE.nextInt(); //reads and stores user input
   System.out.println("Input first number (fn): ");
   int firstNumber = CONSOLE.nextInt();
   System.out.println("Input last number (ln): ");
   int lastNumber = CONSOLE.nextInt();
   System.out.println("Input the increasement (inc): ");
   int incNumber = CONSOLE.nextInt();
   System.out.println("Input multiple(s) to skip (ms): ");
   int skipMultiple = CONSOLE.nextInt();
   
   System.out.println("\n-Special Multiplication Table -\n"); // multipliaction table header
   System.out.println("Value\tResult"); // multiplication table header
   
   try 
   {
      FileWriter oh = new FileWriter("SpecialMultTableOutput.txt", true); //opens output file
      oh.write("-Special Multiplication Table -\n\nValue\tResult"); //appends header to output file
      oh.close(); //closes output file
      //System.out.println("Successfully wrote to the file.");
    } 
   catch (IOException e) 
    {
      System.out.println("An error occurred.");
    }

   for (int x = firstNumber; x <= lastNumber; x += incNumber) //runs loop for ((last number - first number) / increment number) iterations
   {
     if (x % skipMultiple == 0) //checks if current "Value" is a multiple of user input multiple to skip
     {
       System.out.println(x + "\t-> Skipped - " + x * baseNumber + " <-"); //prints row of table with skipped message
       try 
       {
         FileWriter oh = new FileWriter("SpecialMultTableOutput.txt", true); //opens output file
         oh.write("\n" + x + "\t-> Skipped - " + x * baseNumber + " <-"); //appends row of skipped value and results to output file
         oh.close(); //closes output file
         //System.out.println("Successfully wrote to the file.");
       }
       catch (IOException e) 
       {
         System.out.println("An error occurred.");
       }
     }
     else //prints all other cases of value and result
     {
       System.out.println(x + "\t" + x * baseNumber); //prints row of value and result
       try 
       {
         FileWriter oh = new FileWriter("SpecialMultTableOutput.txt", true); //opens output file
         oh.write("\n" + x + "\t" + x * baseNumber); //appends row of value and result
         oh.close(); //closes output file
         //System.out.println("Successfully wrote to the file.");
       } 
       catch (IOException e) 
       {
         System.out.println("An error occurred.");
       }
     }
   }
   
   System.out.println("\nThank you for using this software, Georgy Vinogradov."); //farewell message
   try 
   {
      FileWriter oh = new FileWriter("SpecialMultTableOutput.txt", true); //opens output file
      oh.write("\n\nThank you for using this software, Georgy Vinogradov."); //appends farewell message
      oh.close(); //closes output file
      //System.out.println("Successfully wrote to the file.");
   } 
   catch (IOException e) 
   {
      System.out.println("An error occurred.");
   }
 
 }
}



